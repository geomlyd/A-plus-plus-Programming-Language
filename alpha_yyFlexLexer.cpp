#include "alpha_yyFlexLexer.h"
#include "Object.h"
#ifndef PHASE1
#include "function_actions.h"
#include "alpha_parser.hpp"
#endif
#include <sstream>
#include <string>
#include <iomanip>

std::string supertype_names[] = { "INVALID_TOKEN_TYPE", "KEYWORD", "OPERATOR", "INTCONST", "REALCONST", "STRING", "PUNCTUATION", "ID", "COMMENT", "DOLLAR_IDENT", "SPECIAL_TOKEN" };
std::string subtype_names[] = {
	"NO_SUBTYPE",
	/*KEYWORDS*/
	"IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL",
	"TRUE", "FALSE", "NIL",
	/*OPERATORS*/
	"ASSIGNMENT", "PLUS", "MINUS", "MULTIPLICATION", "DIVISION", "MODULO", "EQUAL", "NOT_EQUAL",
	"PLUS_PLUS", "MINUS_MINUS", "GREATER_THAN", "LESS_THAN", "GREATER_OR_EQUAL",
	"LESS_OR_EQUAL", "EXCLAMATION_MARK", "TILDA", "AT", "SHARP", "QUESTION_MARK",
	/*PUNCTUATIONS*/
	"LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_PAREN", "RIGHT_PAREN",
	"LEFT_QUASI_QUOTE", "RIGHT_QUASI_QUOTE","SEMICOLON", "COMMA", "COLON", "DOUBLE_COLON", "DOT", "DOT_DOT",
	/*COMMENTS*/
	"BLOCK_COMMENT", "LINE_COMMENT",
	/*SPECIAL TOKENS*/
	"PARSE_EXPR"
};

#ifdef PHASE1
std::string tokenToString(alpha_token_t t) {	
	std::stringstream os;
	std::string tmp1, tmp2, tmp3;
	tmp1 += std::to_string(std::get<0>(t));
	tmp1 += ":";
	tmp2 += "\"" + std::get<2>(t)  + "\"";
	os << std::left << std::setw(5) << tmp1 << "  " << "#" << std::setw(5) << std::get<1>(t) << "  " << std::setw(15) << tmp2 <<  std::setw(15) << supertype_names[std::get<3>(t)] << "  ";
	switch (std::get<3>(t)) {
		case(alpha_types::supertype_enum::INTCONST):
			os <<  std::left << std::setw(15) << strtol(std::get<2>(t).c_str(), NULL, 0) << "<- integer" << std::endl;
			break;
		case(alpha_types::supertype_enum::REALCONST):
			os << std::left << std::setw(15) << atof(std::get<2>(t).c_str()) << "<- double" << std::endl;
			break;
		case(alpha_types::supertype_enum::STRING):			
			tmp3 += "\"" + std::get<2>(t) + "\"";
			os << std::left << std::setw(15) <<tmp3 << "<- std::string" << std::endl;
			break;
		case(alpha_types::supertype_enum::ID):
			tmp3 += "\"" + std::get<2>(t) + "\"";
			os << std::left << std::setw(15) <<tmp3 << "<- std::string" << std::endl;
			break;
		default:
			os << std::left << std::setw(15) << subtype_names[std::get<4>(t)] << "<- enumerated" << std::endl;
	}
	return os.str();
}
#endif

#ifdef LATEST_AND_GREATEST
alpha_yyFlexLexer::alpha_yyFlexLexer(std::istream& is, std::ostream& os) : yyFlexLexer(is, os){
	tokens = std::vector<alpha_token_t>();
	numberOfTokens = 0;
}
#endif

alpha_yyFlexLexer::alpha_yyFlexLexer(std::istream * is, std:: ostream * os, bool _useForEval) : yyFlexLexer(is, os){
	useForEval = _useForEval;
	firstToken = true;
	tokens = std::vector<alpha_token_t>();
	numberOfTokens = 0;
}

int alpha_yyFlexLexer::alpha_yylex() {
	int result;
	if(useForEval && firstToken){
		firstToken = false;
		return PARSE_EXPR;
	}
	while ((result = yylex()) == COMMENT_TOKEN || result == BAD_TOKEN);
	return result;
}

#ifdef PHASE1
void alpha_yyFlexLexer::printer() {
	std::string acc = "";
	acc  += "Line#  Token#  Token	      Type	       Subtype	      C++ type\n";
	for (alpha_token_t t : tokens) {
		acc += tokenToString(t);
	}
	LexerOutput(acc.c_str(), acc.length());
}
#endif

void alpha_yyFlexLexer::addToken(const char * content, alpha_types::supertype_enum supertype, alpha_types::subtype_enum subtype, int lineno) {
	alpha_token_t temp = std::make_tuple(lineno == -1 ? yylineno : lineno, ++numberOfTokens, std::string(content), supertype, subtype);
	tokens.push_back(temp);
}

int alpha_yyFlexLexer::getLineNo(){
	return yylineno;
}

char *alpha_yyFlexLexer::getYyText(){
	return yytext;
}