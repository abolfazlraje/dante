/*
 * Copyright (c) 1997, 1998, 1999, 2000, 2001
 *      Inferno Nettverk A/S, Norway.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. The above copyright notice, this list of conditions and the following
 *    disclaimer must appear in all copies of the software, derivative works
 *    or modified versions, and any portions thereof, aswell as in all
 *    supporting documentation.
 * 2. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by
 *      Inferno Nettverk A/S, Norway.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Inferno Nettverk A/S requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  sdc@inet.no
 *  Inferno Nettverk A/S
 *  Oslo Research Park
 *  Gaustadalléen 21
 *  NO-0349 Oslo
 *  Norway
 *
 * any improvements or extensions that they make and grant Inferno Nettverk A/S
 * the rights to redistribute these changes.
 *
 */

#include "common.h"

static const char rcsid[] =
"$Id: sockd_util.c,v 1.72 2001/05/11 09:14:44 michaels Exp $";

#define CM2IM(charmethodv, methodc, intmethodv) \
	do { \
		int cm2im = methodc; \
		while (--cm2im >= 0) \
			intmethodv[cm2im] = charmethodv[cm2im]; \
	} while (lintnoloop_sockd_h) \

int
selectmethod(methodv, methodc, offerdv, offeredc)
	const int *methodv;
	size_t methodc;
	const unsigned char *offerdv;
	size_t offeredc;
{
	size_t i;
	size_t methodokc;
	const char *methodokv;

	/* can select any standard method. */
	const char rfc931methodv[] = {AUTHMETHOD_NONE, AUTHMETHOD_UNAME};

	/*
	 * can select any standard method, some people want to use pam
	 * without user/password.
	*/
	const char pammethodv[] = {AUTHMETHOD_UNAME, AUTHMETHOD_NONE};

	for (i = 0; i < methodc; ++i) {
		if (methodv[i] > AUTHMETHOD_NOACCEPT) { /* non-socks method */
			int intmethodv[MAXMETHOD];
			size_t ii;

			CM2IM(offerdv, offeredc, intmethodv);

			/* find the correct array to use for trying to find a ok method. */
			switch (methodv[i]) {
				case AUTHMETHOD_RFC931: 
					methodokc = ELEMENTS(rfc931methodv);
					methodokv = rfc931methodv;
					break;

				case AUTHMETHOD_PAM:
					methodokc = ELEMENTS(pammethodv);
					methodokv = pammethodv;
					break;

				default:
					SERRX(methodv[i]);
			}

			for (ii = 0; ii < methodokc; ++ii)
				if (methodisset(methodokv[ii], intmethodv, offeredc))
					return methodokv[ii];
			
			continue;
		}

		if (memchr(offerdv, (unsigned char)methodv[i], offeredc) != NULL)
			return methodv[i];
	}

	return AUTHMETHOD_NOACCEPT;
}

void
setsockoptions(s)
	int s;
{
	const char *function = "setsockoptions()";
	socklen_t len;
	int type, val, bufsize;

#ifdef SO_BSDCOMPAT
	val = 1;
	if (setsockopt(s, SOL_SOCKET, SO_BSDCOMPAT, &val, sizeof(val)) != 0)
		swarn("%s: setsockopt(SO_BSDCOMPAT)", function);
#endif /* SO_BSDCOMPAT */

	len = sizeof(type);
	if (getsockopt(s, SOL_SOCKET, SO_TYPE, &type, &len) != 0) {
		swarn("%s: getsockopt(SO_TYPE)", function);
		return;
	}

	switch (type) {
		case SOCK_STREAM:
			bufsize = SOCKD_BUFSIZETCP;

			val = 1;
			if (setsockopt(s, SOL_SOCKET, SO_OOBINLINE, &val, sizeof(val)) != 0)
				swarn("%s: setsockopt(SO_OOBINLINE)", function);

			if (config.option.keepalive) {
				val = 1;
				if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val)) != 0)
					swarn("%s: setsockopt(SO_KEEPALIVE)", function);
			}
			break;

		case SOCK_DGRAM:
			bufsize = SOCKD_BUFSIZEUDP;

			val = 1;
			if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) != 0)
				if (errno != ENOPROTOOPT)
					swarn("%s: setsockopt(SO_BROADCAST)", function);

			break;

		default:
			SERRX(type);
	}

	val = bufsize;
	if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, &val, sizeof(val)) != 0
	||  setsockopt(s, SOL_SOCKET, SO_RCVBUF, &val, sizeof(val)) != 0)
		swarn("%s: setsockopt(SO_SNDBUF/SO_RCVBUF)", function);

#if HAVE_LIBWRAP
	if ((val = fcntl(s, F_GETFD, 0)) == -1
	|| fcntl(s, F_SETFD, val | FD_CLOEXEC) == -1)
		swarn("%s: fcntl(F_GETFD/F_SETFD)", function);
#endif
}

void
sockdexit(sig)
	int sig;
{
	const char *function = "sockdexit()";
	int i, mainmother;

	mainmother = config.state.motherpidv == NULL
	|| (pidismother(config.state.pid)
	  && *config.state.motherpidv == config.state.pid);

	if (mainmother) {
		if (sig > 0)
			slog(LOG_ALERT, "%s: terminating on signal %d", function, sig);
		else
			slog(LOG_ALERT, "%s: terminating", function, sig);

		/* don't want this while cleaning up, which is all that's left. */
		if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
			swarn("%s: signal(SIGCHLD, SIG_IGN)", function);
	}

#if HAVE_PROFILING
	if (chdir(SOCKS_PROFILEDIR) != 0)
		swarn("%s: chdir(%s)", function, SOCKS_PROFILEDIR);
	else {
		char dir[80];

		snprintfn(dir, sizeof(dir), "%s.%d",
		childtype2string(config.state.type), getpid());

		if (mkdir(dir, S_IRWXU) != 0)
			swarn("%s: mkdir(%s)", function, dir);
		else
			if (chdir(dir) != 0)
				swarn("%s: chdir(%s)", function, dir);
	}
#endif /* HAVE_PROFILING */

	for (i = 0;  i < config.log.fpc; ++i) {
		fclose(config.log.fpv[i]);
		close(config.log.fplockv[i]);
	}

	if (sig > 0)
		switch (sig) {
			/* ok signals. */
			case SIGINT:
			case SIGQUIT:
			case SIGTERM:
				break;

			/* bad signals. */
			default:
				abort();
		}

	if (mainmother)
		exit(sig > 0 ? EXIT_FAILURE : -sig);
	else
#if HAVE_PROFILING
		exit(sig > 0 ? EXIT_FAILURE : -sig);
#else
		_exit(sig > 0 ? EXIT_FAILURE : -sig);
#endif /* HAVE_PROFILING */
}

void
socks_seteuid(old, new)
	uid_t *old;
	uid_t new;
{
	const char *function = "socks_seteuid()";
	uid_t oldmem;

	if (old == NULL)
		old = &oldmem;
	*old = geteuid();

	slog(LOG_DEBUG, "%s: old: %lu, new: %lu", function, *old, new);

	if (*old == new)
		return;

	if (*old != config.state.euid)
		/* need to revert back to original (presumably 0) euid before changing. */
		if (seteuid(config.state.euid) != 0) {
			slog(LOG_ERR, "running Linux are we?");
			SERR(config.state.euid);
		}

	if (seteuid(new) != 0)
		serr(EXIT_FAILURE, "%s: seteuid(%d)", function, new);
}

void
socks_reseteuid(current, new)
	uid_t current;
	uid_t new;
{
	const char *function = "socks_reseteuid()";

	slog(LOG_DEBUG, "%s: current: %lu, new: %lu", function, current, new);

#if DIAGNOSTIC
	SASSERTX(current == geteuid());
#endif

	if (current == new)
		return;

	if (new != config.state.euid)
		/* need to revert back to original (presumably 0) euid before changing. */
		if (seteuid(config.state.euid) != 0)
			SERR(config.state.euid);

	if (seteuid(new) != 0)
		SERR(new);
}

int
pidismother(pid)
	pid_t pid;
{
	int i;

	for (i = 0; i < config.option.serverc; ++i)
		if (config.state.motherpidv[i] == pid)
			return i + 1;
	return 0;
}

