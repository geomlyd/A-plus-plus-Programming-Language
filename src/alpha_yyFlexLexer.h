#ifndef ALPHA_YYFLEXLEXER_H
#define ALPHA_YYFLEXLEXER_H

#include <string>
#include <tuple>
#include <vector>
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#include <stdlib.h>
#endif

#define CR "\x1b[0m"
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define GREEN "\x1b[32m"
//#define PHASE1

//#define LATEST_AND_GREATEST
namespace alpha_types {
	enum supertype_enum {
		INVALID_TOKEN_TYPE=0, KEYWORD, OPERATOR, INTCONST, REALCONST, STRING, PUNCTUATION, ID, COMMENT, DOLLAR_IDENT
	};
	enum subtype_enum {
		NO_SUBTYPE=0,
		/*KEYWORDS*/
		IF, ELSE, WHILE, FOR, FUNCTION, RETURN, BREAK, CONTINUE, AND, NOT, OR, LOCAL, 
		TRUE, FALSE, NIL,
		/*OPERATORS*/
		ASSIGNMENT, PLUS, MINUS, MULTIPLICATION, DIVISION, MODULO, EQUAL, NOT_EQUAL, 
		PLUS_PLUS, MINUS_MINUS, GREATER_THAN, LESS_THAN, GREATER_OR_EQUAL, 
		LESS_OR_EQUAL, EXCLAMATION_MARK, TILDA, AT, SHARP, QUESTION_MARK,
		/*PUNCTUATIONS*/
		LEFT_BRACE, RIGHT_BRACE, LEFT_BRACKET, RIGHT_BRACKET, LEFT_PAREN, RIGHT_PAREN,
		LEFT_QUASI_QUOTE, RIGHT_QUASI_QUOTE, SEMICOLON, COMMA, COLON, DOUBLE_COLON, DOT, DOT_DOT, 
		/*COMMENTS*/
		BLOCK_COMMENT, LINE_COMMENT
	};
}


extern std::string supertype_names[];

extern std::string subtype_names[];

typedef std::tuple<unsigned int, unsigned int, std::string, alpha_types::supertype_enum, alpha_types::subtype_enum> alpha_token_t;

#ifdef PHASE1
std::string tokenToString(alpha_token_t);
#endif

class alpha_yyFlexLexer : public yyFlexLexer {
private:
	std::vector<alpha_token_t> tokens;
	std::vector<alpha_token_t> buffer;
	bool useForEval, firstToken;
	unsigned int numberOfTokens;
	void addToken(const char *, alpha_types::supertype_enum, alpha_types::subtype_enum, int lineno = -1);
	void peeker();
public:
	#ifdef LATEST_AND_GREATEST
	alpha_yyFlexLexer(std::istream& is, std::ostream& os);
	#endif
	alpha_yyFlexLexer(std::istream * is = 0, std::ostream * os = 0, bool _useForEval = false);
	int alpha_yylex();
	#ifdef PHASE1
	void printer();
	#endif
	virtual int yylex();

	char *getYyText();
	int getLineNo();

};

#endif