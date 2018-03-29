PROG=	flowd-reader
SRCS=	\
	filter.c \
	flowd-reader.c \
	log.c \
	parse.c
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
