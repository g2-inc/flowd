PROG=	flowd
SRCS=	\
	closefrom.c \
	daemon.c \
	filter.c \
	flowd.c \
	log.c \
	parse.c \
	peer.c \
	privsep.c \
	privsep_fdpass.c \
	setproctitle.c
MAN=

LDADD=	-lflowd

CFLAGS+=	\
		-I${.CURDIR}/../../include

LDFLAGS+=	\
		-L${.CURDIR}/../../lib/libflowd/obj

.if defined(PREFIX)
BINDIR?=	${PREFIX}/bin
.else
BINDIR?=	/usr/bin
.endif

.include <bsd.prog.mk>
