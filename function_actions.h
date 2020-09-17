#ifndef FUNCTION_ACTIONS_H
#define FUNCTION_ACTIONS_H

#include <list>
#include "error_handler.h"
#include "Object.h"
#include "Value.h"
#include "TreeTags.h"
#include <utility>
//#define DEBUG

extern int yyerror (char * yaccProvidedMessage);

typedef std::pair<unsigned, unsigned>  unsignedPair;

Object* Manage_program(Object* stmts);
Object* Manage_stmts();
Object* Manage_stmts_stmtsR_stmt(Object* stmtsR, Object* stmt);

Object* Manage_stmt_default();
Object* Manage_stmt_whilestmt(Object* e);
Object* Manage_stmt_forstmt(Object* e);
Object* Manage_stmt_returnstmt(Object* e);
Object* Manage_stmt_SEMICOLON();
Object* Manage_stmt_funcdef(Object* e);
Object* Manage_stmt_expr_SEMICOLON(Object* e);
Object* Manage_stmt_ifstmt(Object* e);
Object* Manage_stmt_BREAK_SEMICOLON();
Object* Manage_stmt_CONTINUE();
Object* Manage_stmt_block(Object* e);


Object* Manage_expr_assignexpr(Object*  e);
Object* Manage_expr_exprL_ARITH_OPERATOR_exprR(Object* exprL, const char* op, Object* exprR);
Object* Manage_expr_exprL_REL_OPERATOR_exprR(Object* exprL, const char* op, Object* exprR);
Object* Manage_expr_exprL_AND_exprR(Object* exprL, Object* exprR);
Object* Manage_expr_exprL_OR_exprR(Object* exprL, Object* exprR);
Object* Manage_expr_term(Object* term);


Object *Manage_term_LEFT_PAREN_expr_RIGHT_PAREN(Object* e);
Object* Manage_term_MINUS_expr(Object* e);
Object* Manage_term_NOT_expr(Object* term);
Object* Manage_term_PLUS_PLUS_lvalue(Object* lvalue);
Object* Manage_term_MINUS_MINUS_lvalue(Object* lvalue);
Object* Manage_term_lvalue_PLUS_PLUS(Object* lvalue);
Object* Manage_term_lvalue_MINUS_MINUS(Object* lvalue);
Object* Manage_term_primary(Object* value);

Object* Manage_assignexpr_lvalue_ASSIGNMENT_expr(Object* lvalue, Object* expr);

Object* Manage_primary_quasiquotes(Object* e);
Object* Manage_primary_escape(Object* e);
Object* Manage_primary_inline(Object* e);
Object* Manage_primary_unparsed(Object* e);
Object* Manage_primary_compiledstring(Object* e);
Object* Manage_primary_call(Object* e);
Object* Manage_primary_objectdef(Object* e);
Object* Manage_primary_lvalue(Object* lvalue);
Object* Manage_primary_LEFT_PAREN_funcdef_RIGHT_PAREN(Object* funcdef);
Object* Manage_primary_const(Object* value);

Object* Manage_lvalue_ID(char *id);
Object* Manage_lvalue_DOUBLE_COLON_ID(char *id);
Object* Manage_lvalue_LOCAL_ID(char *id);
Object* Manage_lvalue_DOLLAR_ID(char* id);
Object* Manage_lvalue_member(Object* member);

Object* Manage_member_lvalue_DOT_ID(Object* lvalue, char *id);
Object* Manage_lvalue_DOT_DOLLAR_IDENT(Object* lvalue, char* dollar_ident);
Object* Manage_member_lvalue_LEFT_BRACKET_expr_RIGHT_BRACKET(Object* lvalue, Object* expr);
Object* Manage_member_call_DOT_ID(Object* call, char *id);
Object* Manage_call_DOT_DOLLAR_IDENT(Object* call, char* dollar_ident);
Object* Manage_member_call_LEFT_BRACKET_expr_RIGHT_BRACKET(Object* call, Object* expr);

Object* Manage_call_callRight_LEFT_PAREN_elist_RIGHT_PAREN(Object* callRight, Object* elist);
Object* Manage_call_lvalue_callsuffix(Object* lvalue, Object* callsuffix);
Object* Manage_LEFT_PAREN_funcdef_RIGHT_PAREN_LEFT_PAREN_elist_RIGHT_PAREN(Object* funcdef, Object* elist);

Object* Manage_callsuffix_normcall(Object* normcall);
Object* Manage_callsuffix_methodcall(Object* methodcall);

Object* Manage_normcall_LEFT_PAREN_elist_RIGHT_PAREN(Object* elist);

Object* Manage_methodcall_DOT_DOT_ID_LEFT_PAREN_elist_RIGHT_PAREN(char *id, Object* elist);

Object* Manage_elist();
Object* Manage_elist_elistnotempty(Object* elist);

Object* Manage_elistnotempty_expr_commalist(Object* elist, Object* e);

Object* Manage_commalist();
Object* Manage_commalist_COMMA_argument_commalist(Object* elist, Object* arg);

Object* Manage_argument_expr(Object *expr);

Object* Manage_argument_ID_COLON_expr(char *id, Object *expr);

Object* Manage_objectdef_LEFT_BRACKET_objectdinner_RIGHT_BRACKET(Object* cont);

Object* Manage_objectdinner_objelistnotempty(Object* elist);
Object* Manage_objelistnotempty_COMMA_expr_objcommalist(Object *objcommalist, Object *expr);
Object* Manage_objectdinner_indexed(Object* indexed);
Object* Manage_objectdinner();
Object* Manage_objcommalist();

Object* Manage_indexed_indexedelem_commaindexed(Object* indexed, Object* elem);
Object* Manage_commaindexed();
Object* Manage_commaindexed_COMMA_indexedelem_commaindexed(Object* indexed, Object* elem);

Object* Manage_indexedelem_LEFT_BRACE_expr(Object* e);
Object* Manage_indexedelem_LEFT_BRACE_expr_COLON_expr_RIGHT_BRACE(Object* key, Object* value);


Object* Manage_funcdef_funcprefix_LEFT_PAREN_idlist_RIGHT_PAREN_block(Object*, Object*, Object*);

Object* Manage_funcprefix_FUNCTION_funcname(Object* id);

Object* Manage_funcname();
Object* Manage_funcname_ID(char *id);
Object* Manage_funcname_inline(Object* il);

Object* Manage_const_numconst(double value);
Object* Manage_const_strconst(char *value);
Object* Manage_const_nil();
Object* Manage_const_boolconst(bool value);

Object* Manage_idlist();
Object* Manage_commaidlist();
Object* Manage_commaidlist_formal_COMMA(Object*, Object*);

Object *Manage_formal_ID(char *id);

Object *Manage_formal_ID_ASSIGNMENT_expr(char *id, Object *expr);

Object* Manage_ifprefix_LEFT_PAREN_expr_RIGHT_PAREN(Object* value);

Object* Manage_ifstmt_ifprefix_stmt(Object* ifprefix, Object* stmt);

Object* Manage_ifstmt_ifprefix_stmt_elseprefix_stmt(Object* ifprefix, Object* elseprefix, Object* ifstmt, Object* elsestmt);

Object* Manage_elseprefix_ELSE();

Object* Manage_whilestart_WHILE();

Object* Manage_whilecond_LEFT_PAREN_expr_RIGHT_PAREN(Object* value);


Object* Manage_while_whilestart_whilecond_stmt(Object* whilestart, Object* whilecond, Object* stmt);

Object* Manage_block_LEFT_BRACE_stmts_RIGHT_BRACE(Object* stmts);

Object* Manage_forprefix_FOR_LEFT_PAREN_elist_SEMICOLON_expr_SEMICOLON(Object* elist, Object* expr);
Object* Manage_forstmt_forprefix_elist_RIGHT_PAREN_stmt (Object* forprefix, Object *elist, Object *stmt);

Object* Manage_returnstmt_RETURN_expr_SEMICOLON(Object* value);
Object* Manage_returnstmt_RETURN_SEMICOLON();

Object* Manage_quasiquotes_LEFT_QUASI_QUOTE_quotedrules_RIGHT_QUASI_QUOTE(Object *quotedrules);
Object* Manage_quotedrules(Object *contents);
Object* Manage_escape_TILDA_ID(char* id);
Object* Manage_escape_TILDA_LEFT_PAREN_expr_RIGHT_PAREN(Object* expr);
Object* Manage_inline_EXCLAMATION_MARK_LEFT_PAREN_expr_RIGHT_PAREN(Object* expr);
Object* Manage_unparsed_SHARP_LEFT_PAREN_expr_RIGHT_PAREN(Object* expr);
Object* Manage_compiledstring_AT_LEFT_PAREN_expr_RIGHT_PAREN(Object* expr);
#endif