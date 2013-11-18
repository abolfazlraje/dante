#define ALARM 257
#define ALARMTYPE_DATA 258
#define ALARMTYPE_DISCONNECT 259
#define ALARMIF_INTERNAL 260
#define ALARMIF_EXTERNAL 261
#define CLIENTCOMPATIBILITY 262
#define NECGSSAPI 263
#define CLIENTRULE 264
#define HOSTIDRULE 265
#define SOCKSRULE 266
#define COMPATIBILITY 267
#define SAMEPORT 268
#define DRAFT_5_05 269
#define CONNECTTIMEOUT 270
#define TCP_FIN_WAIT 271
#define CPU 272
#define MASK 273
#define SCHEDULE 274
#define CPUMASK_ANYCPU 275
#define DEBUGGING 276
#define DEPRECATED 277
#define ERRORLOG 278
#define LOGOUTPUT 279
#define LOGFILE 280
#define LOGTYPE_ERROR 281
#define LOGIF_INTERNAL 282
#define LOGIF_EXTERNAL 283
#define ERRORVALUE 284
#define EXTENSION 285
#define BIND 286
#define PRIVILEGED 287
#define EXTERNAL_ROTATION 288
#define SAMESAME 289
#define GROUPNAME 290
#define HOSTID 291
#define HOSTINDEX 292
#define INTERFACE 293
#define SOCKETOPTION_SYMBOLICVALUE 294
#define INTERNAL 295
#define EXTERNAL 296
#define INTERNALSOCKET 297
#define EXTERNALSOCKET 298
#define IOTIMEOUT 299
#define IOTIMEOUT_TCP 300
#define IOTIMEOUT_UDP 301
#define NEGOTIATETIMEOUT 302
#define LIBWRAP_FILE 303
#define LOGLEVEL 304
#define SOCKSMETHOD 305
#define CLIENTMETHOD 306
#define METHOD 307
#define METHODNAME 308
#define NONE 309
#define BSDAUTH 310
#define GSSAPI 311
#define PAM_ADDRESS 312
#define PAM_ANY 313
#define PAM_USERNAME 314
#define RFC931 315
#define UNAME 316
#define MONITOR 317
#define PROCESSTYPE 318
#define PROC_MAXREQUESTS 319
#define REALM 320
#define REALNAME 321
#define RESOLVEPROTOCOL 322
#define REQUIRED 323
#define SCHEDULEPOLICY 324
#define SERVERCONFIG 325
#define CLIENTCONFIG 326
#define SOCKET 327
#define CLIENTSIDE_SOCKET 328
#define SNDBUF 329
#define RCVBUF 330
#define SOCKETPROTOCOL 331
#define SOCKETOPTION_OPTID 332
#define SRCHOST 333
#define NODNSMISMATCH 334
#define NODNSUNKNOWN 335
#define CHECKREPLYAUTH 336
#define USERNAME 337
#define USER_PRIVILEGED 338
#define USER_UNPRIVILEGED 339
#define USER_LIBWRAP 340
#define WORD__IN 341
#define ROUTE 342
#define VIA 343
#define GLOBALROUTEOPTION 344
#define BADROUTE_EXPIRE 345
#define MAXFAIL 346
#define PORT 347
#define NUMBER 348
#define BANDWIDTH 349
#define BOUNCE 350
#define BSDAUTHSTYLE 351
#define BSDAUTHSTYLENAME 352
#define COMMAND 353
#define COMMAND_BIND 354
#define COMMAND_CONNECT 355
#define COMMAND_UDPASSOCIATE 356
#define COMMAND_BINDREPLY 357
#define COMMAND_UDPREPLY 358
#define ACTION 359
#define FROM 360
#define TO 361
#define GSSAPIENCTYPE 362
#define GSSAPIENC_ANY 363
#define GSSAPIENC_CLEAR 364
#define GSSAPIENC_INTEGRITY 365
#define GSSAPIENC_CONFIDENTIALITY 366
#define GSSAPIENC_PERMESSAGE 367
#define GSSAPIKEYTAB 368
#define GSSAPISERVICE 369
#define GSSAPISERVICENAME 370
#define GSSAPIKEYTABNAME 371
#define IPV4 372
#define IPV6 373
#define IPVANY 374
#define DOMAINNAME 375
#define IFNAME 376
#define URL 377
#define LDAPATTRIBUTE 378
#define LDAPATTRIBUTE_AD 379
#define LDAPATTRIBUTE_HEX 380
#define LDAPATTRIBUTE_AD_HEX 381
#define LDAPBASEDN 382
#define LDAP_BASEDN 383
#define LDAPBASEDN_HEX 384
#define LDAPBASEDN_HEX_ALL 385
#define LDAPCERTFILE 386
#define LDAPCERTPATH 387
#define LDAPPORT 388
#define LDAPPORTSSL 389
#define LDAPDEBUG 390
#define LDAPDEPTH 391
#define LDAPAUTO 392
#define LDAPSEARCHTIME 393
#define LDAPDOMAIN 394
#define LDAP_DOMAIN 395
#define LDAPFILTER 396
#define LDAPFILTER_AD 397
#define LDAPFILTER_HEX 398
#define LDAPFILTER_AD_HEX 399
#define LDAPGROUP 400
#define LDAPGROUP_NAME 401
#define LDAPGROUP_HEX 402
#define LDAPGROUP_HEX_ALL 403
#define LDAPKEYTAB 404
#define LDAPKEYTABNAME 405
#define LDAPDEADTIME 406
#define LDAPSERVER 407
#define LDAPSERVER_NAME 408
#define LDAPSSL 409
#define LDAPCERTCHECK 410
#define LDAPKEEPREALM 411
#define LDAPTIMEOUT 412
#define LDAPCACHE 413
#define LDAPCACHEPOS 414
#define LDAPCACHENEG 415
#define LDAPURL 416
#define LDAP_URL 417
#define LDAP_FILTER 418
#define LDAP_ATTRIBUTE 419
#define LDAP_CERTFILE 420
#define LDAP_CERTPATH 421
#define LIBWRAPSTART 422
#define LIBWRAP_ALLOW 423
#define LIBWRAP_DENY 424
#define LIBWRAP_HOSTS_ACCESS 425
#define LINE 426
#define OPERATOR 427
#define PAMSERVICENAME 428
#define PROTOCOL 429
#define PROTOCOL_TCP 430
#define PROTOCOL_UDP 431
#define PROTOCOL_FAKE 432
#define PROXYPROTOCOL 433
#define PROXYPROTOCOL_SOCKS_V4 434
#define PROXYPROTOCOL_SOCKS_V5 435
#define PROXYPROTOCOL_HTTP 436
#define PROXYPROTOCOL_UPNP 437
#define REDIRECT 438
#define SENDSIDE 439
#define RECVSIDE 440
#define SERVICENAME 441
#define SESSION_INHERITABLE 442
#define SESSIONMAX 443
#define SESSIONTHROTTLE 444
#define SESSIONSTATE_KEY 445
#define SESSIONSTATE_MAX 446
#define SESSIONSTATE_THROTTLE 447
#define RULE_LOG 448
#define RULE_LOG_CONNECT 449
#define RULE_LOG_DATA 450
#define RULE_LOG_DISCONNECT 451
#define RULE_LOG_ERROR 452
#define RULE_LOG_IOOPERATION 453
#define RULE_LOG_TCPINFO 454
#define STATEKEY 455
#define UDPPORTRANGE 456
#define UDPCONNECTDST 457
#define USER 458
#define GROUP 459
#define VERDICT_BLOCK 460
#define VERDICT_PASS 461
#define YES 462
#define NO 463
#ifndef YYSTYPE_DEFINED
#define YYSTYPE_DEFINED
typedef union {
   struct {
      uid_t   uid;
      gid_t   gid;
   } uid;

   struct {
      valuetype_t valuetype;
      const int   *valuev;
   } error;

   struct {
      const char *oldname;
      const char *newname;
   } deprecated;

   char       *string;
   int        method;
   long long  number;
} YYSTYPE;
#endif /* YYSTYPE_DEFINED */
extern YYSTYPE socks_yylval;
