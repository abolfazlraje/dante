/* $Id: getdtablesize.c,v 1.4 2008/07/25 08:49:04 michaels Exp $ */

#ifdef HAVE_CONFIG_H
#include "autoconf.h"
#endif  /* HAVE_CONFIG_H */

#include "common.h"

#if !HAVE_GETDTABLESIZE

int
getdtablesize(void)
{
#if HAVE_SYSCONF
      const int res = sysconf(_SC_OPEN_MAX);

      if (res == -1)
         return SOCKS_FD_MAX;
      else
         return res;
#else
      return SOCKS_FD_MAX;   /* XXX, won't work. */
#endif  /* HAVE_SYSCONF */
}
#else
static void avoid_error __P((void));
static void avoid_error()
{
   avoid_error();
}
#endif  /* HAVE_GETDTABLESIZE */
