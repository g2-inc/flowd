/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20170430

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 24 "./parse.y"
#include "flowd-common.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <netdb.h>
#include <stdarg.h>
#include <syslog.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flowd.h"
#include "addr.h"

static struct flowd_config	*conf = NULL;

static FILE			*fin = NULL;
static int			 lineno = 1;
static int			 errors = 0;
static int			 pdebug = 1;
const char			*infile;

int	yyerror(const char *, ...);
int	yyparse(void);
int	kw_cmp(const void *, const void *);
int	lookup(char *);
int	lgetc(FILE *);
int	lungetc(int);
int	findeol(void);
int	yylex(void);
int	atoul(char *, u_long *);
int	parse_abstime(const char *s, struct tm *tp);

TAILQ_HEAD(symhead, sym)	 symhead = TAILQ_HEAD_INITIALIZER(symhead);
struct sym {
	TAILQ_ENTRY(sym)	 entry;
	int			 used;
	int			 persist;
	char			*nam;
	char			*val;
};

int	 symset(const char *, const char *, int);
char	*symget(const char *);

typedef struct {
	union {
		u_int32_t			number;
		char				*string;
		u_int8_t			u8;
		struct xaddr			addr;
		struct {
			struct xaddr		addr;
			unsigned int		len;
		} prefix;
		struct {
			struct xaddr		addr;
			u_int16_t		port;
		} addrport;
		struct filter_action		filter_action;
		struct filter_match		filter_match;
	} v;
	int lineno;
} YYSTYPE;

static const char *days[7] = {
    "sun", "mon", "tue", "wed", "thu", "fri", "sat"
};

static const char *longdays[7] = {
    "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"
};

#line 101 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define LISTEN 257
#define ON 258
#define JOIN 259
#define GROUP 260
#define LOGFILE 261
#define LOGSOCK 262
#define BUFSIZE 263
#define STORE 264
#define PIDFILE 265
#define FLOW 266
#define SOURCE 267
#define ALL 268
#define TAG 269
#define ACCEPT 270
#define DISCARD 271
#define QUICK 272
#define AGENT 273
#define SRC 274
#define DST 275
#define PORT 276
#define PROTO 277
#define TOS 278
#define ANY 279
#define TCP_FLAGS 280
#define EQUALS 281
#define MASK 282
#define INET 283
#define INET6 284
#define DAYS 285
#define AFTER 286
#define BEFORE 287
#define DATE 288
#define IN_IFNDX 289
#define OUT_IFNDX 290
#define ERROR 291
#define STRING 292
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    0,    0,    0,    1,    5,   15,   15,
   39,   17,   16,   18,   18,   19,   19,    4,    4,    9,
   10,   11,   11,   12,   12,   12,   13,   14,   38,   38,
   38,   38,   38,   38,   38,   38,   38,    3,   40,   40,
   36,   36,   37,   37,    2,    2,   20,   20,    8,    8,
   34,   34,   35,   35,   26,   26,   21,   21,   21,   22,
   22,   22,   23,   23,   24,   24,    6,    7,    7,   25,
   25,   27,   27,   30,   31,   32,   33,   28,   28,   28,
   29,   29,   29,
};
static const YYINT yylen[] = {                            2,
    0,    2,    3,    3,    3,    3,    1,    1,    2,    1,
    3,    1,    1,    3,    1,    1,    1,    1,    0,    1,
    3,    3,    3,    1,    1,    1,    1,    1,    3,    5,
    3,    3,    2,    2,    4,    2,    2,    1,   15,    4,
    1,    1,    0,    2,    0,    1,    0,    3,    1,    1,
    0,    3,    0,    3,    0,    2,    0,    3,    6,    0,
    3,    6,    0,    3,    0,    3,    1,    0,    2,    0,
    5,    0,    2,    2,    2,    3,    3,    0,    1,    1,
    0,    1,    1,
};
static const YYINT yydefred[] = {                         1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   41,
   42,    0,    2,    0,    0,    0,    0,    6,    0,    0,
   10,    0,    0,   38,   37,    0,    0,    0,    0,    0,
    3,    4,    5,   12,    0,   13,   32,    9,    0,   16,
    0,   17,   31,    0,    7,   44,   46,    0,    0,   35,
    0,   40,    0,    0,   30,   14,   18,    0,    0,    0,
   48,    0,    0,    0,   52,    0,    0,    0,   54,   49,
   50,   56,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   59,    0,    8,   66,    0,    0,    0,    0,
   62,   67,   69,    0,   20,    0,   26,    0,   73,    0,
    0,   79,   80,    0,    0,    0,    0,    0,   27,   74,
    0,   39,   82,   83,   71,   21,   22,   23,   28,   76,
    0,   75,   77,
};
static const YYINT yydgoto[] = {                          1,
   95,   48,   25,   58,  102,  103,   98,   72,  106,  107,
  108,  109,  120,  130,   22,   37,   35,   42,   43,   54,
   74,   77,   81,   86,   92,   68,  100,  111,  122,  112,
  123,  113,  124,   60,   64,   14,   30,   15,   16,   17,
};
static const YYINT yysindex[] = {                         0,
  -10,    4, -238, -234, -263, -263, -260, -263, -233,    0,
    0,  -24,    0, -229,   39,   41,   44,    0, -236, -235,
    0, -232, -256,    0,    0, -232, -275, -263, -228, -214,
    0,    0,    0,    0, -204,    0,    0,    0, -228,    0,
   16,    0,    0, -232,    0,    0,    0, -258, -228,    0,
 -228,    0,   34, -221,    0,    0,    0, -222,   34, -215,
    0, -228,   34,   34,    0, -228, -241, -198,    0,    0,
    0,    0,   34, -196, -275,   34, -197, -194, -275,   34,
 -195,   34, -192, -263,   34, -191, -228,   34, -232, -228,
 -190, -200,    0, -228,    0,    0, -228,   34, -202, -193,
    0,    0,    0, -187,    0,    2,    0,   47,    0, -269,
 -199,    0,    0, -228, -202, -202, -202, -189,    0,    0,
 -261,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -189,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   -9,    0,    0,    0,    0,    0,    0,
    0,   44,   86,    0,    0,   87,    0,    0,    0,   11,
    0,    0,    0,    0,   88,    0,    0,    0,    0,    0,
   28,    0,    0,   89,    0,    0,    0,   45,    0,    0,
    0,    0, -188,   62,    0,    0,    0,    0, -188,   76,
    0,    0, -188,   90,    0,    0,    0,  103,    0,    0,
    0,    0, -270,  118,    0, -270,  132,  107,    0, -188,
  143, -188,  122,    0, -188,  139,    0, -188,  135,    0,
  -31,    6,    0,    0,    0,    0,    0, -180,    0,   -4,
    0,    0,    0,    0,    0,   23,    0,   40,    0,    0,
   92,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  -21,    0,    0,  -11,   15,   -8,    0,    0, -104,    0,
    0,    0,  -14,  -23,   -3,    0,    0,   52,  -40,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 430
static const YYINT yytable[] = {                         13,
   43,   68,   23,   40,   26,   78,   39,   46,   19,   52,
  126,  127,  128,   18,   53,   72,   41,   50,  118,   19,
   45,   19,  119,   43,   44,   20,  131,   55,   21,   56,
  119,   24,   24,   27,   78,   38,   28,   15,   83,   29,
   65,   70,   71,   45,   69,  116,  115,   62,   31,   25,
   32,   66,   67,   33,   47,   34,   36,   47,   49,   38,
   15,   75,   51,   45,   79,   93,   57,   59,   84,   41,
   87,   51,  101,   90,   63,   73,   94,   47,   76,   80,
   89,   82,   85,   88,   99,   53,  104,  121,   91,  105,
  117,   97,  110,  114,   51,   34,   36,   29,   11,   55,
   19,   81,  129,   19,   96,  125,  132,  133,   53,   61,
    0,    0,   57,    0,    0,    0,   58,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   60,    0,    0,
    0,   61,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   63,    0,    0,   64,    0,    0,    0,   70,    0,
    0,    0,   65,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    2,    3,    0,    4,   68,
    5,    6,    0,    7,    8,    9,    0,    0,   43,   10,
   11,    0,   43,   43,   43,   43,    0,   43,   43,    0,
   43,    0,    0,   43,   43,   43,   43,   43,   45,   43,
   43,   12,   78,   45,   45,   45,    0,   45,   45,    0,
   45,   72,   72,   45,   45,   45,   45,   45,    0,   45,
   45,   15,   15,   15,   15,   15,    0,   15,   24,   24,
   15,   15,   15,   15,   15,    0,   15,   15,   47,   47,
    0,   47,   47,    0,   47,   25,   25,   47,   47,   47,
   47,   47,    0,   47,   47,   51,   51,    0,   51,   51,
    0,   51,    0,    0,   51,   51,   51,   51,   51,   53,
   53,   51,   53,   53,    0,   53,    0,    0,   53,   53,
   53,   53,   53,   55,   55,    0,   55,   55,    0,   55,
    0,    0,   19,   19,   55,   55,   55,   57,    0,   57,
   57,   58,   57,   58,   58,    0,   58,   57,   57,   57,
    0,   58,   58,   58,   60,   60,    0,   60,   61,   61,
    0,   61,   60,   60,   60,    0,   61,   61,   61,   63,
    0,   63,   64,    0,   64,    0,   63,   63,   63,   64,
   64,   64,   65,   70,   70,   70,    0,   65,   65,   65,
};
static const YYINT yycheck[] = {                         10,
   10,   33,    6,  279,    8,   10,  263,   29,  279,  268,
  115,  116,  117,   10,  273,   10,  292,   39,  288,  258,
   10,  292,  292,   33,   28,  260,  288,   49,  292,   51,
  292,  292,   10,  267,   75,  292,   61,   10,   79,  269,
   62,  283,  284,   33,   66,   44,   45,   59,   10,   10,
   10,   63,   64,   10,   10,  292,  292,  272,  263,  292,
   33,   73,   47,  292,   76,   87,   33,  289,   80,  292,
   82,   10,   94,   85,  290,  274,   88,   33,  275,  277,
   84,  276,  278,  276,  285,   10,   98,  287,  280,  292,
   44,  282,  286,  281,   33,   10,   10,   10,   10,   10,
  281,   10,  292,  292,   90,  114,  121,  131,   33,   58,
   -1,   -1,   10,   -1,   -1,   -1,   10,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   10,   -1,   -1,
   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   10,   -1,   -1,   10,   -1,   -1,   -1,   10,   -1,
   -1,   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  256,  257,   -1,  259,  281,
  261,  262,   -1,  264,  265,  266,   -1,   -1,  268,  270,
  271,   -1,  272,  273,  274,  275,   -1,  277,  278,   -1,
  280,   -1,   -1,  283,  284,  285,  286,  287,  268,  289,
  290,  292,  287,  273,  274,  275,   -1,  277,  278,   -1,
  280,  286,  287,  283,  284,  285,  286,  287,   -1,  289,
  290,  274,  275,  276,  277,  278,   -1,  280,  286,  287,
  283,  284,  285,  286,  287,   -1,  289,  290,  274,  275,
   -1,  277,  278,   -1,  280,  286,  287,  283,  284,  285,
  286,  287,   -1,  289,  290,  274,  275,   -1,  277,  278,
   -1,  280,   -1,   -1,  283,  284,  285,  286,  287,  274,
  275,  290,  277,  278,   -1,  280,   -1,   -1,  283,  284,
  285,  286,  287,  274,  275,   -1,  277,  278,   -1,  280,
   -1,   -1,  283,  284,  285,  286,  287,  275,   -1,  277,
  278,  275,  280,  277,  278,   -1,  280,  285,  286,  287,
   -1,  285,  286,  287,  277,  278,   -1,  280,  277,  278,
   -1,  280,  285,  286,  287,   -1,  285,  286,  287,  278,
   -1,  280,  278,   -1,  280,   -1,  285,  286,  287,  285,
  286,  287,  280,  285,  286,  287,   -1,  285,  286,  287,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 292
#define YYUNDFTOKEN 335
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'!'",0,0,0,0,0,0,0,0,0,0,"','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,0,0,
"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"LISTEN","ON","JOIN","GROUP","LOGFILE","LOGSOCK","BUFSIZE","STORE","PIDFILE",
"FLOW","SOURCE","ALL","TAG","ACCEPT","DISCARD","QUICK","AGENT","SRC","DST",
"PORT","PROTO","TOS","ANY","TCP_FLAGS","EQUALS","MASK","INET","INET6","DAYS",
"AFTER","BEFORE","DATE","IN_IFNDX","OUT_IFNDX","ERROR","STRING",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : grammar",
"grammar :",
"grammar : grammar '\\n'",
"grammar : grammar conf_main '\\n'",
"grammar : grammar varset '\\n'",
"grammar : grammar filterrule '\\n'",
"grammar : grammar error '\\n'",
"number : STRING",
"octet : number",
"string : string STRING",
"string : STRING",
"varset : STRING '=' string",
"address_port : STRING",
"address : STRING",
"prefix : STRING '/' number",
"prefix : STRING",
"prefix_or_any : ANY",
"prefix_or_any : prefix",
"not : '!'",
"not :",
"dayname : STRING",
"dayrange : dayname '-' dayname",
"daylist : dayname ',' dayname",
"daylist : daylist ',' dayname",
"dayspec : dayname",
"dayspec : daylist",
"dayspec : dayrange",
"daytime : STRING",
"abstime : STRING",
"conf_main : LISTEN ON address_port",
"conf_main : LISTEN ON address_port BUFSIZE number",
"conf_main : FLOW SOURCE prefix_or_any",
"conf_main : JOIN GROUP address",
"conf_main : LOGFILE string",
"conf_main : LOGSOCK string",
"conf_main : LOGSOCK string BUFSIZE number",
"conf_main : PIDFILE string",
"conf_main : STORE logspec",
"logspec : STRING",
"filterrule : action tag quick match_agent match_if_in match_if_out match_af match_src match_dst match_proto match_tos match_tcp_flags match_day match_after match_before",
"filterrule : action tag quick ALL",
"action : ACCEPT",
"action : DISCARD",
"tag :",
"tag : TAG number",
"quick :",
"quick : QUICK",
"match_agent :",
"match_agent : AGENT not prefix",
"af : INET",
"af : INET6",
"match_if_in :",
"match_if_in : IN_IFNDX not number",
"match_if_out :",
"match_if_out : OUT_IFNDX not number",
"match_af :",
"match_af : not af",
"match_src :",
"match_src : SRC not prefix_or_any",
"match_src : SRC not prefix_or_any PORT not number",
"match_dst :",
"match_dst : DST not prefix_or_any",
"match_dst : DST not prefix_or_any PORT not number",
"match_proto :",
"match_proto : PROTO not string",
"match_tos :",
"match_tos : TOS not octet",
"tcp_flags : octet",
"tcp_mask :",
"tcp_mask : MASK tcp_flags",
"match_tcp_flags :",
"match_tcp_flags : TCP_FLAGS tcp_mask not EQUALS tcp_flags",
"match_day :",
"match_day : DAYS dayspec",
"match_dayafter : AFTER daytime",
"match_daybefore : BEFORE daytime",
"match_absafter : AFTER DATE abstime",
"match_absbefore : BEFORE DATE abstime",
"match_after :",
"match_after : match_dayafter",
"match_after : match_absafter",
"match_before :",
"match_before : match_daybefore",
"match_before : match_absbefore",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 883 "./parse.y"

struct keywords {
	const char	*k_name;
	int		 k_val;
};

int
yyerror(const char *fmt, ...)
{
	va_list		 ap;
	char		*nfmt, buf[2048];

	errors = 1;
	va_start(ap, fmt);
	snprintf(buf, sizeof(buf), "%s:%d: %s", infile, yylval.lineno, fmt);
	if ((nfmt = strdup(buf)) == NULL)
		logerrx("yyerror strdup");
	vlogit(LOG_ERR, nfmt, ap);
	va_end(ap);
	free(nfmt);
	return (0);
}

int
kw_cmp(const void *k, const void *e)
{
	return (strcmp(k, ((const struct keywords *)e)->k_name));
}

int
lookup(char *s)
{
	/* this has to be sorted always */
	static const struct keywords keywords[] = {
		{ "accept",		ACCEPT},
		{ "after",		AFTER},
		{ "agent",		AGENT},
		{ "all",		ALL},
		{ "any",		ANY},
		{ "before",		BEFORE},
		{ "bufsize",		BUFSIZE},
		{ "date",		DATE},
		{ "days",		DAYS},
		{ "discard",		DISCARD},
		{ "dst",		DST},
		{ "equals",		EQUALS},
		{ "flow",		FLOW},
		{ "group",		GROUP},
		{ "in_ifndx",		IN_IFNDX},
		{ "inet",		INET},
		{ "inet6",		INET6},
		{ "join",		JOIN},
		{ "listen",		LISTEN},
		{ "logfile",		LOGFILE},
		{ "logsock",		LOGSOCK},
		{ "mask",		MASK},
		{ "on",			ON},
		{ "out_ifndx",		OUT_IFNDX},
		{ "pidfile",		PIDFILE},
		{ "port",		PORT},
		{ "proto",		PROTO},
		{ "quick",		QUICK},
		{ "source",		SOURCE},
		{ "src",		SRC},
		{ "store",		STORE},
		{ "tag",		TAG},
		{ "tcp_flags",		TCP_FLAGS},
		{ "tos",		TOS},
	};
	const struct keywords	*p;

	p = bsearch(s, keywords, sizeof(keywords)/sizeof(keywords[0]),
	    sizeof(keywords[0]), kw_cmp);

	if (p) {
		if (pdebug > 1)
			logit(LOG_DEBUG, "%s: %d", s, p->k_val);
		return (p->k_val);
	} else {
		if (pdebug > 1)
			logit(LOG_DEBUG, "string: %s", s);
		return (STRING);
	}
}

#define MAXPUSHBACK	128

char	*parsebuf;
int	 parseindex;
char	 pushback_buffer[MAXPUSHBACK];
int	 pushback_index = 0;

int
lgetc(FILE *f)
{
	int	c, next;

	if (parsebuf) {
		/* Read character from the parsebuffer instead of input. */
		if (parseindex >= 0) {
			c = parsebuf[parseindex++];
			if (c != '\0')
				return (c);
			parsebuf = NULL;
		} else
			parseindex++;
	}

	if (pushback_index)
		return (pushback_buffer[--pushback_index]);

	while ((c = getc(f)) == '\\') {
		next = getc(f);
		if (next != '\n') {
			if (isspace(next))
				yyerror("whitespace after \\");
			ungetc(next, f);
			break;
		}
		yylval.lineno = lineno;
		lineno++;
	}
	if (c == '\t' || c == ' ') {
		/* Compress blanks to a single space. */
		do {
			c = getc(f);
		} while (c == '\t' || c == ' ');
		ungetc(c, f);
		c = ' ';
	}

	return (c);
}

int
lungetc(int c)
{
	if (c == EOF)
		return (EOF);
	if (parsebuf) {
		parseindex--;
		if (parseindex >= 0)
			return (c);
	}
	if (pushback_index < MAXPUSHBACK-1)
		return (pushback_buffer[pushback_index++] = c);
	else
		return (EOF);
}

int
findeol(void)
{
	int	c;

	parsebuf = NULL;
	pushback_index = 0;

	/* skip to either EOF or the first real EOL */
	while (1) {
		c = lgetc(fin);
		if (c == '\n') {
			lineno++;
			break;
		}
		if (c == EOF)
			break;
	}
	return (ERROR);
}

int
yylex(void)
{
	char	 buf[8096];
	char	*p, *val;
	int	 endc, c;
	int	 token;

top:
	p = buf;
	while ((c = lgetc(fin)) == ' ')
		; /* nothing */

	yylval.lineno = lineno;
	if (c == '#')
		while ((c = lgetc(fin)) != '\n' && c != EOF)
			; /* nothing */
	if (c == '$' && parsebuf == NULL) {
		while (1) {
			if ((c = lgetc(fin)) == EOF)
				return (0);

			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			if (isalnum(c) || c == '_') {
				*p++ = (char)c;
				continue;
			}
			*p = '\0';
			lungetc(c);
			break;
		}
		val = symget(buf);
		if (val == NULL) {
			yyerror("macro \"%s\" not defined", buf);
			return (findeol());
		}
		parsebuf = val;
		parseindex = 0;
		goto top;
	}

	switch (c) {
	case '\'':
	case '"':
		endc = c;
		while (1) {
			if ((c = lgetc(fin)) == EOF)
				return (0);
			if (c == endc) {
				*p = '\0';
				break;
			}
			if (c == '\n') {
				lineno++;
				continue;
			}
			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			*p++ = (char)c;
		}
		yylval.v.string = strdup(buf);
		if (yylval.v.string == NULL)
			logerrx("yylex: strdup");
		return (STRING);
	}

#define allowed_in_string(x) \
	(isalnum(x) || (ispunct(x) && x != '(' && x != ')' && \
	x != '{' && x != '}' && x != '<' && x != '>' && \
	x != '!' && x != '=' && x != '/' && x != '#' && \
	x != ',' && x != '-'))

	if (isalnum(c) || c == '[' || c == ':' || c == '_' || c == '*') {
		do {
			*p++ = c;
			if ((unsigned)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(fin)) != EOF && (allowed_in_string(c)));
		lungetc(c);
		*p = '\0';
		if ((token = lookup(buf)) == STRING)
			if ((yylval.v.string = strdup(buf)) == NULL)
				logerrx("yylex: strdup");
		return (token);
	}
	if (c == '\n') {
		yylval.lineno = lineno;
		lineno++;
	}
	if (c == EOF)
		return (0);
	return (c);
}

int
parse_config(const char *path, FILE *f, struct flowd_config *mconf,
    int filter_only)
{
	struct sym		*sym, *next;

	conf = mconf;

	TAILQ_INIT(&conf->listen_addrs);
	TAILQ_INIT(&conf->filter_list);
	TAILQ_INIT(&conf->allowed_devices);
	TAILQ_INIT(&conf->join_groups);

	lineno = 1;
	errors = 0;
	fin = f;
	infile = path;

	yyparse();

	if (!filter_only && conf->log_file == NULL &&
	    conf->log_socket == NULL) {
		logit(LOG_ERR, "No log file or socket specified");
		return (-1);
	}
	if (!filter_only && conf->pid_file == NULL && 
	    (conf->pid_file = strdup(DEFAULT_PIDFILE)) == NULL) {
		logit(LOG_ERR, "strdup pidfile");
		return (-1);
	}

	if (!filter_only && TAILQ_EMPTY(&conf->listen_addrs)) {
		logit(LOG_ERR, "No listening addresses specified");
		return (-1);
	}
	/* Free macros and check which have not been used. */
	for (sym = TAILQ_FIRST(&symhead); sym != NULL; sym = next) {
		next = TAILQ_NEXT(sym, entry);
		if ((conf->opts & FLOWD_OPT_VERBOSE) && !sym->used)
			logit(LOG_WARNING, "warning: macro \"%s\" not used",
			    sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	return (errors ? -1 : 0);
}

int
symset(const char *nam, const char *val, int persist)
{
	struct sym	*sym;

	for (sym = TAILQ_FIRST(&symhead); sym && strcmp(nam, sym->nam);
	    sym = TAILQ_NEXT(sym, entry))
		;	/* nothing */

	if (sym != NULL) {
		if (sym->persist == 1)
			return (0);
		else {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}
	if ((sym = calloc(1, sizeof(*sym))) == NULL)
		return (-1);

	sym->nam = strdup(nam);
	if (sym->nam == NULL) {
		free(sym);
		return (-1);
	}
	sym->val = strdup(val);
	if (sym->val == NULL) {
		free(sym->nam);
		free(sym);
		return (-1);
	}
	sym->used = 0;
	sym->persist = persist;
	TAILQ_INSERT_TAIL(&symhead, sym, entry);
	return (0);
}

int
cmdline_symset(char *s)
{
	char	*sym, *val;
	int	ret;
	size_t	len;

	if ((val = strrchr(s, '=')) == NULL)
		return (-1);

	len = strlen(s) - strlen(val) + 1;
	if ((sym = malloc(len)) == NULL)
		logerrx("cmdline_symset: malloc");

	strlcpy(sym, s, len);

	ret = symset(sym, val + 1, 1);
	free(sym);

	return (ret);
}

char *
symget(const char *nam)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry)
		if (strcmp(nam, sym->nam) == 0) {
			sym->used = 1;
			return (sym->val);
		}
	return (NULL);
}

int
atoul(char *s, u_long *ulvalp)
{
	u_long	 ulval;
	char	*ep;

	errno = 0;
	ulval = strtoul(s, &ep, 0);
	if (s[0] == '\0' || *ep != '\0')
		return (-1);
	if (errno == ERANGE && ulval == ULONG_MAX)
		return (-1);
	*ulvalp = ulval;
	return (0);
}

int
parse_abstime(const char *s, struct tm *tp)
{
	const char *cp;
	
	bzero(tp, sizeof(*tp));
	if ((cp = strptime(s, "%Y%m%d%H%M%S", tp)) != NULL && *cp == '\0')
		goto good;
	if ((cp = strptime(s, "%Y%m%d%H%M", tp)) != NULL && *cp == '\0')
		goto good;
	if ((cp = strptime(s, "%Y%m%d%H", tp)) != NULL && *cp == '\0')
		goto good;
	if ((cp = strptime(s, "%Y%m%d", tp)) != NULL && *cp == '\0')
		goto good;
	if ((cp = strptime(s, "%Y%m", tp)) != NULL && *cp == '\0')
		goto good;
	if ((cp = strptime(s, "%Y", tp)) != NULL && *cp == '\0')
		goto good;

	return -1;

 good:
	tp->tm_isdst = -1;
	return 0;
}

void
dump_config(struct flowd_config *c, const char *prefix, int filter_only)
{
	struct filter_rule *fr;
	struct listen_addr *la;
	struct join_group *jg;
#define DCPR(a) ((a) == NULL ? "" : a), ((a) == NULL ? "" : ": ")
	if (!filter_only) {
		if (c->log_file != NULL) {
			logit(LOG_DEBUG, "%s%slogfile \"%s\"",
			    DCPR(prefix), c->log_file);
		}
		if (c->log_socket != NULL) {
			logit(LOG_DEBUG, "%s%slogsock \"%s\"",
			    DCPR(prefix), c->log_socket);
		}
	}
	logit(LOG_DEBUG, "%s%s# store mask %08x", DCPR(prefix), c->store_mask);
	if (!filter_only) {
		logit(LOG_DEBUG, "%s%s# opts %08x", DCPR(prefix), c->opts);
		TAILQ_FOREACH(la, &c->listen_addrs, entry) {
			logit(LOG_DEBUG, "%s%slisten on [%s]:%d # fd = %d",
			    DCPR(prefix), addr_ntop_buf(&la->addr), la->port, la->fd);
		}
		TAILQ_FOREACH(jg, &c->join_groups, entry) {
			logit(LOG_DEBUG, "%s%sjoin group [%s]",
			    DCPR(prefix), addr_ntop_buf(&jg->addr));
		}
	}
	TAILQ_FOREACH(fr, &c->filter_list, entry)
		logit(LOG_DEBUG, "%s%s%s", DCPR(prefix), format_rule(fr));
#undef DCPR
}

#line 966 "y.tab.c"

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 6:
#line 125 "./parse.y"
	{ errors++; }
break;
case 7:
#line 128 "./parse.y"
	{
			u_long	ulval;

			if (atoul(yystack.l_mark[0].v.string, &ulval) == -1) {
				yyerror("\"%s\" is not a number", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			} else
				yyval.v.number = ulval;

			free(yystack.l_mark[0].v.string);
		}
break;
case 8:
#line 142 "./parse.y"
	{
			yyval.v.number = yystack.l_mark[0].v.number;
			if (yyval.v.number > 0xff) {
				yyerror("octet value exceeds 0xff");
				YYERROR;
			}
		}
break;
case 9:
#line 151 "./parse.y"
	{
			char buf[2048];
			
			snprintf(buf, sizeof(buf), "%s %s", yystack.l_mark[-1].v.string, yystack.l_mark[0].v.string);
			if ((yyval.v.string = strdup(buf)) == NULL)
				logerrx("string: strdup");
			free(yystack.l_mark[-1].v.string);
			free(yystack.l_mark[0].v.string);
		}
break;
case 11:
#line 163 "./parse.y"
	{
			if (conf->opts & FLOWD_OPT_VERBOSE)
				logit(LOG_DEBUG, "%s = \"%s\"", yystack.l_mark[-2].v.string, yystack.l_mark[0].v.string);
			if (symset(yystack.l_mark[-2].v.string, yystack.l_mark[0].v.string, 0) == -1)
				logerrx("cannot store variable");
			free(yystack.l_mark[-2].v.string);
			free(yystack.l_mark[0].v.string);
		}
break;
case 12:
#line 177 "./parse.y"
	{
			char *colon, *cp;
			unsigned long port;

			cp = yystack.l_mark[0].v.string;

			if ((colon = strrchr(cp, ':')) == NULL) {
				yyerror("missing port specification \"%s\"", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			*colon++ = '\0';

			/* Allow [blah]:foo for IPv6 */
			if (*cp == '[' && *(colon - 2) == ']') {
				cp++;
				*(colon - 2) = '\0';
			}

			if (atoul(colon, &port) == -1 || port == 0 || 
			    port > 65535) {
				yyerror("Invalid port number");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			if (addr_pton(cp, &yyval.v.addrport.addr) == -1) {
				yyerror("could not parse address \"%s\"", cp);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			yyval.v.addrport.port = port;

			free(yystack.l_mark[0].v.string);
		}
break;
case 13:
#line 215 "./parse.y"
	{
			char *cp;
			size_t len;

			cp = yystack.l_mark[0].v.string;
			len = strlen(cp);

			/* Allow [blah]:foo for IPv6 */
			if (cp[0] == '[' && cp[len - 1] == ']') {
				cp++;
				cp[len - 1] = '\0';
			}

			if (addr_pton(cp, &yyval.v.addr) == -1) {
				yyerror("could not parse address \"%s\"", cp);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			free(yystack.l_mark[0].v.string);
		}
break;
case 14:
#line 238 "./parse.y"
	{
			char *s, *cp, buf[2048];
			int len;

			/* Allow [blah]:foo for IPv6 */
			cp = yystack.l_mark[-2].v.string;
			len = strlen(cp);
			if (*cp == '[' && cp[len - 1]  == ']') {
				cp[len - 1] = '\0';
				cp++;
			}

			snprintf(buf, sizeof(buf), "%s/%u", cp, yystack.l_mark[0].v.number);
			if ((s = strdup(buf)) == NULL)
				logerrx("string: strdup");

			free(yystack.l_mark[-2].v.string);

			if (addr_pton_cidr(s, &yyval.v.prefix.addr, &yyval.v.prefix.len) == -1) {
				yyerror("could not parse address \"%s\"", s);
				free(s);
				YYERROR;
			}
			if (addr_host_is_all0s(&yyval.v.prefix.addr, yyval.v.prefix.len) != 0) {
				yyerror("invalid address/masklength \"%s\"", s);
				free(s);
				YYERROR;
			}
			free(s);
		}
break;
case 15:
#line 268 "./parse.y"
	{
			char *cp;
			int len;

			/* Allow [blah]:foo for IPv6 */
			cp = yystack.l_mark[0].v.string;
			len = strlen(cp);
			if (*cp == '[' && cp[len - 1]  == ']') {
				cp[len - 1] = '\0';
				cp++;
			}

			if (addr_pton_cidr(cp, &yyval.v.prefix.addr, &yyval.v.prefix.len) == -1) {
				yyerror("could not parse address \"%s\"", cp);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
break;
case 16:
#line 289 "./parse.y"
	{ memset(&yyval.v.prefix, 0, sizeof(yyval.v.prefix)); }
break;
case 17:
#line 290 "./parse.y"
	{ yyval.v.prefix = yystack.l_mark[0].v.prefix; }
break;
case 18:
#line 293 "./parse.y"
	{ yyval.v.number = 1; }
break;
case 19:
#line 294 "./parse.y"
	{ yyval.v.number = 0; }
break;
case 20:
#line 297 "./parse.y"
	{
			int i;

			for (i = 0; i < 7; i++) {
				if (strcasecmp(yystack.l_mark[0].v.string, days[i]) == 0 ||
				    strcasecmp(yystack.l_mark[0].v.string, longdays[i]) == 0) {
					yyval.v.number = i;
					break;
				}
			}
			if (i >= 7) {
				yyerror("invalid day of week \"%s\"", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
break;
case 21:
#line 316 "./parse.y"
	{
			int i, start, finish;

			start = yystack.l_mark[-2].v.number;
			finish = yystack.l_mark[0].v.number;

			if (finish < start)
				finish += 7;

			yyval.v.number = 0;
			for (i = start; i <= finish; i++)
				yyval.v.number |= (1 << (i % 7));
		}
break;
case 22:
#line 330 "./parse.y"
	{ yyval.v.number = (1 << yystack.l_mark[-2].v.number) | (1 << yystack.l_mark[0].v.number); }
break;
case 23:
#line 331 "./parse.y"
	{ yyval.v.number = yystack.l_mark[-2].v.number | (1 << yystack.l_mark[0].v.number); }
break;
case 24:
#line 333 "./parse.y"
	{ yyval.v.number = (1 << yystack.l_mark[0].v.number); }
break;
case 25:
#line 334 "./parse.y"
	{ yyval.v.number = yystack.l_mark[0].v.number; }
break;
case 26:
#line 335 "./parse.y"
	{ yyval.v.number = yystack.l_mark[0].v.number; }
break;
case 27:
#line 337 "./parse.y"
	{
			int h, m, s, n;

			n = sscanf(yystack.l_mark[0].v.string, "%d:%d:%d", &h, &m, &s);

			if (n < 2) {
				yyerror("invalid time spec \"%s\"", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			if (n < 3)
				s = 0;

			if (h < 0 || h > 23 || 
			    m < 0 || m > 59 || 
			    s < 0 || s > 59) {
				yyerror("invalid time of day \"%s\"", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
			yyval.v.number = s + (m * 60) + (h * 3600);
		}
break;
case 28:
#line 363 "./parse.y"
	{
			time_t t;
			struct tm tm;

			yyval.v.number = 0;
			if (parse_abstime(yystack.l_mark[0].v.string, &tm) != 0 ||
			    (t = mktime(&tm)) < 0) {
				yyerror("invalid time spec \"%s\"", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			yyval.v.number = t;
			free(yystack.l_mark[0].v.string);
		}
break;
case 29:
#line 379 "./parse.y"
	{
			struct listen_addr	*la;

			if ((la = calloc(1, sizeof(*la))) == NULL)
				logerrx("listen_on: calloc");

			la->fd = -1;
			la->addr = yystack.l_mark[0].v.addrport.addr;
			la->port = yystack.l_mark[0].v.addrport.port;
			la->bufsiz = 0;
			TAILQ_INSERT_TAIL(&conf->listen_addrs, la, entry);
		}
break;
case 30:
#line 391 "./parse.y"
	{
			struct listen_addr	*la;

			if ((la = calloc(1, sizeof(*la))) == NULL)
				logerrx("listen_on: calloc");

			la->fd = -1;
			la->addr = yystack.l_mark[-2].v.addrport.addr;
			la->port = yystack.l_mark[-2].v.addrport.port;
			la->bufsiz = yystack.l_mark[0].v.number;
			TAILQ_INSERT_TAIL(&conf->listen_addrs, la, entry);

		}
break;
case 31:
#line 404 "./parse.y"
	{
			struct allowed_device	*ad;

			if ((ad = calloc(1, sizeof(*ad))) == NULL)
				logerrx("flow_source: calloc");

			memcpy(&ad->addr, &yystack.l_mark[0].v.prefix.addr, sizeof(ad->addr));
			ad->masklen = yystack.l_mark[0].v.prefix.len;

			TAILQ_INSERT_TAIL(&conf->allowed_devices, ad, entry);
		}
break;
case 32:
#line 415 "./parse.y"
	{
			struct join_group	*jg;

			if ((jg = calloc(1, sizeof(*jg))) == NULL)
				logerrx("join_group: calloc");

			memcpy(&jg->addr, &yystack.l_mark[0].v.addr, sizeof(jg->addr));

			TAILQ_INSERT_TAIL(&conf->join_groups, jg, entry);
		}
break;
case 33:
#line 425 "./parse.y"
	{
			conf->log_file = yystack.l_mark[0].v.string;
		}
break;
case 34:
#line 428 "./parse.y"
	{
			conf->log_socket = yystack.l_mark[0].v.string;
		}
break;
case 35:
#line 431 "./parse.y"
	{
			conf->log_socket = yystack.l_mark[-2].v.string;
			conf->log_socket_bufsiz = yystack.l_mark[0].v.number;
		}
break;
case 36:
#line 435 "./parse.y"
	{
			conf->pid_file = yystack.l_mark[0].v.string;
		}
break;
case 37:
#line 438 "./parse.y"
	{ conf->store_mask |= yystack.l_mark[0].v.number; }
break;
case 38:
#line 441 "./parse.y"
	{
			if (strcasecmp(yystack.l_mark[0].v.string, "ALL") == 0)
				yyval.v.number = STORE_FIELD_ALL;
			else if (strcasecmp(yystack.l_mark[0].v.string, "TAG") == 0)
				yyval.v.number = STORE_FIELD_TAG;
			else if (strcasecmp(yystack.l_mark[0].v.string, "RECV_TIME") == 0)
				yyval.v.number = STORE_FIELD_RECV_TIME;
			else if (strcasecmp(yystack.l_mark[0].v.string, "PROTO_FLAGS_TOS") == 0)
				yyval.v.number = STORE_FIELD_PROTO_FLAGS_TOS;
			else if (strcasecmp(yystack.l_mark[0].v.string, "AGENT_ADDR") == 0)
				yyval.v.number = STORE_FIELD_AGENT_ADDR;
			else if (strcasecmp(yystack.l_mark[0].v.string, "AGENT_ADDR4") == 0)
				yyval.v.number = STORE_FIELD_AGENT_ADDR4;
			else if (strcasecmp(yystack.l_mark[0].v.string, "AGENT_ADDR6") == 0)
				yyval.v.number = STORE_FIELD_AGENT_ADDR6;
			else if (strcasecmp(yystack.l_mark[0].v.string, "SRCDST_ADDR") == 0)
				yyval.v.number = STORE_FIELD_SRCDST_ADDR;
			else if (strcasecmp(yystack.l_mark[0].v.string, "SRC_ADDR") == 0)
				yyval.v.number = STORE_FIELD_SRC_ADDR;
			else if (strcasecmp(yystack.l_mark[0].v.string, "SRC_ADDR4") == 0)
				yyval.v.number = STORE_FIELD_SRC_ADDR4;
			else if (strcasecmp(yystack.l_mark[0].v.string, "DST_ADDR") == 0)
				yyval.v.number = STORE_FIELD_DST_ADDR;
			else if (strcasecmp(yystack.l_mark[0].v.string, "DST_ADDR4") == 0)
				yyval.v.number = STORE_FIELD_DST_ADDR4;
			else if (strcasecmp(yystack.l_mark[0].v.string, "SRC_ADDR6") == 0)
				yyval.v.number = STORE_FIELD_SRC_ADDR6;
			else if (strcasecmp(yystack.l_mark[0].v.string, "DST_ADDR6") == 0)
				yyval.v.number = STORE_FIELD_DST_ADDR6;
			else if (strcasecmp(yystack.l_mark[0].v.string, "GATEWAY_ADDR") == 0)
				yyval.v.number = STORE_FIELD_GATEWAY_ADDR;
			else if (strcasecmp(yystack.l_mark[0].v.string, "GATEWAY_ADDR4") == 0)
				yyval.v.number = STORE_FIELD_GATEWAY_ADDR4;
			else if (strcasecmp(yystack.l_mark[0].v.string, "GATEWAY_ADDR6") == 0)
				yyval.v.number = STORE_FIELD_GATEWAY_ADDR6;
			else if (strcasecmp(yystack.l_mark[0].v.string, "SRCDST_PORT") == 0)
				yyval.v.number = STORE_FIELD_SRCDST_PORT;
			else if (strcasecmp(yystack.l_mark[0].v.string, "PACKETS") == 0)
				yyval.v.number = STORE_FIELD_PACKETS;
			else if (strcasecmp(yystack.l_mark[0].v.string, "OCTETS") == 0)
				yyval.v.number = STORE_FIELD_OCTETS;
			else if (strcasecmp(yystack.l_mark[0].v.string, "IF_INDICES") == 0)
				yyval.v.number = STORE_FIELD_IF_INDICES;
			else if (strcasecmp(yystack.l_mark[0].v.string, "AGENT_INFO") == 0)
				yyval.v.number = STORE_FIELD_AGENT_INFO;
			else if (strcasecmp(yystack.l_mark[0].v.string, "FLOW_TIMES") == 0)
				yyval.v.number = STORE_FIELD_FLOW_TIMES;
			else if (strcasecmp(yystack.l_mark[0].v.string, "AS_INFO") == 0)
				yyval.v.number = STORE_FIELD_AS_INFO;
			else if (strcasecmp(yystack.l_mark[0].v.string, "FLOW_ENGINE_INFO") == 0)
				yyval.v.number = STORE_FIELD_FLOW_ENGINE_INFO;
			else if (strcasecmp(yystack.l_mark[0].v.string, "CRC32") == 0)
				yyval.v.number = STORE_FIELD_CRC32;
			else {
				yyerror("unknown store field type \"%s\"", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
break;
case 39:
#line 503 "./parse.y"
	{
			struct filter_rule	*r;

			if ((r = calloc(1, sizeof(*r))) == NULL)
				logerrx("filterrule: calloc");

			r->action = yystack.l_mark[-14].v.filter_action;
			if (yystack.l_mark[-13].v.filter_action.action_what == FF_ACTION_TAG) {
				if (r->action.action_what != FF_ACTION_ACCEPT) {
					yyerror("tag not allowed in discard");
					free(r);
					YYERROR;
				}
				r->action = yystack.l_mark[-13].v.filter_action;
			}
			r->quick = yystack.l_mark[-12].v.number;

			r->match.agent_addr = yystack.l_mark[-11].v.filter_match.agent_addr;
			r->match.agent_masklen = yystack.l_mark[-11].v.filter_match.agent_masklen;
			r->match.match_what |= yystack.l_mark[-11].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-11].v.filter_match.match_negate;

			r->match.ifndx_in = yystack.l_mark[-10].v.filter_match.ifndx_in;
			r->match.match_what |= yystack.l_mark[-10].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-10].v.filter_match.match_negate;

			r->match.ifndx_out = yystack.l_mark[-9].v.filter_match.ifndx_out;
			r->match.match_what |= yystack.l_mark[-9].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-9].v.filter_match.match_negate;
			
			r->match.af = yystack.l_mark[-8].v.filter_match.af;
			r->match.match_what |= yystack.l_mark[-8].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-8].v.filter_match.match_negate;

			r->match.src_addr = yystack.l_mark[-7].v.filter_match.src_addr;
			r->match.src_masklen = yystack.l_mark[-7].v.filter_match.src_masklen;
			r->match.src_port = yystack.l_mark[-7].v.filter_match.src_port;
			r->match.match_what |= yystack.l_mark[-7].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-7].v.filter_match.match_negate;

			r->match.dst_addr = yystack.l_mark[-6].v.filter_match.dst_addr;
			r->match.dst_masklen = yystack.l_mark[-6].v.filter_match.dst_masklen;
			r->match.dst_port = yystack.l_mark[-6].v.filter_match.dst_port;
			r->match.match_what |= yystack.l_mark[-6].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-6].v.filter_match.match_negate;

			r->match.proto = yystack.l_mark[-5].v.filter_match.proto;
			r->match.match_what |= yystack.l_mark[-5].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-5].v.filter_match.match_negate;

			r->match.tos = yystack.l_mark[-4].v.filter_match.tos;
			r->match.match_what |= yystack.l_mark[-4].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-4].v.filter_match.match_negate;

			r->match.tcp_flags_mask = yystack.l_mark[-3].v.filter_match.tcp_flags_mask;
			r->match.tcp_flags_equals = yystack.l_mark[-3].v.filter_match.tcp_flags_equals;
			r->match.match_what |= yystack.l_mark[-3].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-3].v.filter_match.match_negate;

			r->match.day_mask = yystack.l_mark[-2].v.filter_match.day_mask;
			r->match.match_what |= yystack.l_mark[-2].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-2].v.filter_match.match_negate;

			r->match.dayafter = yystack.l_mark[-1].v.filter_match.dayafter - 1;
			r->match.absafter = yystack.l_mark[-1].v.filter_match.absafter;
			r->match.match_what |= yystack.l_mark[-1].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[-1].v.filter_match.match_negate;

			r->match.daybefore = yystack.l_mark[0].v.filter_match.daybefore - 1;
			r->match.absbefore = yystack.l_mark[0].v.filter_match.absbefore;
			r->match.match_what |= yystack.l_mark[0].v.filter_match.match_what;
			r->match.match_negate |= yystack.l_mark[0].v.filter_match.match_negate;

			if ((r->match.match_what & FF_MATCH_DAYTIME) != 0) {
				if (r->match.dayafter != 0 && 
				    r->match.daybefore != 0 &&
				    r->match.dayafter >= r->match.daybefore) {
					yyerror("day start time is after "
					    "day finish time");
					free(r);
					YYERROR;
				}
			}

			if ((r->match.match_what & FF_MATCH_ABSTIME) != 0) {
				if (r->match.absafter != 0 && 
				    r->match.absbefore != 0 &&
				    r->match.absafter >= r->match.absbefore) {
					yyerror("date start time is after "
					    "date finish time");
					free(r);
					YYERROR;
				}
			}

			if ((r->match.match_what & 
			    (FF_MATCH_SRC_PORT|FF_MATCH_DST_PORT)) && 
			    (r->match.proto != IPPROTO_TCP &&
			    r->match.proto != IPPROTO_UDP)) {
				yyerror("port matching is only allowed for "
				    "tcp or udp protocols");
				free(r);
				YYERROR;
			}

			if ((r->match.match_what & FF_MATCH_SRC_ADDR) && 
			    (r->match.match_what & FF_MATCH_DST_ADDR) &&
			    (r->match.src_addr.af != r->match.dst_addr.af)) {
				yyerror("src and dst address families do "
				    "not match");
				free(r);
				YYERROR;
			}

			if ((r->match.match_what & FF_MATCH_AF)) {
				if ((r->match.match_what & FF_MATCH_SRC_ADDR) &&
				     (r->match.af != r->match.src_addr.af)) {
					yyerror("Rule address family does not "
					    "match src address family");
					free(r);
					YYERROR;
				}
				if ((r->match.match_what & FF_MATCH_DST_ADDR) &&
				     (r->match.af != r->match.dst_addr.af)) {
					yyerror("Rule address family does not "
					    "match dst address family");
					free(r);
					YYERROR;
				}
			}
				    
			if ((r->match.match_what & FF_MATCH_TCP_FLAGS) &&
			    (r->match.proto != IPPROTO_TCP)) {
				yyerror("tcp_flags matching is only allowed "
				    "for the tcp protocol");
				free(r);
				YYERROR;
			}

			TAILQ_INSERT_TAIL(&conf->filter_list, r, entry);
		}
break;
case 40:
#line 645 "./parse.y"
	{
			struct filter_rule	*r;

			if ((r = calloc(1, sizeof(*r))) == NULL)
				logerrx("filterrule: calloc");

			r->action = yystack.l_mark[-3].v.filter_action;
			if (yystack.l_mark[-2].v.filter_action.action_what == FF_ACTION_TAG) {
				if (r->action.action_what != FF_ACTION_ACCEPT) {
					yyerror("tag not allowed in discard");
					free(r);
					YYERROR;
				}
				r->action = yystack.l_mark[-2].v.filter_action;
			}
			r->quick = yystack.l_mark[-1].v.number;

			TAILQ_INSERT_TAIL(&conf->filter_list, r, entry);
		}
break;
case 41:
#line 666 "./parse.y"
	{
			bzero(&yyval.v.filter_action, sizeof(yyval.v.filter_action));
			yyval.v.filter_action.action_what = FF_ACTION_ACCEPT;
		}
break;
case 42:
#line 670 "./parse.y"
	{
			bzero(&yyval.v.filter_action, sizeof(yyval.v.filter_action));
			yyval.v.filter_action.action_what = FF_ACTION_DISCARD;
		}
break;
case 43:
#line 675 "./parse.y"
	{ bzero(&yyval.v.filter_action, sizeof(yyval.v.filter_action)); }
break;
case 44:
#line 676 "./parse.y"
	{
			bzero(&yyval.v.filter_action, sizeof(yyval.v.filter_action));
			yyval.v.filter_action.action_what = FF_ACTION_TAG;
			yyval.v.filter_action.tag = yystack.l_mark[0].v.number;
		}
break;
case 45:
#line 683 "./parse.y"
	{ yyval.v.number = 0; }
break;
case 46:
#line 684 "./parse.y"
	{ yyval.v.number = 1; }
break;
case 47:
#line 687 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 48:
#line 688 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			memcpy(&yyval.v.filter_match.agent_addr, &yystack.l_mark[0].v.prefix.addr, sizeof(yyval.v.filter_match.agent_addr));
			yyval.v.filter_match.agent_masklen = yystack.l_mark[0].v.prefix.len;
			yyval.v.filter_match.match_what |= FF_MATCH_AGENT_ADDR;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_AGENT_ADDR : 0;
		}
break;
case 49:
#line 697 "./parse.y"
	{ yyval.v.number = AF_INET; }
break;
case 50:
#line 698 "./parse.y"
	{ yyval.v.number = AF_INET6; }
break;
case 51:
#line 700 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 52:
#line 701 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			yyval.v.filter_match.ifndx_in = yystack.l_mark[0].v.number;
			yyval.v.filter_match.match_what |= FF_MATCH_IFNDX_IN;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_IFNDX_IN : 0;
			if (yyval.v.filter_match.ifndx_in <= 0 || yyval.v.filter_match.ifndx_in > 65535) {
				yyerror("invalid input interface index");
				YYERROR;
			}
		}
break;
case 53:
#line 713 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 54:
#line 714 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			yyval.v.filter_match.ifndx_out = yystack.l_mark[0].v.number;
			yyval.v.filter_match.match_what |= FF_MATCH_IFNDX_OUT;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_IFNDX_OUT : 0;
			if (yyval.v.filter_match.ifndx_out <= 0 || yyval.v.filter_match.ifndx_out > 65535) {
				yyerror("invalid output interface index");
				YYERROR;
			}
		}
break;
case 55:
#line 726 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 56:
#line 727 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			yyval.v.filter_match.af = yystack.l_mark[0].v.number;
			yyval.v.filter_match.match_what |= FF_MATCH_AF;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_AF : 0;
		}
break;
case 57:
#line 735 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 58:
#line 736 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			memcpy(&yyval.v.filter_match.src_addr, &yystack.l_mark[0].v.prefix.addr, sizeof(yyval.v.filter_match.src_addr));
			yyval.v.filter_match.src_masklen = yystack.l_mark[0].v.prefix.len;
			yyval.v.filter_match.match_what |= FF_MATCH_SRC_ADDR;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_SRC_ADDR : 0;
		}
break;
case 59:
#line 743 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			memcpy(&yyval.v.filter_match.src_addr, &yystack.l_mark[-3].v.prefix.addr, sizeof(yyval.v.filter_match.src_addr));
			yyval.v.filter_match.src_masklen = yystack.l_mark[-3].v.prefix.len;
			yyval.v.filter_match.src_port = yystack.l_mark[0].v.number;
			if (yyval.v.filter_match.src_port <= 0 || yyval.v.filter_match.src_port > 65535) {
				yyerror("invalid port number");
				YYERROR;
			}
			if (yyval.v.filter_match.src_addr.af != 0)
				yyval.v.filter_match.match_what |= FF_MATCH_SRC_ADDR;
			yyval.v.filter_match.match_what |= FF_MATCH_SRC_PORT;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-4].v.number ? FF_MATCH_SRC_ADDR : 0;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_SRC_PORT : 0;
		}
break;
case 60:
#line 760 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 61:
#line 761 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			memcpy(&yyval.v.filter_match.dst_addr, &yystack.l_mark[0].v.prefix.addr, sizeof(yyval.v.filter_match.dst_addr));
			yyval.v.filter_match.dst_masklen = yystack.l_mark[0].v.prefix.len;
			yyval.v.filter_match.match_what |= FF_MATCH_DST_ADDR;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_DST_ADDR : 0;
		}
break;
case 62:
#line 768 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			memcpy(&yyval.v.filter_match.dst_addr, &yystack.l_mark[-3].v.prefix.addr, sizeof(yyval.v.filter_match.dst_addr));
			yyval.v.filter_match.dst_masklen = yystack.l_mark[-3].v.prefix.len;
			yyval.v.filter_match.dst_port = yystack.l_mark[0].v.number;
			if (yyval.v.filter_match.dst_port <= 0 || yyval.v.filter_match.dst_port > 65535) {
				yyerror("invalid port number");
				YYERROR;
			}
			if (yyval.v.filter_match.dst_addr.af != 0)
				yyval.v.filter_match.match_what |= FF_MATCH_DST_ADDR;
			yyval.v.filter_match.match_what |= FF_MATCH_DST_PORT;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-4].v.number ? FF_MATCH_DST_ADDR : 0;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_DST_PORT : 0;
		}
break;
case 63:
#line 785 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 64:
#line 786 "./parse.y"
	{
			unsigned long proto;
			struct protoent *pe;

			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			if ((pe = getprotobyname(yystack.l_mark[0].v.string)) != NULL)
				proto = pe->p_proto;
			else {
				if (atoul(yystack.l_mark[0].v.string, &proto) == -1 || proto == 0 || 
				    proto > 255) {
					yyerror("Invalid protocol");
					free(yystack.l_mark[0].v.string);
					YYERROR;
				}
			}
			free(yystack.l_mark[0].v.string);
			yyval.v.filter_match.proto = proto;
			yyval.v.filter_match.match_what |= FF_MATCH_PROTOCOL;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_PROTOCOL : 0;
		}
break;
case 65:
#line 808 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 66:
#line 809 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			yyval.v.filter_match.tos = yystack.l_mark[0].v.number;
			yyval.v.filter_match.match_what |= FF_MATCH_TOS;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-1].v.number ? FF_MATCH_TOS : 0;
		}
break;
case 67:
#line 817 "./parse.y"
	{ yyval.v.number = yystack.l_mark[0].v.number; }
break;
case 68:
#line 820 "./parse.y"
	{ yyval.v.number = 0xff; }
break;
case 69:
#line 821 "./parse.y"
	{ yyval.v.number = yystack.l_mark[0].v.number; }
break;
case 70:
#line 824 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 71:
#line 825 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			if (yystack.l_mark[-3].v.number > 0xff) {
				yyerror("Invalid ToS");
				YYERROR;
			}
			yyval.v.filter_match.tcp_flags_mask = yystack.l_mark[-3].v.number;
			yyval.v.filter_match.tcp_flags_equals = yystack.l_mark[0].v.number;
			yyval.v.filter_match.match_what |= FF_MATCH_TCP_FLAGS;
			yyval.v.filter_match.match_negate |= yystack.l_mark[-2].v.number ? FF_MATCH_TCP_FLAGS : 0;
		}
break;
case 72:
#line 838 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 73:
#line 839 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			yyval.v.filter_match.day_mask = yystack.l_mark[0].v.number;
			yyval.v.filter_match.match_what |= FF_MATCH_DAYTIME;
		}
break;
case 74:
#line 846 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			yyval.v.filter_match.dayafter = yystack.l_mark[0].v.number + 1;
			yyval.v.filter_match.match_what |= FF_MATCH_DAYTIME;
		}
break;
case 75:
#line 853 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			yyval.v.filter_match.daybefore = yystack.l_mark[0].v.number + 1;
			yyval.v.filter_match.match_what |= FF_MATCH_DAYTIME;
		}
break;
case 76:
#line 860 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			yyval.v.filter_match.absafter = yystack.l_mark[0].v.number;
			yyval.v.filter_match.match_what |= FF_MATCH_ABSTIME;
		}
break;
case 77:
#line 867 "./parse.y"
	{
			bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match));
			yyval.v.filter_match.absbefore = yystack.l_mark[0].v.number;
			yyval.v.filter_match.match_what |= FF_MATCH_ABSTIME;
		}
break;
case 78:
#line 874 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 79:
#line 875 "./parse.y"
	{ yyval.v.filter_match = yystack.l_mark[0].v.filter_match; }
break;
case 80:
#line 876 "./parse.y"
	{ yyval.v.filter_match = yystack.l_mark[0].v.filter_match; }
break;
case 81:
#line 878 "./parse.y"
	{ bzero(&yyval.v.filter_match, sizeof(yyval.v.filter_match)); }
break;
case 82:
#line 879 "./parse.y"
	{ yyval.v.filter_match = yystack.l_mark[0].v.filter_match; }
break;
case 83:
#line 880 "./parse.y"
	{ yyval.v.filter_match = yystack.l_mark[0].v.filter_match; }
break;
#line 2072 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
