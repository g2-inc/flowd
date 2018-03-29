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

############################
# PIE and RELRO + BIND_NOW #
############################

CFLAGS+=	-fPIC -fPIE -Wl,-z,relro -Wl,-z,now
LDFLAGS+=	-pie

##########################
# Control-Flow Integrity #
##########################

CFLAGS+=	-fsanitize=cfi -flto -fvisibility=hidden
LDFLAGS+=	-fsanitize=cfi -flto -fvisibility=hidden

#############
# SafeStack #
#############

CFLAGS+=	-fsanitize=safe-stack
LDFLAGS+=	-fsanitize=safe-stack

.if defined(PREFIX)
BINDIR?=	${PREFIX}/bin
.else
BINDIR?=	/usr/bin
.endif

.include <bsd.prog.mk>
