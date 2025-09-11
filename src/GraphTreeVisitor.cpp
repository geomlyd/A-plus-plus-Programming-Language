#include "GraphTreeVisitor.h"
#include <assert.h>
#include <string.h>

GraphTreeVisitor::GraphTreeVisitor() {
    idstack = std::stack<int>();
    edges = std::vector<std::string>();
    vertices = std::vector<std::string>();
}

TreeVisitor* GraphTreeVisitor::Clone() const {
    GraphTreeVisitor* tmp = new GraphTreeVisitor();
    tmp->idstack = idstack;
    tmp->edges = edges;
    tmp->vertices = vertices;
    return tmp;
}

std::string GraphTreeVisitor::getGraph() {
    std::string toReturn = "graph AST {\n";

    
    for (auto v : vertices) {
        toReturn += v + "\n";
    }
    for (auto e : edges) {
        toReturn += e + "\n";
    }
    
    toReturn += "\n}";

    return toReturn;
}

void GraphTreeVisitor::visitProgram( Object& node){
    assert(strcmp(node[AST_TAG_TYPE_KEY]->toString(), AST_TAG_PROGRAM) == 0);
    assert(idstack.size() == 1 || node[AST_TAG_CHILD] == nullptr);
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_PROGRAM + "\"];");
    if(!idstack.empty()){
        unsigned child = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
        idstack.push(id++);  
    }  
}

void GraphTreeVisitor::visitStmts( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_STMTS) == 0);
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_STMTS + "\"];");
    for(unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i ++){
        unsigned tmp = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(tmp));
    }
    idstack.push(id++);  
}

void GraphTreeVisitor::visitStmt( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_STMT) == 0);
    const Value *stmt = node[AST_TAG_CHILD];

    if(stmt != nullptr){
        unsigned stmtId = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(stmtId));
    }
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_STMT + "\"];");
    idstack.push(id++); 
}

void GraphTreeVisitor::visitBreak( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_BREAKSTMT) == 0);
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_BREAKSTMT + "\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitContinue( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONTINUESTMT) == 0);
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_CONTINUESTMT + "\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_EXPR) == 0);
    auto childId = idstack.top();
    idstack.pop();    
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_EXPR + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(childId));
    idstack.push(id++);
}

void GraphTreeVisitor::visitArithExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ARITHEXPR) == 0);
    auto operand2Id = idstack.top(); //right operand
    idstack.pop();
    auto operand1Id = idstack.top(); //left operand
    idstack.pop();
    auto op = std::string(node[AST_TAG_ARITHOP_TYPE]->toString());
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_EXPR + 
        "\\noperator : " + op + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(operand2Id) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(operand1Id) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitRelExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_RELEXPR) == 0);
    auto operand2Id = idstack.top(); //right operand
    idstack.pop();
    auto operand1Id = idstack.top(); //left operand
    idstack.pop();
    auto op = std::string(node[AST_TAG_RELOP_TYPE]->toString());
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_EXPR + 
        "\\noperator : " + op + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(operand2Id) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(operand1Id) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitBoolExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_BOOLEXPR) == 0);
    auto operand2Id = idstack.top(); //right operand
    idstack.pop();
    auto operand1Id = idstack.top(); //left operand
    idstack.pop();
    auto op = std::string(node[AST_TAG_BOOLOP_TYPE]->toString());
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_EXPR + 
        "\\noperator : " + op + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(operand2Id) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(operand1Id) + ";");
    idstack.push(id++);    
}

void GraphTreeVisitor::visitTerm( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM) == 0);
    auto childId = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_TERM + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(childId) +";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitTermParensExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_PARENS_EXPR) == 0);
    unsigned childId = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_TERM + "\\n(...)\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(childId) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitTermMinusExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_MINUS_EXPR) == 0);
    auto childId = idstack.top();
    idstack.pop();    
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_TERM + "\\nunary minus\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(childId) +";");
    idstack.push(id++);    
}

void GraphTreeVisitor::visitTermNotExpr( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_NOT_EXPR) == 0);
    auto childId = idstack.top();
    idstack.pop();     
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_TERM + "\\nboolean not\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(childId) +";");
    idstack.push(id++);      
}

void GraphTreeVisitor::visitTermPlusPlusLvalue( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_PLUS_PLUS_LVALUE) == 0);
    auto childId = idstack.top();
    idstack.pop();      
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_TERM + "\\nprefix ++\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(childId) +";");
    idstack.push(id++);  
}

void GraphTreeVisitor::visitTermMinusMinusLvalue( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_MINUS_MINUS_LVALUE) == 0);
    auto childId = idstack.top();
    idstack.pop();     
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_TERM + "\\nprefix --\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(childId) +";");
    idstack.push(id++);  
}

void GraphTreeVisitor::visitTermLvaluePlusPlus( Object& node){
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_LVALUE_PLUS_PLUS) == 0);
    auto childId = idstack.top();
    idstack.pop();     
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_TERM + "\\npostfix ++\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(childId) +";");
    idstack.push(id++);  
}

void GraphTreeVisitor::visitTermLvalueMinusMinus( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_TERM_LVALUE_MINUS_MINUS) == 0);
    auto childId = idstack.top();
    idstack.pop();     
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_TERM + "\\npostfix --\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(childId) +";");
    idstack.push(id++);  
}

void GraphTreeVisitor::visitAssignExpr( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ASSIGNEXPR) == 0);
    unsigned expr = idstack.top();
    idstack.pop();
    unsigned lvalue = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_ASSIGNEXPR + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(lvalue) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitPrimary( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_PRIMARY) == 0);
    unsigned child = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_PRIMARY + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitLvalueId( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_LVALUE_ID) == 0);
    std::string value = node[AST_TAG_ID]->toString();
    vertices.push_back(std::to_string(id++) + "[label=\"" + AST_TAG_ID + "\\nvalue=" + value + "\"];");
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_LVALUE + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(id - 1) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitLvalueGlobalId( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_LVALUE_GLOBAL_ID) == 0);
    std::string value = node[AST_TAG_GLOBALID]->toString();
    vertices.push_back(std::to_string(id++) + "[label=\"" + AST_TAG_GLOBALID + "\\nvalue=" + value + "\"];");
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_LVALUE + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(id - 1) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitLvalueLocalId( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_LVALUE_LOCAL_ID) == 0);
    std::string value = node[AST_TAG_LOCALID]->toString();
    vertices.push_back(std::to_string(id++) + "[label=\"" + AST_TAG_LOCALID + "\\nvalue=" + value + "\"];");
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_LVALUE + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(id - 1) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitLvalueMember( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_LVALUE_MEMBER) == 0);
    unsigned child = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_LVALUE + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitMemberId( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_MEMBER_ID) == 0);
    unsigned child = idstack.top();
    idstack.pop();
    std::string m_id = node[AST_TAG_ID]->toString();
    vertices.push_back(std::to_string(id++) + "[label=\"" + AST_TAG_ID + "\\nvalue=" + m_id + "\"];");
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_MEMBER + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(id - 1) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitMemberExpr( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_MEMBER_EXPR) == 0);
    unsigned expr = idstack.top();
    idstack.pop();
    unsigned lvalue = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_MEMBER + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(lvalue) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CALL) == 0);
    unsigned callsuffix = idstack.top();
    idstack.pop();
    unsigned lvalue = idstack.top();
    idstack.pop();\
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_CALL + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(lvalue) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(callsuffix) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitMultiCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_MULTICALL) == 0);
    unsigned elist = -1;
    if (node[AST_TAG_ELIST] != nullptr) {
        elist = idstack.top();
        idstack.pop();
    }
    unsigned callRight = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_MULTICALL + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(callRight) + ";");
    if (node[AST_TAG_ELIST] != nullptr) edges.push_back(std::to_string(id) + "--" + std::to_string(elist) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitFdefCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FDEFCALL) == 0);
    unsigned elist = -1;
    if (node[AST_TAG_ELIST] != nullptr) {
        elist = idstack.top();
        idstack.pop();
    }
    unsigned fdef = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_FDEFCALL + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(fdef) + ";");
    if (node[AST_TAG_ELIST] != nullptr) edges.push_back(std::to_string(id) + "--" + std::to_string(elist) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitNormCallSuffix( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_NORMCALLSUFFIX) == 0);
    unsigned child = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_CALLSUFFIX + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitMethodCallSuffix( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_METHODCALLSUFFIX) == 0);
    unsigned child = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_CALLSUFFIX + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitNormCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_NORMCALL) == 0);
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_NORMCALL+"(...)" + "\"];");
    if (node[AST_TAG_ELIST] != nullptr) {
        unsigned elist = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(elist) + ";");
    } 
    idstack.push(id++);
}
void GraphTreeVisitor::visitMethodCall( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_METHODCALL) == 0);
    std::string m_id = node[AST_TAG_ID]->toString();
    vertices.push_back(std::to_string(id++) + "[label=\"" + AST_TAG_ID + "\\nvalue=" + m_id + "\"];");
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_METHODCALL+"(...)" + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(id-1) + ";");
    if (node[AST_TAG_ELIST] != nullptr) {
        unsigned elist = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(elist) + ";");
    }  
    idstack.push(id++);
}
void GraphTreeVisitor::visitElist( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ELIST) == 0);
    unsigned child = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_ELIST + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
    idstack.push(id++);
}
void GraphTreeVisitor::visitElistNotEmpty( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ELISTNOTEMPTY) == 0);
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        unsigned tmp = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(tmp));
    }
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_ELISTNOTEMPTY + "\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitArgument(Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_ARGUMENT) == 0);

    unsigned expr = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id++) + "[label=\"" + AST_TAG_ARGUMENT + "\"];");
    if (node[AST_TAG_ID] != nullptr) {
        vertices.push_back(std::to_string(id) + "[label=\"" + std::string(node[AST_TAG_ID]->toString())+"\"];");
        edges.push_back(std::to_string(id) + "--" + std::to_string(id-1) + ";");
    }
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");
    
    idstack.push(id++);
}

void GraphTreeVisitor::visitObjectDef( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_OBJECTDEF) == 0);
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_OBJECTDEF + "\"];");
    if (node[AST_TAG_OBJECTDINNER] != nullptr) {
        unsigned objectdinner = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(objectdinner) + ";");    
    }
    idstack.push(id++);
}

void GraphTreeVisitor::visitObjElistNotEmpty(Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_OBJELISTNOTEMPTY) == 0);
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        unsigned tmp = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(tmp));
    }
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_OBJELISTNOTEMPTY + "\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitObjectDinnerObjElistnotempty(Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONT_LIST) == 0);
    unsigned child = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_OBJECTDINNER + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitObjectDinnerIndexed( Object& node) {
    assert(strcmp(node[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_CONT_INDEXED) == 0);
    unsigned child = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_OBJECTDINNER + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitCommaIndexed( Object& node) {

    for (unsigned int i = 0; i < node[AST_TAG_CHILDREN]->toNumber(); i++) {
        unsigned tmp = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(tmp));
    }
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_ELISTNOTEMPTY + "\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitIndexedElem( Object& node) {
    int key = idstack.top();
    idstack.pop();

    int value = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\""+AST_TAG_INDEXEDELEM+"\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(key) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(value) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitBlock( Object& node) {
    int stmts = -1;

    if (node[AST_TAG_STMTS] != nullptr) {
        stmts = idstack.top();
        idstack.pop();
    }
    
    vertices.push_back(std::to_string(id) + "[label=\""+AST_TAG_BLOCK+"\"];"); 
    if (stmts != -1)
        edges.push_back(std::to_string(id) + "--" + std::to_string(stmts) + ";");
        
    idstack.push(id++);
}

void GraphTreeVisitor::visitFuncDef( Object& node) {
    int block = idstack.top();
    idstack.pop();

    int idlist = -1;
    if (node[AST_TAG_IDLIST] != nullptr) {
        idlist = idstack.top();
        idstack.pop();
    }

    int funcprefix = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\""+AST_TAG_FUNCDEF+"\"];");

    edges.push_back(std::to_string(id) + "--" + std::to_string(funcprefix) + ";");
    if (idlist != -1)
        edges.push_back(std::to_string(id) + "--" + std::to_string(idlist) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(block) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitFuncPrefix( Object& node) {
    std::string tmp = std::to_string(id) + "[label=\"function : ";
    
    if (node[AST_TAG_CHILD] != nullptr) {
        const Object* obj = node[AST_TAG_CHILD]->toObject();
        if (!strcmp((*obj)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FUNCNAME_ID)) {
            std::string funcname = (*obj)[AST_TAG_ID]->toString();
            tmp += funcname;        
        } else {
            tmp += "inline";
            int il = idstack.top();
            idstack.pop();
            vertices.push_back(std::to_string(id) + "[label=\"funcname\"];");
            edges.push_back(std::to_string(id) + "--" + std::to_string(il) + ";");
        }
        
    }
    tmp += "\"];";
    vertices.push_back(tmp);
    idstack.push(id++);
}

void GraphTreeVisitor::visitFuncName( Object& node) {
    return;
}

void GraphTreeVisitor::visitConst( Object& node) {
    unsigned child = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_CONST + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitConstNumconst( Object& node) {
    double value = node[AST_TAG_VALUE]->toNumber();
    vertices.push_back(std::to_string(id) + "[label=\"numconst\\nvalue=" + std::to_string(value) + "\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitConstStringconst( Object& node) {
    std::string st = node[AST_TAG_VALUE]->toString();
    std::string tmp;
    for (auto it : st) {
        switch(it) {
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
                tmp += it;
                break;
        }       
    }
    vertices.push_back(std::to_string(id) + "[label=\"stringconst\\nvalue=" + tmp + "\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitConstBoolconst( Object& node) {
    bool value = node[AST_TAG_VALUE]->toBoolean();
    std::string st = value ? "true" : "false";
    vertices.push_back(std::to_string(id) + "[label=\"boolconst\\nvalue=" + st + "\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitConstNil( Object& node) {
    vertices.push_back(std::to_string(id) + "[label=\"nil\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitID( Object& node)  {
    std::string tmp = node[AST_TAG_ID]->toString();
    vertices.push_back(std::to_string(id)+ "[label=\"" + tmp + "\"]");
    idstack.push(id++);
} 

void GraphTreeVisitor::visitCommaIdList( Object& node) {
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        unsigned tmp = idstack.top();
        idstack.pop();
        edges.push_back(std::to_string(id) + "--" + std::to_string(tmp));
    }
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_COMMAIDLIST + "\"];");
    idstack.push(id++);   
}

void  GraphTreeVisitor::visitFormal(Object& node) {

    unsigned expr = 0;
    if (node[AST_TAG_EXPR] != nullptr) {
        expr = idstack.top();
        idstack.pop();
    }
    vertices.push_back(std::to_string(id++) + "[label=\"" + std::string(node[AST_TAG_ID]->toString()) + "\"];");
    vertices.push_back(std::to_string(id) + "[label=\"" + AST_TAG_FORMAL + "\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(id-1) + ";");
    if (expr != 0)
        edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");
    idstack.push(id++); 
}

void GraphTreeVisitor::visitIfPrefix( Object& node) {
    int expr = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"ifprefix\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitElsePrefix( Object& node) {
    vertices.push_back(std::to_string(id) + "[label=\"else\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitIfStmt( Object& node) {
    int ifstmt = idstack.top();
    idstack.pop();

    int ifprefix = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"ifstmt\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(ifstmt) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(ifprefix) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitIfStmtElseStmt( Object& node) {
    int elsestmt = idstack.top();
    idstack.pop();
    
    int elseprefix = idstack.top();
    idstack.pop();

    int ifstmt = idstack.top();
    idstack.pop();

    int ifprefix = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"ifstmt\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(ifstmt) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(ifprefix) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(elseprefix) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(elsestmt) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitWhileStart( Object& node) {
    return;
}

void GraphTreeVisitor::visitWhileCond( Object& node) {
    int cond = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"whilecond\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(cond) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitWhileStmt( Object& node) {
    int stmt = idstack.top();
    idstack.pop();

    int whilecond = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"whilestmt\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(stmt) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(whilecond) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitForPrefix( Object& node) {
    int expr = idstack.top();
    idstack.pop();

    int elist = -1;
    if (node[AST_TAG_ELIST] != nullptr) {
        elist = idstack.top();
        idstack.pop();
    }
    vertices.push_back(std::to_string(id) + "[label=\"forprefix\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");
    if (elist != -1)
        edges.push_back(std::to_string(id) + "--" + std::to_string(elist) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitForStmt( Object&node) {
    int stmt = idstack.top();
    idstack.pop();

    int elist = -1;
    if (node[AST_TAG_ELIST] != nullptr) {
        elist = idstack.top();
        idstack.pop();
    }

    int forprefix = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"forstmt\"];");

    edges.push_back(std::to_string(id) + "--" + std::to_string(stmt) + ";");
    if (elist != -1)
        edges.push_back(std::to_string(id) + "--" + std::to_string(elist) + ";");
    edges.push_back(std::to_string(id) + "--" + std::to_string(forprefix) + ";");
    idstack.push(id++);
}

void GraphTreeVisitor::visitReturnStmt( Object& node) {
    vertices.push_back(std::to_string(id) + "[label=\"return\"];");
    idstack.push(id++);
}

void GraphTreeVisitor::visitReturnStmtExpr( Object& node) {
    int expr = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"return\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");

    idstack.push(id++);
}

void GraphTreeVisitor::visitEscapeId(Object& node) {
    std::string ID = node[AST_TAG_ID]->toString();

    vertices.push_back(std::to_string(id) + "[label=\"~" + ID + "\"];");   

    idstack.push(id++);
}

void GraphTreeVisitor::visitEscapeExpr(Object& node) {
    int expr = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"~\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");

    idstack.push(id++);
}

void GraphTreeVisitor::visitQuasiQuotes(Object& node) {
    int body = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"<< >>\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(body) + ";");

    idstack.push(id++);
}

void GraphTreeVisitor::visitQuotedRules(Object& node) {
    int child = idstack.top();
    idstack.pop();

    vertices.push_back(std::to_string(id) + "[label=\"quoted rules\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(child) + ";");

    idstack.push(id++);
} 

void GraphTreeVisitor::visitInline( Object& node) {
    int expr = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"inline\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");

    idstack.push(id++);
}

void GraphTreeVisitor::visitUnparsed( Object& node) {
    int expr = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"unparsed\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");

    idstack.push(id++);
}

void GraphTreeVisitor::visitCompiledString( Object& node) {
    int expr = idstack.top();
    idstack.pop();
    vertices.push_back(std::to_string(id) + "[label=\"compiledstring\"];");
    edges.push_back(std::to_string(id) + "--" + std::to_string(expr) + ";");

    idstack.push(id++);
}

void GraphTreeVisitor::visitValueStorage(Object& node) {
    std::string value = node[AST_TAG_VALUE]->makeString();
    vertices.push_back(std::to_string(id) + "[label=\"valuestorage\\nvalue=" + value + "\"];");
    idstack.push(id++);
}