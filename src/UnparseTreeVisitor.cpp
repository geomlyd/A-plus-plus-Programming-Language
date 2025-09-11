#include "UnparseTreeVisitor.h"
#include <assert.h>
#include <string.h>

UnparseTreeVisitor::UnparseTreeVisitor() {
    ast2string = std::stack<std::string>();
}

TreeVisitor* UnparseTreeVisitor::Clone() const {
    UnparseTreeVisitor* tmp = new UnparseTreeVisitor();
    tmp->ast2string = std::stack<std::string>(ast2string);
    return tmp;
}

std::string UnparseTreeVisitor::getSourceText() {
    if(ast2string.empty())
        return "";
    return ast2string.top();
}

void UnparseTreeVisitor::visitProgram( Object& node) {
    assert(strcmp(node[AST_TAG_TYPE_KEY]->toString(), AST_TAG_PROGRAM) == 0);
    assert(ast2string.size() == 1 || node[AST_TAG_CHILD] == nullptr);
}

void UnparseTreeVisitor::visitStmts( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_STMTS) == 0);
    std::string statementText = "";
    for(unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++){
        statementText = ast2string.top() + "\n" + statementText;
        ast2string.pop();
    }
    ast2string.push(statementText);
}

void UnparseTreeVisitor::visitStmt( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_STMT) == 0);
    const Value *stmt = node[AST_TAG_CHILD];
    if(stmt == nullptr){ //empty statement
        ast2string.push(";");
    }
    else{
        auto stmtObj = stmt->toObject();
        auto childType = (*stmtObj)[AST_TAG_TYPE_KEY]->toString();
        //stmt -> expr; or stmt -> break; or stmt -> continue;
        if(strcmp(childType, AST_TAG_RETURNSTMT) == 0 ||strcmp(childType, AST_TAG_EXPR) == 0 || strcmp(childType, AST_TAG_BREAKSTMT) == 0 
                || strcmp(childType, AST_TAG_CONTINUESTMT) == 0
                || strcmp(childType, AST_TAG_ERROR) == 0){
            std::string childStmtText = ast2string.top();
            ast2string.pop();
            ast2string.push(childStmtText + ";");
        }
    }
}

void UnparseTreeVisitor::visitBreak( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_BREAKSTMT) == 0);
    ast2string.push("break");
}

void UnparseTreeVisitor::visitContinue( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONTINUESTMT) == 0);
    ast2string.push("continue");
}

void UnparseTreeVisitor::visitExpr( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_EXPR) == 0);
}

void UnparseTreeVisitor::visitArithExpr( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ARITHEXPR) == 0);
    auto operand2 = ast2string.top(); //right operand
    ast2string.pop();
    auto operand1 = ast2string.top(); //left operand
    ast2string.pop();
    ast2string.push(operand1 + " " + node[AST_TAG_ARITHOP_TYPE]->toString() + " " + operand2);
}

void UnparseTreeVisitor::visitRelExpr( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_RELEXPR) == 0);
    auto operand2 = ast2string.top(); //right operand
    ast2string.pop();
    auto operand1 = ast2string.top(); //left operand
    ast2string.pop();
    ast2string.push(operand1 + " " + node[AST_TAG_RELOP_TYPE]->toString() + " " + operand2);    
}

void UnparseTreeVisitor::visitBoolExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_BOOLEXPR) == 0);
    auto operand2 = ast2string.top(); //right operand
    ast2string.pop();
    auto operand1 = ast2string.top(); //left operand
    ast2string.pop();
    ast2string.push(operand1 + " " + node[AST_TAG_BOOLOP_TYPE]->toString() + " " + operand2); 
}

void UnparseTreeVisitor::visitTerm( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM) == 0);
}

void UnparseTreeVisitor::visitTermParensExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_PARENS_EXPR) == 0);
    auto exprString = ast2string.top();
    ast2string.pop();
    ast2string.push("( " + exprString + " )");
}

void UnparseTreeVisitor::visitTermMinusExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_MINUS_EXPR) == 0);
    auto exprString = ast2string.top();
    ast2string.pop();
    ast2string.push("-" + exprString);
}

void UnparseTreeVisitor::visitTermNotExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_NOT_EXPR) == 0);
    auto exprString = ast2string.top();
    ast2string.pop();
    ast2string.push("not " + exprString);
}

void UnparseTreeVisitor::visitTermPlusPlusLvalue( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_PLUS_PLUS_LVALUE) == 0);
    auto exprString = ast2string.top();
    ast2string.pop();
    ast2string.push("++" + exprString);
}

void UnparseTreeVisitor::visitTermMinusMinusLvalue( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_MINUS_MINUS_LVALUE) == 0);
    auto exprString = ast2string.top();
    ast2string.pop();
    ast2string.push("--" + exprString);
}

void UnparseTreeVisitor::visitTermLvaluePlusPlus( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_LVALUE_PLUS_PLUS) == 0);
    auto exprString = ast2string.top();
    ast2string.pop();
    ast2string.push(exprString + "++");
}

void UnparseTreeVisitor::visitTermLvalueMinusMinus( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_LVALUE_MINUS_MINUS) == 0);
    auto exprString = ast2string.top();
    ast2string.pop();
    ast2string.push(exprString + "--");
}

void UnparseTreeVisitor::visitAssignExpr( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ASSIGNEXPR) == 0);
    std::string expr = ast2string.top();
    ast2string.pop();
    std::string lvalue = ast2string.top();
    ast2string.pop();
    ast2string.push(lvalue + " = " + expr);
}

void UnparseTreeVisitor::visitPrimary( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_PRIMARY) == 0);
}

void UnparseTreeVisitor::visitLvalueId( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_LVALUE_ID) == 0);
    ast2string.push(node[AST_TAG_ID]->toString());
}

void UnparseTreeVisitor::visitLvalueGlobalId( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_LVALUE_GLOBAL_ID) == 0);
    std::string s = node[AST_TAG_GLOBALID]->toString();
    ast2string.push("::" + s);
}

void UnparseTreeVisitor::visitLvalueLocalId( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_LVALUE_LOCAL_ID) == 0);
    std::string s = node[AST_TAG_LOCALID]->toString();
    ast2string.push("local " + s);
}

void UnparseTreeVisitor::visitLvalueMember( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_LVALUE_MEMBER) == 0);
}

void UnparseTreeVisitor::visitMemberId( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_MEMBER_ID) == 0);
    std::string id = node[AST_TAG_ID]->toString();
    std::string lvalue = ast2string.top();
    ast2string.pop();
    ast2string.push(lvalue + "." + id);
}

void UnparseTreeVisitor::visitMemberExpr( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_MEMBER_EXPR) == 0);
    std::string expr = ast2string.top();
    ast2string.pop();
    std::string lvalue = ast2string.top();
    ast2string.pop();
    ast2string.push(lvalue + "[" + expr + "]");
}

void UnparseTreeVisitor::visitMultiCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_MULTICALL) == 0);
    std::string elist;
    if (node[AST_TAG_ELIST] == nullptr) elist = "";
    else {
        elist = ast2string.top();
        ast2string.pop();
    }
    std::string callRight = ast2string.top();
    ast2string.pop();
    ast2string.push(callRight + "(" + elist + ")");
}

void UnparseTreeVisitor::visitCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CALL) == 0);
    std::string callsuffix = ast2string.top();
    ast2string.pop();
    std::string lvalue = ast2string.top();
    ast2string.pop();
    ast2string.push(lvalue + callsuffix);
}

void UnparseTreeVisitor::visitFdefCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FDEFCALL) == 0);
    std::string elist;
    if (node[AST_TAG_ELIST] == nullptr) elist = "";
    else {
        elist = ast2string.top();
        ast2string.pop();
    }
    std::string fdef = ast2string.top();
    ast2string.pop();
    ast2string.push("(" + fdef + ")" + "(" + elist + ")");
}

void UnparseTreeVisitor::visitNormCallSuffix( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_NORMCALLSUFFIX) == 0);
}

void UnparseTreeVisitor::visitMethodCallSuffix( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_METHODCALLSUFFIX) == 0);
}

void UnparseTreeVisitor::visitNormCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_NORMCALL) == 0);
    std::string elist;
    if (node[AST_TAG_ELIST] == nullptr) elist = "";
    else {
        elist = ast2string.top();
        ast2string.pop();
    }
    ast2string.push("(" + elist + ")");
}

void UnparseTreeVisitor::visitMethodCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_METHODCALL) == 0);
    std::string elist;
    if (node[AST_TAG_ELIST] == nullptr) elist = "";
    else {
        elist = ast2string.top();
        ast2string.pop();
    }
    std::string id = node[AST_TAG_ID]->toString();
    ast2string.push(".." + id + "(" + elist + ")");
}

void UnparseTreeVisitor::visitElist( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ELIST) == 0);
    
}

void UnparseTreeVisitor::visitElistNotEmpty( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ELISTNOTEMPTY) == 0);
    std::string tmp = std::string();
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        tmp = ast2string.top() + tmp;
        ast2string.pop();
        if (i < node[AST_TAG_NUMCHILDREN]->toNumber()-1) tmp = ", " + tmp;
    }
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitArgument(Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ARGUMENT) == 0);
    std::string expr = ast2string.top();
    ast2string.pop();

    std::string id = "";
    if (node[AST_TAG_ID] != nullptr) {
        id = std::string(node[AST_TAG_ID]->toString()) + " : ";
    }
    ast2string.push(id + expr);
}

void UnparseTreeVisitor::visitObjectDef( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_OBJECTDEF) == 0);
    std::string cont;
    if (node[AST_TAG_OBJECTDINNER] == nullptr) cont = "";
    else {
        cont = ast2string.top();
        ast2string.pop();
    }
    ast2string.push("[" + cont + "]");
}

 void UnparseTreeVisitor::visitObjElistNotEmpty( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_OBJELISTNOTEMPTY) == 0);
    std::string tmp = std::string();
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        tmp = ast2string.top() + tmp;
        ast2string.pop();
        if (i < node[AST_TAG_NUMCHILDREN]->toNumber()-1) tmp = ", " + tmp;
    }
    ast2string.push(tmp);
 }

void UnparseTreeVisitor::visitObjectDinnerObjElistnotempty( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONT_LIST) == 0);
}

void UnparseTreeVisitor::visitObjectDinnerIndexed( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONT_INDEXED) == 0);
}

void UnparseTreeVisitor::visitCommaIndexed( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_COMMAINDEXED) == 0);

    std::string tmp = std::string();
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        tmp = ast2string.top() + tmp;
        ast2string.pop();
        if (i != node[AST_TAG_NUMCHILDREN]->toNumber() - 1) tmp = ", " + tmp;
    }
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitIndexedElem( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_INDEXEDELEM) == 0);
    std::string value = ast2string.top();
    ast2string.pop();

    std::string key = ast2string.top();
    ast2string.pop();

    ast2string.push("{" + key + ": " + value + "}");
}

void UnparseTreeVisitor::visitBlock( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_BLOCK) == 0);
    std::string tmp;
    if (node[AST_TAG_STMTS] != nullptr) {
        tmp = "{\n" + ast2string.top() + "}";
        ast2string.pop();
    }
    else
        tmp = "{ }";
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitFuncDef( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FUNCDEF) == 0);
    std::string block = ast2string.top();
    ast2string.pop();

    std::string idlist = "";
    if (node[AST_TAG_IDLIST] != nullptr) {
        idlist += ast2string.top();
        ast2string.pop();
    }

    std::string funcprefix = ast2string.top();
    ast2string.pop();

    if (funcprefix[0] == '(')   
        ast2string.push(funcprefix + "(" + idlist + ") " + block + ")");
    else
     ast2string.push(funcprefix + "(" + idlist + ") " + block);
}

void UnparseTreeVisitor::visitFuncPrefix( Object& node) {
    assert(strcmp(node[AST_TAG_TYPE_KEY]->toString(), AST_TAG_FUNCPREFIX) == 0);
    std::string tmp = "";
    if (node[AST_TAG_CHILD] != nullptr) {
        tmp = "function " + ast2string.top();
        ast2string.pop();
    }
    else
        tmp = "(function ";

    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitFuncName( Object& node) {
    //assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FUNCPREFIX_FUNCNAME) == 0);
    if (!strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FUNCNAME_ID))
        ast2string.push(node[AST_TAG_ID]->toString());
}

void UnparseTreeVisitor::visitConst( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONST) == 0);
    return;
}

void UnparseTreeVisitor::visitConstNumconst( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONST_NUMCONST) == 0);
    ast2string.push(std::to_string(node[AST_TAG_VALUE]->toNumber()));
}

void UnparseTreeVisitor::visitConstStringconst( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONST_STRCONST) == 0);
    std::string original = node[AST_TAG_VALUE]->toString();
    std::string tmp = "\"";
    for (std::string::iterator it = original.begin(); it != original.end(); it++) {
        switch(*it) {
            case '\t':
                tmp += "\\t";
                break;
            case '\n':
                tmp += "\\n";
                break;
            case '\r':
                tmp += "\\r";
                break;
            case '\\':
                tmp += "\\\\";
                break;
            case '\"':
                tmp += "\\\"";
                break;
            case '\?':
                tmp += "\\\?";
                break;
            case '\b':
                tmp += "\\\b";
                break;                     
            default:
                tmp += *it;
                break;
        }       
    }
    tmp += "\"";
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitConstBoolconst( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONST_BOOLCONST) == 0);
    std::string tmp;   
    node[AST_TAG_VALUE]->toBoolean() ? tmp = "true" : tmp = "false";
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitConstNil( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONST_NIL) == 0);
    ast2string.push("nil");
}

void UnparseTreeVisitor::visitID( Object& node) {
    ast2string.push(node[AST_TAG_ID]->toString());
}

void UnparseTreeVisitor::visitCommaIdList( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_COMMAIDLIST) == 0);
   
    std::string tmp = std::string();
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        tmp = ast2string.top() + tmp;
        ast2string.pop();
        if (i != node[AST_TAG_NUMCHILDREN]->toNumber() - 1) tmp = ", " + tmp;
    }
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitFormal( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FORMAL) == 0);

    std::string id = node[AST_TAG_ID]->toString();

    std::string expr = "";
    if (node[AST_TAG_EXPR] != nullptr) {
        expr = " = " + ast2string.top();
        ast2string.pop();
    }
    ast2string.push(id + expr);
}

void UnparseTreeVisitor::visitIfPrefix( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_IFPREFIX) == 0);
    std::string expr = ast2string.top();
    ast2string.pop();

    std::string tmp = "if (" + expr + ")\n";

    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitElsePrefix( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ELSEPREFIX) == 0);
    ast2string.push("else ");
}

void UnparseTreeVisitor::visitIfStmt( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_IFSTMT) == 0);
    std::string ifstmt = ast2string.top();
    ast2string.pop();

    std::string ifprefix = ast2string.top();
    ast2string.pop();

    std::string tmp = ifprefix + ifstmt;

    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitIfStmtElseStmt( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_IFSTMT) == 0);
    std::string elsestmt = ast2string.top();
    ast2string.pop();

    std::string elseprefix = ast2string.top();
    ast2string.pop();

    std::string ifstmt = ast2string.top();
    ast2string.pop();

    std::string ifprefix = ast2string.top();
    ast2string.pop();

    std::string tmp = ifprefix + ifstmt + "\n" +elseprefix;

    const Object* stmts = node[AST_TAG_IFSTMT_ELSEBODY]->toObject();
    const Object *obj = (*stmts)[AST_TAG_CHILD]->toObject();
    
    if ((*obj)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_IFSTMT))
        tmp += elsestmt;
    else
        tmp += "\n" + elsestmt;
           
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitWhileStart( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_WHILESTART) == 0);
    ast2string.push("while ");
}

void UnparseTreeVisitor::visitWhileCond( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_WHILECOND) == 0);
    std::string whilecond = ast2string.top();
    ast2string.pop();

    std::string whilestart = ast2string.top();
    ast2string.pop();

    ast2string.push(whilestart + "(" + whilecond + ") ");
}

void UnparseTreeVisitor::visitWhileStmt( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_WHILESTMT) == 0);
    
    std::string whilestmt = ast2string.top();
    ast2string.pop();

    std::string whilestartwhilecond = ast2string.top();
    ast2string.pop();    

    ast2string.push(whilestartwhilecond + whilestmt);
}

void UnparseTreeVisitor::visitForPrefix( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FORPREFIX) == 0);
    std::string expr = ast2string.top();
    ast2string.pop();
    
    std::string elist = "";
    if (node[AST_TAG_ELIST] != nullptr) {
        elist += ast2string.top();
        ast2string.pop();
    }

    ast2string.push("for (" + elist + "; " + expr +"; ");
}

void UnparseTreeVisitor::visitForStmt( Object&node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FORSTMT) == 0);
    std::string stmt = ast2string.top();
    ast2string.pop();

    std::string elist = "";
    if (node[AST_TAG_ELIST] != nullptr) {
        elist += ast2string.top();
        ast2string.pop();
    }

    std::string forPrefix = ast2string.top();
    ast2string.pop();

    ast2string.push(forPrefix + elist + ")" + "\n" + stmt);
}


void UnparseTreeVisitor::visitReturnStmt( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_RETURNSTMT) == 0);
    ast2string.push("return;");
}

void UnparseTreeVisitor::visitReturnStmtExpr( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_RETURNSTMT) == 0);
    std::string tmp = "return " + ast2string.top();
    ast2string.pop();
    ast2string.push(tmp);   
}

void UnparseTreeVisitor::visitQuasiQuotes(Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_QUASIQUOTES) == 0);
    std::string tmp = "<< " + ast2string.top() + " >>";
    ast2string.pop();
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitQuotedRules(Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_QUOTEDRULES) == 0);
    std::string tmp = ast2string.top();
    ast2string.pop();
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitEscapeId(Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ESCAPE_ID) == 0);
    std::string ID = node[AST_TAG_ID]->toString();

    std::string tmp = "~" + ID;
   
    ast2string.push(tmp);  
}

void UnparseTreeVisitor::visitEscapeExpr(Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ESCAPE_EXPR) == 0);
    std::string tmp = "~(" + ast2string.top() + ")";
    ast2string.pop();
    ast2string.push(tmp);  
}

void UnparseTreeVisitor::visitInline( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_INLINE) == 0);
    std::string tmp = "!(" + ast2string.top() + ")";
    ast2string.pop();
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitUnparsed( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_UNPARSED) == 0);
    std::string tmp = "#(" + ast2string.top() + ")";
    ast2string.pop();
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitCompiledString( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_COMPILEDSTRING) == 0);
    std::string tmp = "@(" + ast2string.top() + ")";
    ast2string.pop();
    ast2string.push(tmp);
}

void UnparseTreeVisitor::visitValueStorage(Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_VALUESTORAGE) == 0);

    ast2string.push(node[AST_TAG_VALUE]->makeString());
}