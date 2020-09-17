/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 23 "alpha_parser.y" /* yacc.c:1909  */

	int    			  intValue;
	unsigned		  unsignedValue;
	double 			  doubleValue;
	char*  			  stringValue;
	Object*			  ObjectValue;

#line 180 "alpha_parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ALPHA_PARSER_HPP_INCLUDED  */
