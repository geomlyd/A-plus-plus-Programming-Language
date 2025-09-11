#include "function_actions.h"
#include "defines_header.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define BON "\e[1m"
#define BOFF "\e[0m"

Object* Manage_stmt_default() {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ERROR));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    return tmp;
}

Object* Manage_program(Object* stmts) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PROGRAM));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PROGRAM));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    if(stmts != nullptr)
        tmp->set(AST_TAG_CHILD, Value(stmts));
    return tmp;
}

Object* Manage_stmts_stmtsR_stmt(Object* stmtsR, Object* stmt) {
    if(stmtsR == nullptr){
        stmtsR = new Object();
        stmtsR->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMTS));
        stmtsR->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMTS));
        stmtsR->set(AST_TAG_LINE_KEY, Value((double)yylineno));
        stmtsR->set(AST_TAG_NUMCHILDREN, Value((double)0));
    }
    auto numChildren = (*stmtsR)[AST_TAG_NUMCHILDREN]->toNumber();
    stmtsR->set(numChildren, Value(stmt));
    stmtsR->set(AST_TAG_NUMCHILDREN, Value(numChildren + 1));
    return stmtsR;
}

Object* Manage_stmts() {
    return nullptr;
}

Object* Manage_stmt_expr_SEMICOLON(Object* e) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
	tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    tmp->set(AST_TAG_LINE_KEY, Value((*e)[AST_TAG_LINE_KEY]->toNumber()));
    tmp->set(AST_TAG_CHILD, Value(e));
    return tmp;
}

Object* Manage_stmt_whilestmt(Object* e){
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_LINE_KEY, Value((*e)[AST_TAG_LINE_KEY]->toNumber()));

    assert( strcmp( (*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_WHILESTMT) == 0 );
    newNode->set(AST_TAG_CHILD, Value(e));
    return newNode;
}

Object* Manage_stmt_forstmt(Object* e){
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_LINE_KEY, Value((*e)[AST_TAG_LINE_KEY]->toNumber()));

    assert( strcmp( (*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_FORSTMT) == 0 );
    newNode->set(AST_TAG_CHILD, Value(e));
    return newNode;    
}

Object* Manage_stmt_returnstmt(Object* e){
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_LINE_KEY, Value((*e)[AST_TAG_LINE_KEY]->toNumber()));

    assert( strcmp( (*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_RETURNSTMT) == 0 );
    newNode->set(AST_TAG_CHILD, Value(e));
    return newNode;  
}

Object* Manage_stmt_SEMICOLON(){
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));

    return newNode;
}

Object* Manage_stmt_funcdef(Object* e){
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_LINE_KEY, Value(Value((*e)[AST_TAG_LINE_KEY]->toNumber())));

    assert( strcmp( (*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_FUNCDEF) == 0 );
    newNode->set(AST_TAG_CHILD, Value(e));
    return newNode;      
}

Object* Manage_stmt_ifstmt(Object* e){
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_LINE_KEY, Value(Value((*e)[AST_TAG_LINE_KEY]->toNumber())));

    assert( strcmp( (*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_IFSTMT) == 0 );
    newNode->set(AST_TAG_CHILD, Value(e));
    return newNode;        
}

Object* Manage_stmt_BREAK_SEMICOLON(){
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));

    Object* breakNode = new Object();
    breakNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_BREAKSTMT));
    breakNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_BREAKSTMT));
    breakNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(breakNode));
    return newNode;
}

Object* Manage_stmt_CONTINUE(){
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));

    Object* continueNode = new Object();
    continueNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CONTINUESTMT));
    continueNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_CONTINUESTMT));
    continueNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(continueNode));
    return newNode;
}

Object* Manage_stmt_block(Object* e){
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
    newNode->set(AST_TAG_LINE_KEY, Value(Value((*e)[AST_TAG_LINE_KEY]->toNumber())));

    assert( strcmp( (*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_BLOCK) == 0 );
    newNode->set(AST_TAG_CHILD, Value(e));
    return newNode;
}

Object* Manage_expr_assignexpr(Object* e) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_EXPR));
	tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_EXPR));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CHILD, Value(e));
    return tmp;
}

Object* Manage_expr_exprL_ARITH_OPERATOR_exprR(Object *exprL, const char* op, Object* exprR){
    Object* newNode = new Object();

    assert( strcmp((*exprL)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);
    assert( strcmp((*exprR)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_EXPR));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ARITHEXPR));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_LEFTEXPR, Value(exprL));
    newNode->set(AST_TAG_RIGHTEXPR, Value(exprR));
    newNode->set(AST_TAG_ARITHOP_TYPE, Value(op));
    return newNode;
}

Object* Manage_expr_exprL_REL_OPERATOR_exprR(Object* exprL, const char* op, Object* exprR){
    Object* newNode = new Object();

    assert( strcmp((*exprL)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);
    assert( strcmp((*exprR)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_EXPR));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_RELEXPR));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));

    newNode->set(AST_TAG_LEFTEXPR, Value(exprL));
    newNode->set(AST_TAG_RIGHTEXPR, Value(exprR));
    newNode->set(AST_TAG_RELOP_TYPE, Value(op));
    return newNode;
}

Object* Manage_expr_exprL_AND_exprR(Object* exprL, Object* exprR){
    Object* newNode = new Object();

    assert( strcmp((*exprL)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);
    assert( strcmp((*exprR)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_EXPR));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_BOOLEXPR));  
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno)); 

    newNode->set(AST_TAG_LEFTEXPR, Value(exprL));
    newNode->set(AST_TAG_RIGHTEXPR, Value(exprR));
    newNode->set(AST_TAG_BOOLOP_TYPE, Value("and"));
    return newNode;    
}

Object* Manage_expr_exprL_OR_exprR(Object* exprL, Object* exprR){
    Object* newNode = new Object();

    assert( strcmp((*exprL)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);
    assert( strcmp((*exprR)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_EXPR));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_BOOLEXPR));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));

    newNode->set(AST_TAG_LEFTEXPR, Value(exprL));
    newNode->set(AST_TAG_RIGHTEXPR, Value(exprR));
    newNode->set(AST_TAG_BOOLOP_TYPE, Value("or"));
    return newNode;   
}

Object* Manage_expr_term(Object* e){
    Object* newNode = new Object();

    assert( strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_TERM) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_EXPR));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_EXPR));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(e));
    return newNode;     
}

Object* Manage_term_LEFT_PAREN_expr_RIGHT_PAREN(Object* e){
    Object* newNode = new Object();

    assert( strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_TERM));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_TERM_PARENS_EXPR));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_EXPR, Value(e));
    return newNode;
}

Object* Manage_term_MINUS_expr(Object* e){
    Object* newNode = new Object();

    assert( strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_TERM));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_TERM_MINUS_EXPR));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_EXPR, Value(e));
    return newNode;
}

Object* Manage_term_NOT_expr(Object* e){
    Object* newNode = new Object();

    assert( strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_TERM));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_TERM_NOT_EXPR));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_EXPR, Value(e));
    return newNode;
}

Object* Manage_term_PLUS_PLUS_lvalue(Object* lvalue){
    Object* newNode = new Object();

    assert( strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_TERM));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_TERM_PLUS_PLUS_LVALUE));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_LVALUE, Value(lvalue));
    return newNode;
}

Object* Manage_term_MINUS_MINUS_lvalue(Object* lvalue){
    Object* newNode = new Object();

    assert( strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_TERM));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_TERM_MINUS_MINUS_LVALUE));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_LVALUE, Value(lvalue));
    return newNode;
}

Object* Manage_term_lvalue_PLUS_PLUS(Object* lvalue){
    Object* newNode = new Object();

    assert( strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_TERM));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_TERM_LVALUE_PLUS_PLUS));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_LVALUE, Value(lvalue));
    return newNode;
}

Object* Manage_term_lvalue_MINUS_MINUS(Object* lvalue){
    Object* newNode = new Object();

    assert( strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE) == 0);

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_TERM));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_TERM_LVALUE_MINUS_MINUS));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_LVALUE, Value(lvalue));
    return newNode;
}

Object* Manage_term_primary(Object* value) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_TERM));
	tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_TERM));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CHILD, Value(value));
    return tmp;
}

Object* Manage_assignexpr_lvalue_ASSIGNMENT_expr(Object* lvalue, Object* expression) {
    Object* tmp = new Object();
    assert(!strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE));
    assert(!strcmp((*expression)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_EXPR));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ASSIGNEXPR));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_LVALUE, Value(lvalue));
    tmp->set(AST_TAG_EXPR, Value(expression));
    return tmp;
}

Object* Manage_primary_quasiquotes(Object* e) {
    Object *newNode = new Object();
    assert(!strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_QUASIQUOTES));
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(e));

    return newNode;
}

Object* Manage_primary_escape(Object* e) {
    Object* newNode = new Object();

    assert(!strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_ESCAPE));
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(e));

    return newNode;
}

Object* Manage_primary_inline(Object* e) {
    Object *newNode = new Object();
    assert(!strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_INLINE));
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(e));

    return newNode;
}

Object* Manage_primary_unparsed(Object* e) {
    Object *newNode = new Object();
    assert(!strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_UNPARSED));
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(e));

    return newNode;
}

Object* Manage_primary_compiledstring(Object* e) {
    Object *newNode = new Object();
    assert(!strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_COMPILEDSTRING));
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(e));

    return newNode;
}

Object* Manage_primary_call(Object* e) {
    Object* tmp = new Object();
    assert(!strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_CALL));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CHILD, Value(e));
    return tmp;
}
Object* Manage_primary_objectdef(Object* e) {
    Object* tmp = new Object();
    assert(!strcmp((*e)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_OBJECTDEF));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CHILD, Value(e));
    return tmp;
}
Object* Manage_primary_lvalue(Object* lvalue) {
    Object* tmp = new Object();
    assert(!strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CHILD, Value(lvalue));
    return tmp;
}
Object* Manage_primary_LEFT_PAREN_funcdef_RIGHT_PAREN(Object* funcdef) {
    Object* tmp = new Object();
    assert(!strcmp((*funcdef)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_FUNCDEF));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CHILD, Value(funcdef));
    return tmp;
}
Object* Manage_primary_const(Object* value) {
    Object* tmp = new Object();
    assert(!strcmp((*value)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_CONST));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_PRIMARY));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CHILD, Value(value));
    return tmp;
}

Object* Manage_lvalue_ID(char *id) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_LVALUE));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_LVALUE_ID));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_ID, Value(id));
    return tmp;
}
Object* Manage_lvalue_DOUBLE_COLON_ID(char *id) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_LVALUE));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_LVALUE_GLOBAL_ID));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_GLOBALID, Value(id));
    return tmp;
}
Object* Manage_lvalue_LOCAL_ID(char *id) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_LVALUE));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_LVALUE_LOCAL_ID));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_LOCALID, Value(id));
    return tmp;
}

Object* Manage_lvalue_member(Object* member) {
    Object* tmp = new Object();
    assert(!strcmp((*member)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_MEMBER));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_LVALUE));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_LVALUE_MEMBER));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_MEMBER, Value(member));
    return tmp;
}

Object* Manage_member_lvalue_DOT_ID(Object* lvalue, char *id) {
    Object* tmp = new Object();
    assert(!strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_MEMBER));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_MEMBER_ID));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CALLER, Value(lvalue));
    tmp->set(AST_TAG_ID, Value(id));
    return tmp;
}

Object* Manage_lvalue_DOT_DOLLAR_IDENT(Object* lvalue, char* dollar_ident) {
    Object* tmp = new Object();
    assert(!strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_MEMBER));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_MEMBER_ID));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CALLER, Value(lvalue));
    tmp->set(AST_TAG_ID, Value(dollar_ident));
    return tmp;
}

Object* Manage_member_lvalue_LEFT_BRACKET_expr_RIGHT_BRACKET(Object* lvalue, Object* expr) {
    Object* tmp = new Object();
    assert(!strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE));
    assert(!strcmp((*expr)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_MEMBER));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_MEMBER_EXPR));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CALLER, Value(lvalue));
    tmp->set(AST_TAG_EXPR, Value(expr));
    return tmp;
}
Object* Manage_member_call_DOT_ID(Object* call, char *id) {
    Object* tmp = new Object();
    assert(!strcmp((*call)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_CALL));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_MEMBER));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_MEMBER_ID));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CALLER, Value(call));
    tmp->set(AST_TAG_ID, Value(id));
    return tmp;
}

Object* Manage_call_DOT_DOLLAR_IDENT(Object* call, char* dollar_ident) {
    Object* tmp = new Object();
    assert(!strcmp((*call)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_CALL));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_MEMBER));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_MEMBER_ID));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CALLER, Value(call));
    tmp->set(AST_TAG_ID, Value(dollar_ident));
    return tmp;
}

Object* Manage_member_call_LEFT_BRACKET_expr_RIGHT_BRACKET(Object* call, Object* expr) {
    Object* tmp = new Object();
    assert(!strcmp((*call)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_CALL));
    assert(!strcmp((*expr)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_EXPR));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_MEMBER));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_MEMBER_EXPR));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CALLER, Value(call));
    tmp->set(AST_TAG_EXPR, Value(expr));
    return tmp;
}

Object* Manage_call_callRight_LEFT_PAREN_elist_RIGHT_PAREN(Object* callRight, Object* elist) {
    Object* tmp = new Object();
    assert(!strcmp((*callRight)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_CALL));
    if (elist != nullptr)
        assert(!strcmp((*elist)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_ELIST));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CALL));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_MULTICALL));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_CALL, Value(callRight));
    if (elist != nullptr)
        tmp->set(AST_TAG_ELIST, Value(elist));
    return tmp;
}
Object* Manage_call_lvalue_callsuffix(Object* lvalue, Object* callsuffix) {
    Object* tmp = new Object();
    assert(!strcmp((*lvalue)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_LVALUE));
    assert(!strcmp((*callsuffix)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_CALLSUFFIX));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CALL));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_CALL));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_LVALUE, Value(lvalue));
    tmp->set(AST_TAG_CALLSUFFIX, Value(callsuffix));
    return tmp;
}
Object* Manage_LEFT_PAREN_funcdef_RIGHT_PAREN_LEFT_PAREN_elist_RIGHT_PAREN(Object* funcdef, Object* elist) {
    Object* tmp = new Object();
    assert(!strcmp((*funcdef)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_FUNCDEF));
    if (elist != nullptr)
        assert(!strcmp((*elist)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_ELIST));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CALL));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_FDEFCALL));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_FUNCDEF, Value(funcdef));
    if (elist != nullptr)
        tmp->set(AST_TAG_ELIST, Value(elist));
    return tmp;
}

Object* Manage_callsuffix_normcall(Object* normcall) {
    Object* tmp = new Object();
    assert(!strcmp((*normcall)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_NORMCALL));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CALLSUFFIX));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_NORMCALLSUFFIX));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_NORMCALL, Value(normcall));
    return tmp;
}
Object* Manage_callsuffix_methodcall(Object* methodcall) {
    Object* tmp = new Object();
    assert(!strcmp((*methodcall)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_METHODCALL));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CALLSUFFIX));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_METHODCALLSUFFIX));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_METHODCALL, Value(methodcall));
    return tmp;
}

Object* Manage_normcall_LEFT_PAREN_elist_RIGHT_PAREN(Object* elist) {
    Object* tmp = new Object();
        if (elist != nullptr)
    assert(!strcmp((*elist)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_ELIST));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_NORMCALL));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_NORMCALL));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    if (elist != nullptr)
        tmp->set(AST_TAG_ELIST, Value(elist));
    return tmp;
}

Object* Manage_methodcall_DOT_DOT_ID_LEFT_PAREN_elist_RIGHT_PAREN(char *id, Object* elist) {
    Object* tmp = new Object();
    if (elist != nullptr)
        assert(!strcmp((*elist)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_ELIST));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_METHODCALL));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_METHODCALL));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_ID, Value(id));
    if (elist != nullptr) tmp->set(AST_TAG_ELIST, Value(elist));
    return tmp;
}

Object* Manage_elist() {
    return nullptr;
}
Object* Manage_elist_elistnotempty(Object* elist) {
    Object* tmp = new Object();
    assert(!strcmp((*elist)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_ELISTNOTEMPTY));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_ELIST));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ELIST));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_ELISTNOTEMPTY, Value(elist));
    bool idflag = false;
    for (unsigned int i = 0; i < (*elist)[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        auto argName = (*(*((*elist)[i])).toObjectNoConst())[AST_TAG_ID];
        if (idflag && argName == nullptr) {
            error(ErrorType::Error, yylineno, "A++ Syntax Error: positional arguments after keyword arguments are not allowed\n");
        }
        if (!idflag && argName != nullptr) idflag = true;
    }
    return tmp;
}

Object* Manage_commalist() {
    return nullptr;
}
Object* Manage_commalist_COMMA_argument_commalist(Object* elist, Object* arg) {
    if (elist != nullptr)
        assert(!strcmp((*elist)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_ELISTNOTEMPTY));
    else {
        elist = new Object();
        elist->set(AST_TAG_TYPE_KEY, Value(AST_TAG_ELISTNOTEMPTY));
        elist->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ELISTNOTEMPTY));
        elist->set(AST_TAG_LINE_KEY, Value((double)yylineno));
        elist->set(AST_TAG_NUMCHILDREN, Value((double)0));
    }
    auto numChildren = (*elist)[AST_TAG_NUMCHILDREN]->toNumber();
    elist->set(numChildren, Value(arg));
    elist->set(AST_TAG_NUMCHILDREN, Value(numChildren + 1));
    return elist;
}

Object* Manage_argument_expr(Object *expr) {
    Object* arg = new Object();
    arg->set(AST_TAG_TYPE_KEY, Value(AST_TAG_ARGUMENT));
    arg->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ARGUMENT));
    arg->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    arg->set(AST_TAG_EXPR, Value(expr));
    return arg;
}

Object* Manage_argument_ID_COLON_expr(char *id, Object *expr) {
    Object* arg = new Object();
    arg->set(AST_TAG_TYPE_KEY, Value(AST_TAG_ARGUMENT));
    arg->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ARGUMENT));
    arg->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    arg->set(AST_TAG_ID, Value(id));
    arg->set(AST_TAG_EXPR, Value(expr));
    return arg;
}

Object* Manage_objectdef_LEFT_BRACKET_objectdinner_RIGHT_BRACKET(Object* cont) {
    Object* tmp = new Object();
    if (cont != nullptr)
        assert(!strcmp((*cont)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_OBJECTDINNER));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_OBJECTDEF));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_OBJECTDEF));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    if (cont != nullptr) tmp->set(AST_TAG_OBJECTDINNER, Value(cont));
    return tmp;
}

Object* Manage_objelistnotempty_COMMA_expr_objcommalist(Object *objcommalist, Object *expr) {
    if (objcommalist != nullptr)
        assert(!strcmp((*objcommalist)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_OBJELISTNOTEMPTY));
    
    else {
        objcommalist = new Object();
        objcommalist->set(AST_TAG_TYPE_KEY, Value(AST_TAG_OBJELISTNOTEMPTY));
        objcommalist->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_OBJELISTNOTEMPTY));
        objcommalist->set(AST_TAG_LINE_KEY, Value((double)yylineno));
        objcommalist->set(AST_TAG_NUMCHILDREN, Value((double)0));
    }
    auto numChildren = (*objcommalist)[AST_TAG_NUMCHILDREN]->toNumber();
    objcommalist->set(numChildren, Value(expr));
    objcommalist->set(AST_TAG_NUMCHILDREN, Value(numChildren + 1));
    return objcommalist;
}

Object* Manage_objectdinner_objelistnotempty(Object* elist) {
    Object* tmp = new Object();
    if (elist != nullptr)
        assert(!strcmp((*elist)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_OBJELISTNOTEMPTY));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_OBJECTDINNER));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_CONT_LIST));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_OBJELISTNOTEMPTY, Value(elist));
    return tmp;
}
Object* Manage_objectdinner_indexed(Object* indexed) {
    Object* tmp = new Object();
    assert(!strcmp((*indexed)[AST_TAG_TYPE_KEY]->toString(), AST_TAG_COMMAINDEXED));
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_OBJECTDINNER));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_CONT_INDEXED));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_INDEXED, Value(indexed));
    return tmp;
}
Object* Manage_objectdinner() {
    return nullptr;
}

Object* Manage_objcommalist() {
    return nullptr;
}

Object* Manage_indexed_indexedelem_commaindexed(Object* indexed, Object* elem) {
    assert(false);
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_INDEXED));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_INDEXED));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    if (indexed != nullptr)
        tmp->set(AST_TAG_COMMAINDEXED, Value(indexed));
    tmp->set(AST_TAG_INDEXEDELEM, Value(elem));

    return tmp;
}

Object* Manage_commaindexed() {
    return nullptr;   
}

Object* Manage_commaindexed_COMMA_indexedelem_commaindexed(Object* indexed, Object* elem) {
    if (indexed == nullptr) {
        indexed = new Object();
        indexed->set(AST_TAG_TYPE_KEY, Value(AST_TAG_COMMAINDEXED));
        indexed->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_COMMAINDEXED));
        indexed->set(AST_TAG_LINE_KEY, Value((double)yylineno));
        indexed->set(AST_TAG_NUMCHILDREN, Value((double)0));
    }
    auto numChildren = (*indexed)[AST_TAG_NUMCHILDREN]->toNumber();
    indexed->set(numChildren, Value(elem));
    indexed->set(AST_TAG_NUMCHILDREN, Value(numChildren + 1));
    return indexed;
}

Object* Manage_indexedelem_LEFT_BRACE_expr_COLON_expr_RIGHT_BRACE(Object* key, Object* value) {
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_INDEXEDELEM));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_INDEXEDELEM));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_OBJECT_KEY, Value(key));
    tmp->set(AST_TAG_OBJECT_VALUE, Value(value));

    return tmp;
}

Object* Manage_funcdef_funcprefix_LEFT_PAREN_idlist_RIGHT_PAREN_block(Object* funcprefix, Object* idlist, Object *block) {
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_FUNCDEF));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_FUNCDEF));
    tmp->set(AST_TAG_LINE_KEY, Value((*funcprefix)[AST_TAG_LINE_KEY]->toNumber()));
    tmp->set(AST_TAG_FUNCPREFIX, Value(funcprefix));
    std::map<std::string, bool> idMap = std::map<std::string, bool>();

    if (idlist != nullptr) {
        tmp->set(AST_TAG_IDLIST, Value(idlist));
        auto numFormals = (*idlist)[AST_TAG_NUMCHILDREN]->toNumber();
        bool idflag = false;
        for (unsigned int i = 0; i < numFormals; i++) {
            auto currFormalName = (*((*idlist)[i]->toObjectNoConst()))[AST_TAG_ID]->toString();
            if (idMap.find(currFormalName) == idMap.end())
                idMap[currFormalName] = true;
            else
                error(ErrorType::Error, yylineno, "A++ Syntax Error: same argument many times\n");
            auto formalExpr = (*((*idlist)[i]->toObjectNoConst()))[AST_TAG_EXPR];
            if (idflag && formalExpr == nullptr) {
                error(ErrorType::Error, yylineno, "A++ Syntax Error: required arguments cannot be after optional arguments\n");
            }
            if (!idflag && formalExpr != nullptr) idflag = true;
        }
    }
    tmp->set(AST_TAG_BLOCK, Value(block));
    
    return tmp;
}

Object* Manage_funcprefix_FUNCTION_funcname(Object* value) {
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_FUNCPREFIX));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_FUNCPREFIX));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    if (value != nullptr)
        tmp->set(AST_TAG_CHILD, Value(value));

    return tmp;
}

Object* Manage_funcname(){
   return nullptr;
}

Object* Manage_funcname_ID(char *id) {
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_FUNCNAME));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_FUNCNAME_ID));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_ID, Value(id));
    
    return tmp;
}

Object* Manage_const_numconst(double value) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CONST));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_CONST_NUMCONST));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_VALUE, Value(value));
    
    return tmp;
}

Object* Manage_const_strconst(char *value) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CONST));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_CONST_STRCONST));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_VALUE, Value(value));
    
    return tmp;
}

Object* Manage_const_nil() {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CONST));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_CONST_NIL));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_VALUE, Value(Value::NilType));
    
    return tmp;
}

Object* Manage_const_boolconst(bool value) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_CONST));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_CONST_BOOLCONST));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_VALUE, Value(value));
    
    return tmp;
}

Object* Manage_idlist() {
    return nullptr;
}

Object* Manage_commaidlist() {
    return nullptr;
}

Object* Manage_commaidlist_formal_COMMA(Object* value, Object* formal) {
    if (value == nullptr) {
        value = new Object();
        value->set(AST_TAG_TYPE_KEY, Value(AST_TAG_COMMAIDLIST));
        value->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_COMMAIDLIST));
        value->set(AST_TAG_LINE_KEY, Value((double)yylineno));
        value->set(AST_TAG_NUMCHILDREN, Value((double)0));
    }
    auto numChildren = (*value)[AST_TAG_NUMCHILDREN]->toNumber();
    value->set(numChildren, Value(formal));
    value->set(AST_TAG_NUMCHILDREN, Value(numChildren + 1));
    return value;
}

Object *Manage_formal_ID(char *id){
    Object* formal = new Object();
    formal->set(AST_TAG_TYPE_KEY, Value(AST_TAG_FORMAL));
    formal->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_FORMAL));
    formal->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    formal->set(AST_TAG_ID, Value(id));
    return formal;
}

Object *Manage_formal_ID_ASSIGNMENT_expr(char *id, Object *expr){
    Object* formal = new Object();
    formal->set(AST_TAG_TYPE_KEY, Value(AST_TAG_FORMAL));
    formal->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_FORMAL));
    formal->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    formal->set(AST_TAG_ID, Value(id));
    formal->set(AST_TAG_EXPR, Value(expr));
    return formal;
}

Object* Manage_ifprefix_LEFT_PAREN_expr_RIGHT_PAREN(Object* value) {
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_IFPREFIX));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_IFPREFIX));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_EXPR, Value(value));

    return tmp;
}

Object* Manage_ifstmt_ifprefix_stmt(Object* ifprefix, Object* stmt) {
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_IFSTMT));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_IFSTMT));
    tmp->set(AST_TAG_LINE_KEY, Value((*ifprefix)[AST_TAG_LINE_KEY]->toNumber()));
    tmp->set(AST_TAG_IFPREFIX, Value(ifprefix));
    tmp->set(AST_TAG_IFSTMT_IFBODY, Value(stmt));      
    
    return tmp;
}

Object* Manage_ifstmt_ifprefix_stmt_elseprefix_stmt(Object* ifprefix, Object* elseprefix, Object* ifstmt, Object* elsestmt) {
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_IFSTMT));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_IFSTMT));
    tmp->set(AST_TAG_LINE_KEY, Value((*ifprefix)[AST_TAG_LINE_KEY]->toNumber()));
    tmp->set(AST_TAG_IFPREFIX, Value(ifprefix));
    tmp->set(AST_TAG_ELSEPREFIX, Value(elseprefix));
    tmp->set(AST_TAG_IFSTMT_IFBODY, Value(ifstmt));
    tmp->set(AST_TAG_IFSTMT_ELSEBODY, Value(elsestmt));     
    
    return tmp;
}

Object* Manage_elseprefix_ELSE() {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_ELSEPREFIX));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ELSEPREFIX));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    
    return tmp;
}

Object* Manage_whilestart_WHILE() {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_WHILESTART));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_WHILESTART));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    return tmp;
}

Object* Manage_whilecond_LEFT_PAREN_expr_RIGHT_PAREN(Object* value) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_WHILECOND));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_WHILECOND));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_EXPR, Value(value));
    
    return tmp;
}

Object* Manage_while_whilestart_whilecond_stmt(Object* whilestart, Object* whilecond, Object* stmt) {
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_WHILESTMT));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_WHILESTMT));
    tmp->set(AST_TAG_LINE_KEY, Value((*whilestart)[AST_TAG_LINE_KEY]->toNumber()));
    tmp->set(AST_TAG_WHILESTART, Value(whilestart));
    tmp->set(AST_TAG_WHILECOND, Value(whilecond));
    tmp->set(AST_TAG_STMT, Value(stmt));  
    
    return tmp;
}

Object* Manage_block_LEFT_BRACE_stmts_RIGHT_BRACE(Object* stmts) {
    Object* tmp = new Object();

    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_BLOCK));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_BLOCK));
    
    if (stmts != nullptr) {
        tmp->set(AST_TAG_STMTS, Value(stmts));
        tmp->set(AST_TAG_LINE_KEY, Value((*stmts)[AST_TAG_LINE_KEY]->toNumber()));
    }
    else
        tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    
   
    return tmp;
}

Object* Manage_forprefix_FOR_LEFT_PAREN_elist_SEMICOLON_expr_SEMICOLON(Object* elist, Object* expr) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_FORPREFIX));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_FORPREFIX));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    if (elist != nullptr)
        tmp->set(AST_TAG_ELIST, Value(elist));
    tmp->set(AST_TAG_EXPR, Value(expr));   
    
    return tmp;
}

Object* Manage_forstmt_forprefix_elist_RIGHT_PAREN_stmt (Object* forprefix, Object *elist, Object *stmt) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_FORSTMT));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_FORSTMT));
    tmp->set(AST_TAG_LINE_KEY, Value((*forprefix)[AST_TAG_LINE_KEY]->toNumber())); 
    tmp->set(AST_TAG_FORPREFIX, Value(forprefix));
    if (elist != nullptr)
        tmp->set(AST_TAG_ELIST, Value(elist));
    tmp->set(AST_TAG_STMT, Value(stmt));
    
    return tmp;
}

Object* Manage_returnstmt_RETURN_expr_SEMICOLON(Object* value) {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_RETURNSTMT));
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_RETURNSTMT));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    tmp->set(AST_TAG_EXPR, Value(value));
    
    return tmp;
}

Object* Manage_returnstmt_RETURN_SEMICOLON() {
    Object* tmp = new Object();
    tmp->set(AST_TAG_TYPE_KEY, Value(AST_TAG_RETURNSTMT));   
    tmp->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_RETURNSTMT));
    tmp->set(AST_TAG_LINE_KEY, Value((double)yylineno));

    return tmp;
}

Object* Manage_quasiquotes_LEFT_QUASI_QUOTE_quotedrules_RIGHT_QUASI_QUOTE(Object *quotedrules){
    Object *newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_QUASIQUOTES));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_QUASIQUOTES));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(quotedrules));

    return newNode;
}

Object* Manage_quotedrules(Object *contents) {
    Object *newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_QUOTEDRULES));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_QUOTEDRULES));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    if(contents != nullptr)
        newNode->set(AST_TAG_CHILD, Value(contents));

    return newNode;
}

Object* Manage_escape_TILDA_ID(char* id) {
    Object *newNode = new Object();

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_ESCAPE));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ESCAPE_ID));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_ID, Value(id));

    return newNode;
}

Object* Manage_escape_TILDA_LEFT_PAREN_expr_RIGHT_PAREN(Object* expr) {
    Object *newNode = new Object();

    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_ESCAPE));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ESCAPE_EXPR));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_EXPR, Value(expr));

    return newNode;;
}

Object* Manage_inline_EXCLAMATION_MARK_LEFT_PAREN_expr_RIGHT_PAREN(Object* expr) {
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_INLINE));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_INLINE));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(expr));

    return newNode;
}

Object* Manage_unparsed_SHARP_LEFT_PAREN_expr_RIGHT_PAREN(Object* expr) {
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_UNPARSED));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_UNPARSED));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(expr));

    return newNode;
}

Object* Manage_compiledstring_AT_LEFT_PAREN_expr_RIGHT_PAREN(Object* expr) {
    Object* newNode = new Object();
    newNode->set(AST_TAG_TYPE_KEY, Value(AST_TAG_COMPILEDSTRING));
    newNode->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_COMPILEDSTRING));
    newNode->set(AST_TAG_LINE_KEY, Value((double)yylineno));
    newNode->set(AST_TAG_CHILD, Value(expr));

    return newNode;
}