%{
	#if defined(WIN32)
	#define YY_NO_UNISTD_H
	static int isatty(int i) { return 0;}
	#elif defined(_WIN32_WCE)
	#define YY_NO_UNISTD_H
	static int isatty(void *i) {return 0;}
	#endif
	
	#include <stdlib.h>
	#include <fstream>
	#include <stack>
	#include <sstream>
	#include "alpha_yyFlexLexer.h"
	#include "Object.h"
	#include "alpha_parser.hpp"
	#include "error_handler.h"

	#define CR "\x1b[0m"
  	#define RED "\x1b[31m"
  	#define YELLOW "\x1b[33m"
  	#define CYAN "\x1b[36m"
  	#define GREEN "\x1b[32m"
  	#define BON "\e[1m"
	#define BOFF "\e[0m"
  	//#define DEBUG
  	//#define STRCAT
%}

%option c++
%option yyclass = "alpha_yyFlexLexer"
%option outfile = "alpha_lexer.cpp"
%option yylineno
%option noyywrap

id 				[a-zA-Z][a-zA-Z_0-9]*
integer 		((0[xX][0-9A-Fa-f]+)|([0-9]+))
real 			(([0-9]+\.[0-9]*)|([0-9]*\.[0-9]+))((e|E)([-+]?)[0-9]+)?    
space 			[\r \t\v]
newline 		\n
line_comment	"//".*
dollar_ident	[$]{id}

%%

{space}

{newline}


{integer}				{
							#ifdef DEBUG
							addToken(yytext, INTCONST, NO_SUBTYPE);							
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized integer with value: %ld\n", strtol(yytext, NULL, 0));
							#endif
							yylval.intValue = atoi(yytext);
							return INTCONST;
						}
{real}					{
							#ifdef DEBUG	
							addToken(yytext, REALCONST, NO_SUBTYPE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized real with value: %f\n", atof(yytext));
							#endif
							yylval.doubleValue = atof(yytext);
							return REALCONST;

						}
if 						{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, IF);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return IF;

						}
else 					{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, ELSE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return ELSE;

						}
while 					{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, WHILE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return WHILE;

						}
for 					{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, FOR);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return FOR;

						}
function 				{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, FUNCTION);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return FUNCTION;

						}
return 					{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, RETURN);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return RETURN;

						}
break 					{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, BREAK);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return BREAK;

						}
continue 				{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, CONTINUE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return CONTINUE;
						}
and 					{
							#ifdef DEBUG	
							addToken(yytext, KEYWORD, AND);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return AND;

						}
not 					{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, NOT);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return NOT;

						}
or 						{
							#ifdef DEBUG	
							addToken(yytext, KEYWORD, OR);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return OR;

						}
local 					{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, LOCAL);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return LOCAL;
						}
true 					{
							#ifdef DEBUG	
							addToken(yytext, KEYWORD, TRUE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return TRUE;

						}
false 					{
							#ifdef DEBUG	
							addToken(yytext, KEYWORD, FALSE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return FALSE;
						}
nil 					{
							#ifdef DEBUG
							addToken(yytext, KEYWORD, NIL);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return NIL;
						}
"+"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,PLUS);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return PLUS;

						}
"-"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,MINUS);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return MINUS;

						}
"="						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,ASSIGNMENT)
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return ASSIGNMENT;

						}
"*"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,MULTIPLICATION);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return MULTIPLICATION;

						}
"/"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,DIVISION);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return DIVISION;

						}
"%"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,MODULO);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return MODULO;

						}
"=="					{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,EQUAL);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return EQUAL;

						}
"!="					{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,NOT_EQUAL);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return NOT_EQUAL;

						}
"++"					{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,PLUS_PLUS);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return PLUS_PLUS;

						}
"--"					{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,MINUS_MINUS);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return MINUS_MINUS;

						}
">"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,GREATER_THAN);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return GREATER_THAN;

						}
"<"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,LESS_THAN);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return LESS_THAN;

						}
">="					{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,GREATER_OR_EQUAL);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return GREATER_OR_EQUAL;

						}
"<="					{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,LESS_OR_EQUAL);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return LESS_OR_EQUAL;

						}
"!"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,EXCLAMATION_MARK);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return EXCLAMATION_MARK;
						}
"~"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,TILDA);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return TILDA;
						}
"@"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,AT);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return AT;
						}
"#"						{
							#ifdef DEBUG
							addToken(yytext,OPERATOR,SHARP);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return SHARP;
						}													
"{"						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,LEFT_BRACE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return LEFT_BRACE;

						}
"}"						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,RIGHT_BRACE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return RIGHT_BRACE;

						}
"["						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,LEFT_BRACKET);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return LEFT_BRACKET;

						}
"]"						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,RIGHT_BRACKET);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return RIGHT_BRACKET;

						}
"("						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,LEFT_PAREN);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return LEFT_PAREN;

						}
")"						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,RIGHT_PAREN);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return RIGHT_PAREN;

						}
"<<"					{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,LEFT_QUASI_QUOTE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return LEFT_QUASI_QUOTE;
						}
">>"					{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,RIGHT_QUASI_QUOTE);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return RIGHT_QUASI_QUOTE;
						}
";"						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,SEMICOLON);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return SEMICOLON;

						}
","						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,COMMA);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return COMMA;

						}
":"						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,COLON);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return COLON;

						}
"::"					{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,DOUBLE_COLON);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return DOUBLE_COLON;

						}
"."						{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,DOT);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return DOT;

						}
".."					{
							#ifdef DEBUG
							addToken(yytext,PUNCTUATION,DOT_DOT);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return DOT_DOT;

						}

"?"						{
							#ifdef DEBUG
							addToken(yytext, PUNCTUATION, QUESTION_MARK);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return QUESTION_MARK;
						}

{line_comment}			{ 
							#ifdef DEBUG
							addToken("",COMMENT,LINE_COMMENT);
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized comment with value: %s\n", yytext);
							#endif
							return COMMENT_TOKEN;
						}
{id} 					{	
							#ifdef DEBUG
							addToken(yytext, ID, NO_SUBTYPE);							
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized id with value: %s\n", yytext);
							#endif
							yylval.stringValue = strdup(yytext);
							return ID;
						}

{dollar_ident}			{	
							#ifdef DEBUG
							addToken(yytext, DOLLAR_IDENT, NO_SUBTYPE);							
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized dollar_ident with value: %s\n", yytext);
							#endif
							yylval.stringValue = strdup(yytext);
							return DOLLAR_IDENT;
						}

"/*"					{
							std::string dacc = "/*";
							std::stack<int> s = std::stack<int>();
                    		s.push(yylineno);
                    		while (!s.empty()) {
                        		int c = yyinput();
                        		dacc += c;
                        		if (c == 0 || c == EOF) {
                            		while (!s.empty()) {
                            			/* fprintf(stderr, RED "ERROR" CR ": Unclosed comment, starting on line: %d\n", s.top()); */
                            			error(ErrorType::Error, s.top(), "Unclosed comment\n");
                            			s.pop();
                            		}
                            		return BAD_TOKEN;
                        		}
                        		else if (c == '*') {
                            		if ((c = yyinput()) == '/') {
                            			dacc += c;               		
                                		s.pop();
                                		#ifdef DEBUG
                                		int startno = s.top();
                                		std::stringstream os;
                                		os << startno << " - " << yylineno;
                                		addToken(os.str().c_str(), COMMENT, BLOCK_COMMENT, startno);
                                		#endif
                            		} else {
                                		unput(c);
                            		}	
                        		}
                        		else if (c == '/') {
                            		if ((c = yyinput()) == '*') {
                            			dacc += c;
                                		s.push(yylineno);
                            		} else {
                                		unput(c);
                            		}
                        		}
                    		}
							#ifdef DEBUG
                    		fprintf(stderr, CYAN "DEBUG" CR ":Recognized block comment with value: %s\n", dacc.c_str());
							#endif
							return COMMENT_TOKEN;
                    	}

\"						{
							std::vector<char> my_yytext; 
							int curr = 0, tmp = 0, flag = 1, prop_closed = 0, ignore_white_space = 0;
							
							int	init_line_no = yylineno;
							while ((curr = yyinput()) != 0 && curr != EOF) {						
								if (curr == '\"') {	
									ignore_white_space = 0;								
									std::string my_yytext_for_real;
									for (auto i : my_yytext) my_yytext_for_real += i;										
									if (flag) {
										#ifdef DEBUG										
										addToken(my_yytext_for_real.c_str(), STRING, NO_SUBTYPE, init_line_no);
										fprintf(stderr, CYAN "DEBUG" CR ":Recognized string with value: %s\n", my_yytext_for_real.c_str());
										#endif
										yylval.stringValue = strdup(my_yytext_for_real.c_str());
										return STRINGCONST;
									}
									prop_closed = 1;	
									break;															
								}
								else if (curr == '\\') {
									ignore_white_space = 0;
									tmp = yyinput();
									switch(tmp) {
										case 'n':
											my_yytext.push_back('\n');
											break;
										case 'v':
											my_yytext.push_back('\v');
											break;
										case 'r':
											my_yytext.push_back('\r');
											break; 
										case 't':
											my_yytext.push_back('\t'); 
											break;
										case '\\':
											my_yytext.push_back('\\');
											break;
										case '\"':
											my_yytext.push_back('\"');
											break;
										default:
											/* fprintf(stderr, RED "ERROR" CR ":Invalid escape character at line %d\n", yylineno); */
											error(ErrorType::Error, yylineno, "Invalid escape character " BON "\'\\%c\'" BOFF "\n", tmp);
											flag = 0;
									}
								}
								#ifdef STRCAT
								else if (curr == '\n') {
									ignore_white_space = 1;
								}
								#endif 
								else if (!ignore_white_space || (curr != ' ' && curr != '\t')) {
									ignore_white_space = 0;
									my_yytext.push_back(curr);
								}
							}
							if (!prop_closed) {
								/* fprintf(stderr, RED "ERROR" CR ":String opened at line %d but was not closed at line %d\n", init_line_no, yylineno); */
								error(ErrorType::Error, init_line_no, "Unclosed string\n");
							}
							return BAD_TOKEN;
						}

.				{ 
					/* fprintf(stderr, RED "ERROR" CR ":Cannot match character '%s', at line %d, with any rule!\n", yytext, yylineno); */
					error(ErrorType::Error, yylineno, "Stray " BON "\'%s\'" BOFF " in program\n", yytext);
					return BAD_TOKEN;
				}

%%
