/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "alpha_parser.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <string>
	#include <fstream>
	#include <assert.h>
	#include <list>
	#include <utility>
	#include "function_actions.h"
	#include "Object.h"
	#include "defines_header.h"
	#include "error_handler.h"
	#define yylex() lexer->alpha_yylex()
	#define BON "\e[1m"
	#define BOFF "\e[0m"	
	int yyerror (char * yaccProvidedMessage);
	Object* __astRoot;

#line 84 "alpha_parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "alpha_parser.hpp".  */
#ifndef YY_YY_ALPHA_PARSER_HPP_INCLUDED
# define YY_YY_ALPHA_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PARSE_EXPR = 258,
    INTCONST = 259,
    REALCONST = 260,
    STRINGCONST = 261,
    ID = 262,
    DOLLAR_IDENT = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    FOR = 267,
    FUNCTION = 268,
    RETURN = 269,
    BREAK = 270,
    CONTINUE = 271,
    AND = 272,
    NOT = 273,
    OR = 274,
    LOCAL = 275,
    TRUE = 276,
    FALSE = 277,
    NIL = 278,
    ASSIGNMENT = 279,
    PLUS = 280,
    MINUS = 281,
    MULTIPLICATION = 282,
    DIVISION = 283,
    MODULO = 284,
    EQUAL = 285,
    NOT_EQUAL = 286,
    PLUS_PLUS = 287,
    MINUS_MINUS = 288,
    GREATER_THAN = 289,
    LESS_THAN = 290,
    GREATER_OR_EQUAL = 291,
    LESS_OR_EQUAL = 292,
    EXCLAMATION_MARK = 293,
    TILDA = 294,
    AT = 295,
    SHARP = 296,
    QUESTION_MARK = 297,
    LEFT_BRACE = 298,
    RIGHT_BRACE = 299,
    LEFT_BRACKET = 300,
    RIGHT_BRACKET = 301,
    LEFT_PAREN = 302,
    RIGHT_PAREN = 303,
    LEFT_QUASI_QUOTE = 304,
    RIGHT_QUASI_QUOTE = 305,
    SEMICOLON = 306,
    COMMA = 307,
    COLON = 308,
    DOUBLE_COLON = 309,
    DOT = 310,
    DOT_DOT = 311,
    COMMENT_TOKEN = 312,
    BAD_TOKEN = 313,
    UMINUS = 314
  };
#endif
/* Tokens.  */
#define PARSE_EXPR 258
#define INTCONST 259
#define REALCONST 260
#define STRINGCONST 261
#define ID 262
#define DOLLAR_IDENT 263
#define IF 264
#define ELSE 265
#define WHILE 266
#define FOR 267
#define FUNCTION 268
#define RETURN 269
#define BREAK 270
#define CONTINUE 271
#define AND 272
#define NOT 273
#define OR 274
#define LOCAL 275
#define TRUE 276
#define FALSE 277
#define NIL 278
#define ASSIGNMENT 279
#define PLUS 280
#define MINUS 281
#define MULTIPLICATION 282
#define DIVISION 283
#define MODULO 284
#define EQUAL 285
#define NOT_EQUAL 286
#define PLUS_PLUS 287
#define MINUS_MINUS 288
#define GREATER_THAN 289
#define LESS_THAN 290
#define GREATER_OR_EQUAL 291
#define LESS_OR_EQUAL 292
#define EXCLAMATION_MARK 293
#define TILDA 294
#define AT 295
#define SHARP 296
#define QUESTION_MARK 297
#define LEFT_BRACE 298
#define RIGHT_BRACE 299
#define LEFT_BRACKET 300
#define RIGHT_BRACKET 301
#define LEFT_PAREN 302
#define RIGHT_PAREN 303
#define LEFT_QUASI_QUOTE 304
#define RIGHT_QUASI_QUOTE 305
#define SEMICOLON 306
#define COMMA 307
#define COLON 308
#define DOUBLE_COLON 309
#define DOT 310
#define DOT_DOT 311
#define COMMENT_TOKEN 312
#define BAD_TOKEN 313
#define UMINUS 314

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "alpha_parser.y" /* yacc.c:355  */

	int    			  intValue;
	unsigned		  unsignedValue;
	double 			  doubleValue;
	char*  			  stringValue;
	Object*			  ObjectValue;

#line 250 "alpha_parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ALPHA_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 267 "alpha_parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   988

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  223

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   118,   118,   121,   123,   124,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   157,   159,   160,   161,   162,   163,
     164,   165,   168,   171,   172,   173,   174,   175,   176,   180,
     181,   182,   184,   187,   192,   197,   202,   207,   210,   215,
     220,   224,   225,   226,   229,   231,   233,   237,   239,   243,
     247,   252,   253,   257,   260,   263,   264,   267,   268,   271,
     272,   279,   286,   287,   288,   292,   295,   296,   299,   305,
     309,   312,   315,   320,   323,   324,   325,   326,   327,   328,
     332,   336,   338,   342,   344,   348,   354,   356,   357,   360,
     362,   364,   366,   368,   375,   383,   384,   387,   390,   391,
     394,   395,   397,   398,   402,   403,   406,   409,   412
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PARSE_EXPR", "INTCONST", "REALCONST",
  "STRINGCONST", "ID", "DOLLAR_IDENT", "IF", "ELSE", "WHILE", "FOR",
  "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL",
  "TRUE", "FALSE", "NIL", "ASSIGNMENT", "PLUS", "MINUS", "MULTIPLICATION",
  "DIVISION", "MODULO", "EQUAL", "NOT_EQUAL", "PLUS_PLUS", "MINUS_MINUS",
  "GREATER_THAN", "LESS_THAN", "GREATER_OR_EQUAL", "LESS_OR_EQUAL",
  "EXCLAMATION_MARK", "TILDA", "AT", "SHARP", "QUESTION_MARK",
  "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", "RIGHT_BRACKET",
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_QUASI_QUOTE", "RIGHT_QUASI_QUOTE",
  "SEMICOLON", "COMMA", "COLON", "DOUBLE_COLON", "DOT", "DOT_DOT",
  "COMMENT_TOKEN", "BAD_TOKEN", "UMINUS", "$accept", "bogusStart",
  "program", "stmts", "stmt", "expr", "term", "assignexpr", "primary",
  "lvalue", "member", "call", "callsuffix", "normcall", "methodcall",
  "elist", "elistnotempty", "objelistnotempty", "commalist",
  "objcommalist", "argument", "objectdef", "objectdinner", "indexed",
  "commaindexed", "indexedelem", "block", "funcdef", "funcprefix",
  "funcname", "const", "idlist", "commaidlist", "formal", "ifprefix",
  "ifstmt", "elseprefix", "whilestart", "whilecond", "whilestmt",
  "forprefix", "forstmt", "returnstmt", "quasiquotes", "nonemptystmts",
  "objelistmulti", "quotedrules", "escape", "inline", "unparsed",
  "compiledstring", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

#define YYPACT_NINF -68

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-68)))

#define YYTABLE_NINF -123

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-123)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,   363,     2,   -68,   149,   -35,   -68,   -68,   -68,   -68,
     -68,    -9,   -68,    -7,    23,    21,    -5,    16,   465,    62,
     -68,   -68,   -68,   465,    -2,    -2,    24,     3,    26,    27,
     -68,   -22,   414,   363,   -68,    69,   -68,   596,   -68,   -68,
     -68,   383,   -68,   -32,   -68,   -68,   -68,    30,   -68,   363,
     -68,    31,   -68,    33,   -68,   -68,   -68,   210,   -68,   -68,
     -68,   -68,   -68,   -68,   596,   -68,   465,    28,   -68,   -68,
     -68,   623,   -68,   -68,   -68,   -68,   -68,    72,   -36,   -32,
     -36,   465,   -68,   465,   465,   465,   261,   -68,   465,    42,
     -68,    46,   677,    43,   596,   312,    38,    44,   -68,   465,
     465,   465,   465,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   -68,   465,   -68,   -68,   465,    33,    29,    85,
     -68,   -68,   -68,   465,    33,    48,    86,    87,   465,   363,
      63,   -68,   516,   -68,   701,    45,   -68,    65,   725,   749,
     773,   797,   -68,   568,   -68,   465,    64,   -68,    67,   465,
     -68,   938,   925,     6,     6,   -68,   -68,   -68,   951,   951,
     582,   582,   582,   582,   910,   845,    70,   -68,   -68,    73,
     867,    71,   -68,   -68,    75,   110,   -68,   363,   821,   -68,
     363,    68,   910,    74,   -68,   465,    67,   -68,   -68,   -68,
     -68,   -68,   547,   -68,    33,   910,   -68,   -68,    33,   -68,
     -68,    81,   101,    78,   -68,   -68,   -68,   465,   -68,   650,
     465,    88,    89,   -68,   465,   -68,   910,   -68,   889,   -68,
     -68,   910,   -68
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,     0,     0,     2,     0,     0,    94,    95,    96,    53,
      54,     0,   110,     0,    93,     0,     0,     0,     0,     0,
      98,    99,    97,     0,     0,     0,     0,     0,     0,     0,
       7,    78,     0,     0,    17,     0,   119,     4,    33,    19,
      41,    48,    57,    49,    50,    15,    16,     0,    52,     0,
       9,     0,    10,    76,    11,    12,    43,     0,    44,    45,
      46,    47,     1,     6,     0,    18,     0,    76,    92,    91,
     116,     0,    13,    14,    36,    55,    35,     0,    37,     0,
      39,     0,   124,     0,     0,     0,     0,    82,     0,     0,
      83,     0,     0,     0,   121,     0,   123,     0,    56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,    38,    40,     0,    76,     0,     0,
      65,    67,    68,     0,    76,     0,   101,   107,     0,     0,
       0,    71,     0,   118,     0,     0,   115,     0,     0,     0,
       0,     0,    89,    74,    81,     0,    85,    34,    51,     0,
     117,    31,    32,    20,    21,    22,    23,    24,    29,    30,
      25,    27,    26,    28,    42,     0,     0,    58,    59,     0,
       0,     0,    61,    62,     0,     0,   109,     0,     0,   112,
       0,    53,    79,    73,   106,     0,     0,   126,   125,   128,
     127,    77,     0,    86,    76,   120,    60,    69,    76,    63,
      64,     0,   104,   100,   108,   111,   114,     0,    75,     0,
       0,     0,     0,    90,     0,   102,    80,   113,     0,    66,
      70,   105,    88
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -68,   -68,   -68,   103,     0,    -1,   -68,   -68,   -68,   -17,
     -68,    39,   -68,   -68,   -68,   -66,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -67,   -29,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   102,   -68,   -68,   -68,   -68,   -68,
     -68
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    36,    64,    38,    39,    40,    41,
      42,    43,   120,   121,   122,   130,   131,    87,   132,    88,
     183,    44,    89,    90,    91,   146,    45,    46,    47,    69,
      48,   174,   175,   203,    49,    50,   177,    51,   129,    52,
      53,    54,    55,    56,    57,    96,    97,    58,    59,    60,
      61
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,   135,    62,    93,    63,     9,    10,    78,    80,   116,
      82,   117,     1,   123,    71,   124,    65,    74,    19,   118,
     119,   -87,    76,   125,   -84,     6,     7,     8,     9,    10,
      68,    92,    94,   103,   104,   105,   167,   168,    66,    18,
      67,    19,    20,    21,    22,    77,    72,    23,   137,   127,
      83,   166,    35,    24,    25,   172,   173,   133,   171,    26,
      27,    28,    29,    79,    79,   134,    31,    73,    32,    75,
      33,    81,    70,    84,    85,    35,    98,   126,   128,   -72,
     138,   -72,   139,   140,   141,    14,    63,   143,   144,   145,
     149,   148,   169,  -103,   150,   133,   185,   176,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   180,   164,   186,   194,   165,   193,   202,   197,   200,
     198,   207,   170,   201,    30,   214,   208,   178,   211,   179,
     215,   182,   212,    86,   213,    95,   219,   220,     0,     0,
       0,     0,     0,     0,   192,     0,     0,     0,   195,    -5,
       5,     0,     0,     6,     7,     8,     9,    10,    11,     0,
      12,    13,    14,    15,    16,    17,     0,    18,     0,    19,
      20,    21,    22,     0,     0,    23,     0,   204,     0,     0,
     206,    24,    25,     0,   209,     0,     0,    26,    27,    28,
      29,     0,    30,     0,    31,     0,    32,     0,    33,     0,
      34,     0,     0,    35,     0,     0,   216,     0,     0,   218,
      -3,     5,     0,   221,     6,     7,     8,     9,    10,    11,
       0,    12,    13,    14,    15,    16,    17,     0,    18,     0,
      19,    20,    21,    22,     0,     0,    23,     0,     0,     0,
       0,     0,    24,    25,     0,     0,     0,     0,    26,    27,
      28,    29,     0,    30,     0,    31,     0,    32,     0,    33,
       0,    34,     5,     0,    35,     6,     7,     8,     9,    10,
      11,     0,    12,    13,    14,    15,    16,    17,     0,    18,
       0,    19,    20,    21,    22,     0,     0,    23,     0,     0,
       0,     0,     0,    24,    25,     0,     0,     0,     0,    26,
      27,    28,    29,     0,    30,   142,    31,     0,    32,     0,
      33,     0,    34,     5,     0,    35,     6,     7,     8,     9,
      10,    11,     0,    12,    13,    14,    15,    16,    17,     0,
      18,     0,    19,    20,    21,    22,     0,     0,    23,     0,
       0,     0,     0,     0,    24,    25,     0,     0,     0,     0,
      26,    27,    28,    29,     0,    30,     0,    31,     0,    32,
       0,    33,  -122,    34,     5,     0,    35,     6,     7,     8,
       9,    10,    11,     0,    12,    13,    14,    15,    16,    17,
       0,    18,     0,    19,    20,    21,    22,     0,     0,    23,
       0,     0,     0,     0,     0,    24,    25,     0,     0,     0,
       0,    26,    27,    28,    29,     0,    30,   113,    31,     0,
      32,     0,    33,     0,    34,   114,   115,    35,     6,     7,
       8,     9,    10,     0,     0,     0,     0,    14,   116,     0,
     117,     0,    18,     0,    19,    20,    21,    22,   118,   119,
      23,     0,     0,     0,     0,     0,    24,    25,     0,     0,
       0,     0,    26,    27,    28,    29,     0,     0,     0,    31,
       0,    32,     0,    33,     0,     0,     0,     0,    35,     6,
       7,     8,     9,    10,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,    19,    20,    21,    22,     0,
       0,    23,     0,     0,     0,     0,     0,    24,    25,     0,
       0,     0,     0,    26,    27,    28,    29,     0,     0,     0,
      31,     0,    32,     0,    33,     0,     0,     0,     0,    35,
       6,     7,     8,   181,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,     0,    19,    20,    21,    22,
       0,     0,    23,     0,     0,     0,     0,     0,    24,    25,
       0,     0,     0,     0,    26,    27,    28,    29,     0,     0,
       0,    31,     0,    32,    99,    33,   100,     0,     0,     0,
      35,     0,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,    99,     0,   100,     0,     0,
       0,     0,     0,   101,   102,   103,   104,   105,   106,   107,
     210,     0,   108,   109,   110,   111,     0,   101,   102,   103,
     104,   105,     0,    99,     0,   100,  -123,  -123,  -123,  -123,
     191,   101,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
      99,     0,   100,     0,     0,     0,     0,   112,   101,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,    99,     0,   100,
       0,     0,     0,     0,   136,   101,   102,   103,   104,   105,
     106,   107,     0,     0,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,    99,     0,   100,     0,     0,     0,
       0,   217,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,    99,     0,
     100,     0,     0,     0,     0,   147,   101,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,    99,     0,   100,     0,     0,     0,     0,   184,
     101,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,    99,     0,   100,     0,
       0,     0,     0,   187,   101,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
      99,     0,   100,     0,     0,     0,     0,   188,   101,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,    99,     0,   100,     0,     0,     0,
       0,   189,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,    99,     0,
     100,     0,     0,     0,     0,   190,   101,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,    99,     0,   100,     0,     0,     0,     0,   205,
     101,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,    99,     0,   100,     0,     0,     0,
       0,   196,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,    99,     0,   100,     0,
       0,     0,     0,   199,   101,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,    99,     0,   100,
       0,     0,     0,   222,     0,   101,   102,   103,   104,   105,
     106,   107,    99,     0,   108,   109,   110,   111,     0,     0,
     101,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,   101,   102,   103,   104,   105,   106,   107,
       0,     0,   108,   109,   110,   111,   101,   102,   103,   104,
     105,  -123,  -123,     0,     0,   108,   109,   110,   111
};

static const yytype_int16 yycheck[] =
{
       1,    67,     0,    32,     4,     7,     8,    24,    25,    45,
       7,    47,     3,    45,    15,    47,    51,    18,    20,    55,
      56,    43,    23,    55,    46,     4,     5,     6,     7,     8,
       7,    32,    33,    27,    28,    29,     7,     8,    47,    18,
      47,    20,    21,    22,    23,    47,    51,    26,    77,    49,
      47,   117,    54,    32,    33,     7,     8,    57,   124,    38,
      39,    40,    41,    24,    25,    66,    45,    51,    47,     7,
      49,    47,    51,    47,    47,    54,     7,    47,    47,    51,
      81,    48,    83,    84,    85,    13,    86,    88,    46,    43,
      52,    48,     7,     7,    50,    95,    51,    10,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,    48,   113,    48,    47,   116,    52,     7,    48,    48,
      47,    53,   123,    48,    43,    24,    52,   128,   194,   129,
      52,   132,   198,    30,   201,    33,    48,    48,    -1,    -1,
      -1,    -1,    -1,    -1,   145,    -1,    -1,    -1,   149,     0,
       1,    -1,    -1,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    -1,    18,    -1,    20,
      21,    22,    23,    -1,    -1,    26,    -1,   177,    -1,    -1,
     180,    32,    33,    -1,   185,    -1,    -1,    38,    39,    40,
      41,    -1,    43,    -1,    45,    -1,    47,    -1,    49,    -1,
      51,    -1,    -1,    54,    -1,    -1,   207,    -1,    -1,   210,
       0,     1,    -1,   214,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    -1,    18,    -1,
      20,    21,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    47,    -1,    49,
      -1,    51,     1,    -1,    54,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    -1,    18,
      -1,    20,    21,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    -1,    43,    44,    45,    -1,    47,    -1,
      49,    -1,    51,     1,    -1,    54,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    -1,
      18,    -1,    20,    21,    22,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    -1,    43,    -1,    45,    -1,    47,
      -1,    49,    50,    51,     1,    -1,    54,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      -1,    18,    -1,    20,    21,    22,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    24,    45,    -1,
      47,    -1,    49,    -1,    51,    32,    33,    54,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    13,    45,    -1,
      47,    -1,    18,    -1,    20,    21,    22,    23,    55,    56,
      26,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    -1,    -1,    -1,    45,
      -1,    47,    -1,    49,    -1,    -1,    -1,    -1,    54,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    20,    21,    22,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    -1,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    -1,    -1,    54,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    18,    -1,    20,    21,    22,    23,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    -1,
      -1,    45,    -1,    47,    17,    49,    19,    -1,    -1,    -1,
      54,    -1,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    34,    35,    36,    37,    17,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    28,    29,    30,    31,
      53,    -1,    34,    35,    36,    37,    -1,    25,    26,    27,
      28,    29,    -1,    17,    -1,    19,    34,    35,    36,    37,
      52,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    -1,    19,    -1,    -1,    -1,    -1,    51,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,    19,
      -1,    -1,    -1,    -1,    51,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    -1,    19,    -1,    -1,    -1,
      -1,    51,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    34,    35,    36,    37,    -1,    -1,    -1,    17,    -1,
      19,    -1,    -1,    -1,    -1,    48,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    17,    -1,    19,    -1,    -1,    -1,    -1,    48,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    34,
      35,    36,    37,    -1,    -1,    -1,    17,    -1,    19,    -1,
      -1,    -1,    -1,    48,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,
      17,    -1,    19,    -1,    -1,    -1,    -1,    48,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    34,    35,    36,
      37,    -1,    -1,    -1,    17,    -1,    19,    -1,    -1,    -1,
      -1,    48,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    34,    35,    36,    37,    -1,    -1,    -1,    17,    -1,
      19,    -1,    -1,    -1,    -1,    48,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    17,    -1,    19,    -1,    -1,    -1,    -1,    48,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    34,
      35,    36,    37,    -1,    17,    -1,    19,    -1,    -1,    -1,
      -1,    46,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    34,    35,    36,    37,    -1,    17,    -1,    19,    -1,
      -1,    -1,    -1,    46,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    34,    35,    36,    37,    17,    -1,    19,
      -1,    -1,    -1,    44,    -1,    25,    26,    27,    28,    29,
      30,    31,    17,    -1,    34,    35,    36,    37,    -1,    -1,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    34,
      35,    36,    37,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    34,    35,    36,    37,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    34,    35,    36,    37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    61,    62,    63,     1,     4,     5,     6,     7,
       8,     9,    11,    12,    13,    14,    15,    16,    18,    20,
      21,    22,    23,    26,    32,    33,    38,    39,    40,    41,
      43,    45,    47,    49,    51,    54,    64,    65,    66,    67,
      68,    69,    70,    71,    81,    86,    87,    88,    90,    94,
      95,    97,    99,   100,   101,   102,   103,   104,   107,   108,
     109,   110,     0,    64,    65,    51,    47,    47,     7,    89,
      51,    65,    51,    51,    65,     7,    65,    47,    69,    71,
      69,    47,     7,    47,    47,    47,    63,    77,    79,    82,
      83,    84,    65,    87,    65,   104,   105,   106,     7,    17,
      19,    25,    26,    27,    28,    29,    30,    31,    34,    35,
      36,    37,    51,    24,    32,    33,    45,    47,    55,    56,
      72,    73,    74,    45,    47,    55,    47,    64,    47,    98,
      75,    76,    78,    64,    65,    75,    51,    87,    65,    65,
      65,    65,    44,    65,    46,    43,    85,    48,    48,    52,
      50,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    75,     7,     8,     7,
      65,    75,     7,     8,    91,    92,    10,    96,    65,    64,
      48,     7,    65,    80,    48,    51,    48,    48,    48,    48,
      48,    52,    65,    52,    47,    65,    46,    48,    47,    46,
      48,    48,     7,    93,    64,    48,    64,    53,    52,    65,
      53,    75,    75,    86,    24,    52,    65,    51,    65,    48,
      48,    65,    44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    61,    61,    62,    63,    63,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    69,    69,    69,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    72,    72,    73,
      74,    75,    75,    76,    77,    78,    78,    79,    79,    80,
      80,    81,    82,    82,    82,    83,    84,    84,    85,    86,
      87,    88,    89,    89,    90,    90,    90,    90,    90,    90,
      91,    91,    92,    92,    93,    93,    94,    95,    95,    96,
      97,    98,    99,   100,   101,   102,   102,   103,   104,   104,
     105,   105,   106,   106,   107,   107,   108,   109,   110
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     2,     0,     2,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     2,     2,     2,     2,     2,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     2,     2,     1,     3,     3,
       4,     3,     3,     4,     4,     2,     6,     1,     1,     3,
       5,     1,     0,     2,     2,     3,     0,     3,     0,     1,
       3,     3,     1,     1,     0,     2,     3,     0,     5,     3,
       5,     2,     1,     0,     1,     1,     1,     1,     1,     1,
       2,     0,     3,     0,     1,     3,     4,     2,     4,     1,
       1,     3,     3,     6,     4,     3,     2,     3,     2,     1,
       3,     1,     1,     1,     2,     4,     4,     4,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 6: /* STRINGCONST  */
#line 96 "alpha_parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).stringValue)); }
#line 1417 "alpha_parser.cpp" /* yacc.c:1257  */
        break;

    case 7: /* ID  */
#line 97 "alpha_parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).stringValue)); }
#line 1423 "alpha_parser.cpp" /* yacc.c:1257  */
        break;

    case 8: /* DOLLAR_IDENT  */
#line 98 "alpha_parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).stringValue)); }
#line 1429 "alpha_parser.cpp" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 118 "alpha_parser.y" /* yacc.c:1646  */
    {__astRoot = (yyvsp[0].ObjectValue);}
#line 1693 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 118 "alpha_parser.y" /* yacc.c:1646  */
    {__astRoot = (yyvsp[0].ObjectValue);}
#line 1699 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 118 "alpha_parser.y" /* yacc.c:1646  */
    {__astRoot = (yyvsp[0].ObjectValue);}
#line 1705 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 121 "alpha_parser.y" /* yacc.c:1646  */
    {(yyval.ObjectValue) = Manage_program((yyvsp[0].ObjectValue));}
#line 1711 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 123 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmts_stmtsR_stmt((yyvsp[-1].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 1717 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 124 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmts(); }
#line 1723 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 126 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_expr_SEMICOLON((yyvsp[-1].ObjectValue)); }
#line 1729 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 127 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_ifstmt((yyvsp[0].ObjectValue)); }
#line 1735 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 128 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_whilestmt((yyvsp[0].ObjectValue)); }
#line 1741 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 129 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_forstmt((yyvsp[0].ObjectValue)); }
#line 1747 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 130 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_returnstmt((yyvsp[0].ObjectValue)); }
#line 1753 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 131 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_BREAK_SEMICOLON(); }
#line 1759 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 132 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_CONTINUE(); }
#line 1765 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 133 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_block((yyvsp[0].ObjectValue)); }
#line 1771 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 134 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_funcdef((yyvsp[0].ObjectValue)); }
#line 1777 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 135 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_SEMICOLON(); }
#line 1783 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 136 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmt_default(); yyerrok; }
#line 1789 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 140 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_assignexpr((yyvsp[0].ObjectValue)); }
#line 1795 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 141 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].ObjectValue), "+", (yyvsp[0].ObjectValue)); }
#line 1801 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 142 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].ObjectValue), "-", (yyvsp[0].ObjectValue)); }
#line 1807 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 143 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].ObjectValue), "*", (yyvsp[0].ObjectValue)); }
#line 1813 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 144 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].ObjectValue), "/", (yyvsp[0].ObjectValue)); }
#line 1819 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 145 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].ObjectValue), "%", (yyvsp[0].ObjectValue)); }
#line 1825 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 146 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].ObjectValue), ">", (yyvsp[0].ObjectValue)); }
#line 1831 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 147 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].ObjectValue), ">=", (yyvsp[0].ObjectValue)); }
#line 1837 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 148 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].ObjectValue), "<", (yyvsp[0].ObjectValue)); }
#line 1843 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 149 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].ObjectValue), "<=", (yyvsp[0].ObjectValue)); }
#line 1849 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 150 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].ObjectValue), "==", (yyvsp[0].ObjectValue)); }
#line 1855 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 151 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].ObjectValue), "!=", (yyvsp[0].ObjectValue)); }
#line 1861 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 152 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_AND_exprR((yyvsp[-2].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 1867 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 153 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_exprL_OR_exprR((yyvsp[-2].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 1873 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 154 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_expr_term((yyvsp[0].ObjectValue)); }
#line 1879 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 157 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_term_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].ObjectValue));}
#line 1885 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 159 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_term_MINUS_expr((yyvsp[0].ObjectValue)); }
#line 1891 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 160 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_term_NOT_expr((yyvsp[0].ObjectValue)); }
#line 1897 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 161 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_term_PLUS_PLUS_lvalue((yyvsp[0].ObjectValue)); }
#line 1903 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 162 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_term_lvalue_PLUS_PLUS((yyvsp[-1].ObjectValue)); }
#line 1909 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 163 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_term_MINUS_MINUS_lvalue((yyvsp[0].ObjectValue)); }
#line 1915 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 164 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_term_lvalue_MINUS_MINUS((yyvsp[-1].ObjectValue)); }
#line 1921 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 165 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_term_primary((yyvsp[0].ObjectValue));}
#line 1927 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 168 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_assignexpr_lvalue_ASSIGNMENT_expr((yyvsp[-2].ObjectValue),(yyvsp[0].ObjectValue)); }
#line 1933 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 171 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_primary_quasiquotes((yyvsp[0].ObjectValue)); }
#line 1939 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 172 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_primary_escape((yyvsp[0].ObjectValue)); }
#line 1945 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 173 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_primary_inline((yyvsp[0].ObjectValue)); }
#line 1951 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 174 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_primary_unparsed((yyvsp[0].ObjectValue)); }
#line 1957 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 175 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_primary_compiledstring((yyvsp[0].ObjectValue)); }
#line 1963 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 177 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_primary_lvalue((yyvsp[0].ObjectValue));
				}
#line 1971 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 180 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_primary_call((yyvsp[0].ObjectValue)); }
#line 1977 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 181 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_primary_objectdef((yyvsp[0].ObjectValue)); }
#line 1983 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 183 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_primary_LEFT_PAREN_funcdef_RIGHT_PAREN((yyvsp[-1].ObjectValue)); }
#line 1989 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 184 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) =  Manage_primary_const((yyvsp[0].ObjectValue));}
#line 1995 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 188 "alpha_parser.y" /* yacc.c:1646  */
    {			
					(yyval.ObjectValue) = Manage_lvalue_ID((yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 2004 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 193 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_lvalue_ID((yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 2013 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 198 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_lvalue_LOCAL_ID((yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 2022 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 203 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_lvalue_DOUBLE_COLON_ID((yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 2031 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 207 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_lvalue_member((yyvsp[0].ObjectValue)); }
#line 2037 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 211 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_member_lvalue_DOT_ID((yyvsp[-2].ObjectValue), (yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 2046 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 216 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_lvalue_DOT_DOLLAR_IDENT((yyvsp[-2].ObjectValue), (yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 2055 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 221 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_member_lvalue_LEFT_BRACKET_expr_RIGHT_BRACKET((yyvsp[-3].ObjectValue), (yyvsp[-1].ObjectValue));
				}
#line 2063 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 224 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_member_call_DOT_ID((yyvsp[-2].ObjectValue), (yyvsp[0].stringValue)); free((yyvsp[0].stringValue)); }
#line 2069 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 225 "alpha_parser.y" /* yacc.c:1646  */
    {(yyval.ObjectValue) = Manage_call_DOT_DOLLAR_IDENT((yyvsp[-2].ObjectValue), (yyvsp[0].stringValue)); free((yyvsp[0].stringValue));}
#line 2075 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 226 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_member_call_LEFT_BRACKET_expr_RIGHT_BRACKET((yyvsp[-3].ObjectValue), (yyvsp[-1].ObjectValue)); }
#line 2081 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 230 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_call_callRight_LEFT_PAREN_elist_RIGHT_PAREN((yyvsp[-3].ObjectValue), (yyvsp[-1].ObjectValue)); }
#line 2087 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 232 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_call_lvalue_callsuffix((yyvsp[-1].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2093 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 234 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_LEFT_PAREN_funcdef_RIGHT_PAREN_LEFT_PAREN_elist_RIGHT_PAREN((yyvsp[-4].ObjectValue), (yyvsp[-1].ObjectValue)); }
#line 2099 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 238 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_callsuffix_normcall((yyvsp[0].ObjectValue)); }
#line 2105 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 240 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_callsuffix_methodcall((yyvsp[0].ObjectValue)); }
#line 2111 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 244 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_normcall_LEFT_PAREN_elist_RIGHT_PAREN((yyvsp[-1].ObjectValue)); }
#line 2117 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 248 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_methodcall_DOT_DOT_ID_LEFT_PAREN_elist_RIGHT_PAREN((yyvsp[-3].stringValue), (yyvsp[-1].ObjectValue)); free((yyvsp[-3].stringValue));}
#line 2123 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 252 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_elist_elistnotempty((yyvsp[0].ObjectValue)); }
#line 2129 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 253 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_elist(); }
#line 2135 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 257 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_commalist_COMMA_argument_commalist((yyvsp[-1].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2141 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 260 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_objelistnotempty_COMMA_expr_objcommalist((yyvsp[-1].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2147 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 263 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_commalist_COMMA_argument_commalist((yyvsp[-2].ObjectValue), (yyvsp[-1].ObjectValue)); }
#line 2153 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 264 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_commalist(); }
#line 2159 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 267 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_objelistnotempty_COMMA_expr_objcommalist((yyvsp[-2].ObjectValue), (yyvsp[-1].ObjectValue)); }
#line 2165 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 268 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_objcommalist(); }
#line 2171 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 271 "alpha_parser.y" /* yacc.c:1646  */
    {(yyval.ObjectValue) = Manage_argument_expr((yyvsp[0].ObjectValue));}
#line 2177 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 272 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_argument_ID_COLON_expr((yyvsp[-2].stringValue), (yyvsp[0].ObjectValue));
					free((yyvsp[-2].stringValue));
				}
#line 2186 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 280 "alpha_parser.y" /* yacc.c:1646  */
    { 
					(yyval.ObjectValue) = Manage_objectdef_LEFT_BRACKET_objectdinner_RIGHT_BRACKET((yyvsp[-1].ObjectValue)); 
				}
#line 2194 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 286 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_objectdinner_objelistnotempty((yyvsp[0].ObjectValue)); }
#line 2200 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 287 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_objectdinner_indexed((yyvsp[0].ObjectValue)); }
#line 2206 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 288 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_objectdinner(); }
#line 2212 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 292 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_commaindexed_COMMA_indexedelem_commaindexed((yyvsp[-1].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2218 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 295 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_commaindexed_COMMA_indexedelem_commaindexed((yyvsp[-2].ObjectValue), (yyvsp[-1].ObjectValue)); }
#line 2224 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 296 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_commaindexed(); }
#line 2230 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 300 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_indexedelem_LEFT_BRACE_expr_COLON_expr_RIGHT_BRACE((yyvsp[-3].ObjectValue), (yyvsp[-1].ObjectValue));
				}
#line 2238 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 305 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_block_LEFT_BRACE_stmts_RIGHT_BRACE((yyvsp[-1].ObjectValue)); }
#line 2244 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 309 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_funcdef_funcprefix_LEFT_PAREN_idlist_RIGHT_PAREN_block((yyvsp[-4].ObjectValue), (yyvsp[-2].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2250 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 312 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_funcprefix_FUNCTION_funcname((yyvsp[0].ObjectValue)); }
#line 2256 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 316 "alpha_parser.y" /* yacc.c:1646  */
    { 
					(yyval.ObjectValue) = Manage_funcname_ID((yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 2265 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 320 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_funcname(); }
#line 2271 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 323 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_const_numconst((yyvsp[0].intValue));}
#line 2277 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 324 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_const_numconst((yyvsp[0].doubleValue));}
#line 2283 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 325 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_const_strconst((yyvsp[0].stringValue)); free((yyvsp[0].stringValue));}
#line 2289 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 326 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_const_nil();}
#line 2295 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 327 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_const_boolconst(true);}
#line 2301 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 328 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_const_boolconst(false);}
#line 2307 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 333 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_commaidlist_formal_COMMA((yyvsp[-1].ObjectValue), (yyvsp[0].ObjectValue));
				}
#line 2315 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 336 "alpha_parser.y" /* yacc.c:1646  */
    {(yyval.ObjectValue) = Manage_idlist();}
#line 2321 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 339 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_commaidlist_formal_COMMA((yyvsp[-2].ObjectValue), (yyvsp[-1].ObjectValue)); 
				}
#line 2329 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 342 "alpha_parser.y" /* yacc.c:1646  */
    {(yyval.ObjectValue) = Manage_commaidlist();}
#line 2335 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 344 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_formal_ID((yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 2344 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 348 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_formal_ID_ASSIGNMENT_expr((yyvsp[-2].stringValue), (yyvsp[0].ObjectValue));
					free((yyvsp[-2].stringValue));
				}
#line 2353 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 354 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_ifprefix_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].ObjectValue)); }
#line 2359 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 356 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_ifstmt_ifprefix_stmt((yyvsp[-1].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2365 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 357 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_ifstmt_ifprefix_stmt_elseprefix_stmt((yyvsp[-3].ObjectValue), (yyvsp[-1].ObjectValue), (yyvsp[-2].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2371 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 360 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_elseprefix_ELSE(); }
#line 2377 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 362 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_whilestart_WHILE(); }
#line 2383 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 364 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) =  Manage_whilecond_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].ObjectValue)); }
#line 2389 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 366 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_while_whilestart_whilecond_stmt((yyvsp[-2].ObjectValue), (yyvsp[-1].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2395 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 369 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.ObjectValue) = Manage_forprefix_FOR_LEFT_PAREN_elist_SEMICOLON_expr_SEMICOLON((yyvsp[-3].ObjectValue), (yyvsp[-1].ObjectValue));
					
				}
#line 2404 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 376 "alpha_parser.y" /* yacc.c:1646  */
    { 
					(yyval.ObjectValue) = Manage_forstmt_forprefix_elist_RIGHT_PAREN_stmt((yyvsp[-3].ObjectValue), (yyvsp[-2].ObjectValue), (yyvsp[0].ObjectValue));
					 
				}
#line 2413 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 383 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_returnstmt_RETURN_expr_SEMICOLON((yyvsp[-1].ObjectValue)); }
#line 2419 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 384 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_returnstmt_RETURN_SEMICOLON(); }
#line 2425 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 387 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_quasiquotes_LEFT_QUASI_QUOTE_quotedrules_RIGHT_QUASI_QUOTE((yyvsp[-1].ObjectValue)); }
#line 2431 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 390 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmts_stmtsR_stmt((yyvsp[-1].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2437 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 391 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_stmts_stmtsR_stmt(nullptr, (yyvsp[0].ObjectValue)); }
#line 2443 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 394 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_objelistnotempty_COMMA_expr_objcommalist((yyvsp[-2].ObjectValue), (yyvsp[0].ObjectValue)); }
#line 2449 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 395 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_objelistnotempty_COMMA_expr_objcommalist(nullptr, (yyvsp[0].ObjectValue)); }
#line 2455 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 397 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_quotedrules((yyvsp[0].ObjectValue)); }
#line 2461 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 398 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_quotedrules((yyvsp[0].ObjectValue)); }
#line 2467 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 402 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_escape_TILDA_ID((yyvsp[0].stringValue)); free((yyvsp[0].stringValue)); }
#line 2473 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 403 "alpha_parser.y" /* yacc.c:1646  */
    {(yyval.ObjectValue) = Manage_escape_TILDA_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].ObjectValue)); }
#line 2479 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 406 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_inline_EXCLAMATION_MARK_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].ObjectValue)); }
#line 2485 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 409 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_unparsed_SHARP_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].ObjectValue)); }
#line 2491 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 412 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.ObjectValue) = Manage_compiledstring_AT_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].ObjectValue)); }
#line 2497 "alpha_parser.cpp" /* yacc.c:1646  */
    break;


#line 2501 "alpha_parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 414 "alpha_parser.y" /* yacc.c:1906  */



int yyerror(char * yaccProvidedMessage) {
 	error(ErrorType::Error, yylineno, "%s before token " BON "\'%s\'" BOFF "\n", yaccProvidedMessage, yytext);
	return 0;
}

