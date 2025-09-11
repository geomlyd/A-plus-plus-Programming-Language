%{
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
%}

%defines 

%output = "alpha_parser.cpp"

%union {
	int    			  intValue;
	unsigned		  unsignedValue;
	double 			  doubleValue;
	char*  			  stringValue;
	Object*			  ObjectValue;
}

%start bogusStart

%token <intValue>			PARSE_EXPR
%token <intValue>    	  	INTCONST
%token <doubleValue> 	  	REALCONST
%token <stringValue> 	  	STRINGCONST
%token <stringValue> 	  	ID
%token <stringValue>		DOLLAR_IDENT
%type  <ObjectValue>   	  	expr
%type  <ObjectValue>   	  	lvalue
%type  <ObjectValue> 	  	funcname
%type  <ObjectValue> 	  	funcprefix
%type  <ObjectValue>	 	funcdef
%type  <ObjectValue>	 	member
%type  <ObjectValue>	 	primary
%type  <ObjectValue>	 	assignexpr
%type  <ObjectValue>        const
%type  <ObjectValue>        term
%type  <ObjectValue>    	methodcall
%type  <ObjectValue>    	callsuffix
%type  <ObjectValue>    	normcall
%type  <ObjectValue>        call
%type  <ObjectValue> 	  	objectdef
%type  <ObjectValue> 		objectdinner
%type  <ObjectValue>		objelistnotempty
%type  <ObjectValue>		objcommalist
%type  <ObjectValue>     	commaindexed
%type  <ObjectValue>     	indexed
%type  <ObjectValue>   		indexedelem
%type  <ObjectValue>  	  	elist
%type  <ObjectValue>	 	elistnotempty
%type  <ObjectValue>		argument
%type  <ObjectValue>	 	commalist
%type  <ObjectValue>	  	ifprefix
%type  <ObjectValue>	  	elseprefix
%type  <ObjectValue>  		forprefix
%type  <ObjectValue>		program
%type  <ObjectValue>		stmt
%type  <ObjectValue>	    stmts
%type  <ObjectValue>		nonemptystmts
%type  <ObjectValue>		objelistmulti
%type  <ObjectValue>      	block
%type  <ObjectValue>	    ifstmt
%type  <ObjectValue>	    whilestmt
%type  <ObjectValue>	    forstmt
%type  <ObjectValue>	    returnstmt
%type  <ObjectValue>     	whilestart
%type  <ObjectValue>      	whilecond
%type  <ObjectValue>		idlist
%type  <ObjectValue>		commaidlist
%type  <ObjectValue>		formal
%type  <ObjectValue>        quasiquotes
%type  <ObjectValue>        quotedrules
%type  <ObjectValue>        escape
%type  <ObjectValue>        inline
%type  <ObjectValue>		unparsed
%type  <ObjectValue>		compiledstring
%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL
%token TRUE FALSE NIL ASSIGNMENT PLUS MINUS MULTIPLICATION DIVISION MODULO EQUAL NOT_EQUAL 
%token PLUS_PLUS MINUS_MINUS GREATER_THAN LESS_THAN GREATER_OR_EQUAL LESS_OR_EQUAL
%token EXCLAMATION_MARK TILDA AT SHARP QUESTION_MARK
%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PAREN RIGHT_PAREN
%token LEFT_QUASI_QUOTE RIGHT_QUASI_QUOTE
%token SEMICOLON COMMA COLON DOUBLE_COLON DOT DOT_DOT COMMENT_TOKEN BAD_TOKEN

%destructor { free($$); } STRINGCONST
%destructor { free($$); } ID
%destructor { free($$); } DOLLAR_IDENT

%right ASSIGNMENT
%left OR
%left AND
%nonassoc EQUAL NOT_EQUAL
%nonassoc GREATER_THAN GREATER_OR_EQUAL LESS_THAN LESS_OR_EQUAL
%left PLUS MINUS 
%left MULTIPLICATION DIVISION MODULO
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT DOT_DOT
%left LEFT_BRACKET RIGHT_BRACKET
%left EXCLAMATION_MARK AT SHARP
%left LEFT_QUASI_QUOTE RIGHT_QUASI_QUOTE QUESTION_MARK
%left LEFT_PAREN RIGHT_PAREN
%right TILDA


%%

bogusStart: program {__astRoot = $1;} | PARSE_EXPR nonemptystmts {__astRoot = $2;} | PARSE_EXPR expr {__astRoot = $2;}

//introduced a stmts symbol to implement stmt*
program:		stmts {$$ = Manage_program($1);} ;

stmts:			stmts stmt { $$ = Manage_stmts_stmtsR_stmt($1, $2); }
				| { $$ = Manage_stmts(); }; 

stmt:			expr SEMICOLON { $$ = Manage_stmt_expr_SEMICOLON($1); }
				|ifstmt { $$ = Manage_stmt_ifstmt($1); }
				| whilestmt { $$ = Manage_stmt_whilestmt($1); }
				| forstmt { $$ = Manage_stmt_forstmt($1); }
				| returnstmt { $$ = Manage_stmt_returnstmt($1); }
				| BREAK SEMICOLON { $$ = Manage_stmt_BREAK_SEMICOLON(); }
				| CONTINUE SEMICOLON { $$ = Manage_stmt_CONTINUE(); }
				| block { $$ = Manage_stmt_block($1); }
				| funcdef { $$ = Manage_stmt_funcdef($1); }
				| SEMICOLON { $$ = Manage_stmt_SEMICOLON(); }
				| error SEMICOLON { $$ = Manage_stmt_default(); yyerrok; }
				;

//converted all expr op expr into expr PLUS expr etc. to force priorities
expr:            assignexpr { $$ = Manage_expr_assignexpr($1); }
                | expr PLUS expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1, "+", $3); }
                | expr MINUS expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1, "-", $3); }
                | expr MULTIPLICATION expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1, "*", $3); }
                | expr DIVISION expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1, "/", $3); }
                | expr MODULO expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1, "%", $3); }
                | expr GREATER_THAN expr  { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, ">", $3); }
                | expr GREATER_OR_EQUAL expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, ">=", $3); }
                | expr LESS_THAN expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, "<", $3); }
                | expr LESS_OR_EQUAL expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, "<=", $3); }
                | expr EQUAL expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, "==", $3); }
                | expr NOT_EQUAL expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, "!=", $3); }
                | expr AND expr { $$ = Manage_expr_exprL_AND_exprR($1, $3); }
                | expr OR expr { $$ = Manage_expr_exprL_OR_exprR($1, $3); }
                | term { $$ = Manage_expr_term($1); }
                ;
//forced priority of unary minus
term:			LEFT_PAREN expr RIGHT_PAREN { $$ = Manage_term_LEFT_PAREN_expr_RIGHT_PAREN($2);}

				| MINUS expr %prec UMINUS { $$ = Manage_term_MINUS_expr($2); }
				| NOT expr { $$ = Manage_term_NOT_expr($2); }
				| PLUS_PLUS lvalue { $$ = Manage_term_PLUS_PLUS_lvalue($2); }
				| lvalue PLUS_PLUS { $$ = Manage_term_lvalue_PLUS_PLUS($1); }
				| MINUS_MINUS lvalue { $$ = Manage_term_MINUS_MINUS_lvalue($2); }
				| lvalue MINUS_MINUS { $$ = Manage_term_lvalue_MINUS_MINUS($1); }
				| primary { $$ = Manage_term_primary($1);}
				;

assignexpr:		lvalue ASSIGNMENT expr { $$ = Manage_assignexpr_lvalue_ASSIGNMENT_expr($1,$3); }
				;

primary:		quasiquotes { $$ = Manage_primary_quasiquotes($1); }
				| escape { $$ = Manage_primary_escape($1); }
				| inline { $$ = Manage_primary_inline($1); }
				| unparsed { $$ = Manage_primary_unparsed($1); }
				| compiledstring { $$ = Manage_primary_compiledstring($1); }
				| lvalue 
				{
					$$ = Manage_primary_lvalue($1);
				}
				| call { $$ = Manage_primary_call($1); }
				| objectdef { $$ = Manage_primary_objectdef($1); }
				| LEFT_PAREN funcdef RIGHT_PAREN
                                { $$ = Manage_primary_LEFT_PAREN_funcdef_RIGHT_PAREN($2); }
				| const { $$ =  Manage_primary_const($1);}
				;

lvalue: 		ID 
				{			
					$$ = Manage_lvalue_ID($1);
					free($1);
				}
				| DOLLAR_IDENT
				{
					$$ = Manage_lvalue_ID($1);
					free($1);
				}
				| LOCAL ID 
				{
					$$ = Manage_lvalue_LOCAL_ID($2);
					free($2);
				}
				| DOUBLE_COLON ID 
				{
					$$ = Manage_lvalue_DOUBLE_COLON_ID($2);
					free($2);
				}
				| member { $$ = Manage_lvalue_member($1); }
				;

member: 		lvalue DOT ID 
				{
					$$ = Manage_member_lvalue_DOT_ID($1, $3);
					free($3);
				}
				| lvalue DOT DOLLAR_IDENT 
				{
					$$ = Manage_lvalue_DOT_DOLLAR_IDENT($1, $3);
					free($3);
				}
				| lvalue LEFT_BRACKET expr RIGHT_BRACKET
				{
					$$ = Manage_member_lvalue_LEFT_BRACKET_expr_RIGHT_BRACKET($1, $3);
				}
				| call DOT ID { $$ = Manage_member_call_DOT_ID($1, $3); free($3); }
				| call DOT DOLLAR_IDENT {$$ = Manage_call_DOT_DOLLAR_IDENT($1, $3); free($3);}
				| call LEFT_BRACKET expr RIGHT_BRACKET { $$ = Manage_member_call_LEFT_BRACKET_expr_RIGHT_BRACKET($1, $3); }
				;

call:			call LEFT_PAREN elist RIGHT_PAREN
                        { $$ = Manage_call_callRight_LEFT_PAREN_elist_RIGHT_PAREN($1, $3); }
				| lvalue callsuffix
                        { $$ = Manage_call_lvalue_callsuffix($1, $2); }
				| LEFT_PAREN funcdef RIGHT_PAREN LEFT_PAREN elist RIGHT_PAREN
                        { $$ = Manage_LEFT_PAREN_funcdef_RIGHT_PAREN_LEFT_PAREN_elist_RIGHT_PAREN($2, $5); }
				;

callsuffix:		normcall
                        { $$ = Manage_callsuffix_normcall($1); }
				| methodcall
                        { $$ = Manage_callsuffix_methodcall($1); }            
				;

normcall:		LEFT_PAREN elist RIGHT_PAREN
                        { $$ = Manage_normcall_LEFT_PAREN_elist_RIGHT_PAREN($2); }
				;

methodcall:		DOT_DOT ID LEFT_PAREN elist RIGHT_PAREN 
                        { $$ = Manage_methodcall_DOT_DOT_ID_LEFT_PAREN_elist_RIGHT_PAREN($2, $4); free($2);}
				;

//introduced elistnotempty to implement "zero or more" repetitions
elist:			elistnotempty { $$ = Manage_elist_elistnotempty($1); }
				| { $$ = Manage_elist(); }
				;

//commalist expands into 2nd, 3rd etc. arguments
elistnotempty:	commalist argument { $$ = Manage_commalist_COMMA_argument_commalist($1, $2); }
				;
				
objelistnotempty:	objcommalist expr { $$ = Manage_objelistnotempty_COMMA_expr_objcommalist($1, $2); }
				;				

commalist:		commalist argument COMMA { $$ = Manage_commalist_COMMA_argument_commalist($1, $2); }
				| { $$ = Manage_commalist(); }
				;
				
objcommalist:	objcommalist expr COMMA { $$ = Manage_objelistnotempty_COMMA_expr_objcommalist($1, $2); }
				| { $$ = Manage_objcommalist(); }
				;				

argument:		expr {$$ = Manage_argument_expr($1);}
				| ID COLON expr {
					$$ = Manage_argument_ID_COLON_expr($1, $3);
					free($1);
				}
				;

//introduced objectdinner to implement potentially empty bracket content
objectdef:		LEFT_BRACKET objectdinner RIGHT_BRACKET 
				{ 
					$$ = Manage_objectdef_LEFT_BRACKET_objectdinner_RIGHT_BRACKET($2); 
				}
				;

//empty list produced via index, not needed via elist (resolves reduce-reduce)
objectdinner:	objelistnotempty { $$ = Manage_objectdinner_objelistnotempty($1); }
				| indexed { $$ = Manage_objectdinner_indexed($1); }
				| { $$ = Manage_objectdinner(); }
				;

//commaindexed produces 2nd, 3rd etc.arguments
indexed:		commaindexed indexedelem { $$ = Manage_commaindexed_COMMA_indexedelem_commaindexed($1, $2); }
				;

commaindexed:	commaindexed indexedelem COMMA { $$ = Manage_commaindexed_COMMA_indexedelem_commaindexed($1, $2); }
				| { $$ = Manage_commaindexed(); }
				;

indexedelem:	LEFT_BRACE expr COLON expr RIGHT_BRACE 
				{
					$$ = Manage_indexedelem_LEFT_BRACE_expr_COLON_expr_RIGHT_BRACE($2, $4);
				}
				;

block:			LEFT_BRACE stmts RIGHT_BRACE { $$ = Manage_block_LEFT_BRACE_stmts_RIGHT_BRACE($2); }
				;

//introduced funcname to implement optional function name
funcdef:		funcprefix LEFT_PAREN idlist RIGHT_PAREN block { $$ = Manage_funcdef_funcprefix_LEFT_PAREN_idlist_RIGHT_PAREN_block($1, $3, $5); }
				;

funcprefix:		FUNCTION funcname { $$ = Manage_funcprefix_FUNCTION_funcname($2); }
				;

funcname:		ID
				{ 
					$$ = Manage_funcname_ID($1);
					free($1);
				}				
				| { $$ = Manage_funcname(); }
				;

const:			INTCONST { $$ = Manage_const_numconst($1);}
				| REALCONST { $$ = Manage_const_numconst($1);}
				| STRINGCONST { $$ = Manage_const_strconst($1); free($1);}
				| NIL { $$ = Manage_const_nil();}
				| TRUE { $$ = Manage_const_boolconst(true);}
				| FALSE { $$ = Manage_const_boolconst(false);}
				;

//introduced commaidlist to implement 2nd, 3rd etc. arguments
idlist:			commaidlist formal 
				{
					$$ = Manage_commaidlist_formal_COMMA($1, $2);
				}
				| {$$ = Manage_idlist();};

commaidlist:	commaidlist formal COMMA  
				{
					$$ = Manage_commaidlist_formal_COMMA($1, $2); 
				}
				| {$$ = Manage_commaidlist();};

formal:			ID {
					$$ = Manage_formal_ID($1);
					free($1);
				}
				| ID ASSIGNMENT expr {
					$$ = Manage_formal_ID_ASSIGNMENT_expr($1, $3);
					free($1);
				}
				;

ifprefix:		IF LEFT_PAREN expr RIGHT_PAREN { $$ = Manage_ifprefix_LEFT_PAREN_expr_RIGHT_PAREN($3); }; 

ifstmt:			ifprefix stmt { $$ = Manage_ifstmt_ifprefix_stmt($1, $2); }
				| ifprefix stmt elseprefix stmt { $$ = Manage_ifstmt_ifprefix_stmt_elseprefix_stmt($1, $3, $2, $4); }
			    ;

elseprefix:		ELSE { $$ = Manage_elseprefix_ELSE(); };

whilestart:		WHILE { $$ = Manage_whilestart_WHILE(); }

whilecond:      LEFT_PAREN expr RIGHT_PAREN  { $$ =  Manage_whilecond_LEFT_PAREN_expr_RIGHT_PAREN($2); };

whilestmt:      whilestart whilecond stmt { $$ = Manage_while_whilestart_whilecond_stmt($1, $2, $3); };

forprefix:		FOR LEFT_PAREN elist SEMICOLON expr SEMICOLON 
				{
					$$ = Manage_forprefix_FOR_LEFT_PAREN_elist_SEMICOLON_expr_SEMICOLON($3, $5);
					
				}
				;

forstmt:		forprefix elist RIGHT_PAREN stmt 
				{ 
					$$ = Manage_forstmt_forprefix_elist_RIGHT_PAREN_stmt($1, $2, $4);
					 
				} 
				;

//introduced retex to implement empty return; statement
returnstmt:		RETURN expr SEMICOLON { $$ = Manage_returnstmt_RETURN_expr_SEMICOLON($2); }
				| RETURN SEMICOLON { $$ = Manage_returnstmt_RETURN_SEMICOLON(); }
				;

quasiquotes:	LEFT_QUASI_QUOTE quotedrules RIGHT_QUASI_QUOTE { $$ = Manage_quasiquotes_LEFT_QUASI_QUOTE_quotedrules_RIGHT_QUASI_QUOTE($2); }
				;

nonemptystmts:	nonemptystmts stmt { $$ = Manage_stmts_stmtsR_stmt($1, $2); }
				| stmt { $$ = Manage_stmts_stmtsR_stmt(nullptr, $1); }
				;

objelistmulti:	objelistmulti COMMA expr { $$ = Manage_objelistnotempty_COMMA_expr_objcommalist($1, $3); }
				| expr { $$ = Manage_objelistnotempty_COMMA_expr_objcommalist(nullptr, $1); }

quotedrules:	nonemptystmts { $$ = Manage_quotedrules($1); }
				| objelistmulti { $$ = Manage_quotedrules($1); }
				;	


escape:			TILDA ID { $$ = Manage_escape_TILDA_ID($2); free($2); }
				| TILDA LEFT_PAREN expr RIGHT_PAREN {$$ = Manage_escape_TILDA_LEFT_PAREN_expr_RIGHT_PAREN($3); } 
				;

inline: 		EXCLAMATION_MARK LEFT_PAREN expr RIGHT_PAREN { $$ = Manage_inline_EXCLAMATION_MARK_LEFT_PAREN_expr_RIGHT_PAREN($3); }
				;

unparsed:		SHARP LEFT_PAREN expr RIGHT_PAREN { $$ = Manage_unparsed_SHARP_LEFT_PAREN_expr_RIGHT_PAREN($3); }
				;

compiledstring: AT LEFT_PAREN expr RIGHT_PAREN { $$ = Manage_compiledstring_AT_LEFT_PAREN_expr_RIGHT_PAREN($3); }
				;
%%


int yyerror(char * yaccProvidedMessage) {
 	error(ErrorType::Error, yylineno, "%s before token " BON "\'%s\'" BOFF "\n", yaccProvidedMessage, yytext);
	return 0;
}

