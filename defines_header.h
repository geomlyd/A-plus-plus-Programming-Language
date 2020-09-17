#ifndef DEFINES_HEADER_H
#define DEFINES_HEADER_H
#include "alpha_yyFlexLexer.h"
extern alpha_yyFlexLexer * lexer;
#define yylineno lexer->getLineNo()
#define yytext lexer->getYyText()
#endif
