#include "CopyTreeVisitor.h"
#include "SetParentTreeVisitor.h"
#include "error_handler.h"
#include <string.h>
#include <assert.h>

void CopyTreeVisitor::copyNodeInNewTree(Object& node){
    newTree = new Object();
    *newTree = node;
    newTree->remove(PARENT_FIELD);   
    if(&node != treeToCopy)
        node.set(COPIED_TREE, newTree);   
}

void CopyTreeVisitor::stealFieldFrom(Object& node, std::string field){
    if(node[field] != nullptr){
        auto tmpNode = node[field]->toObjectNoConst()->getAndRemove(COPIED_TREE);
        newTree->set(field, tmpNode);
    }
}

CopyTreeVisitor::CopyTreeVisitor(Object *_treeToCopy) {
    newTree = nullptr;
    treeToCopy = _treeToCopy;
}

void CopyTreeVisitor::visitProgram(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD);
}

void CopyTreeVisitor::visitChildren(Object& node) {
    int numChildren = node[AST_TAG_NUMCHILDREN]->toNumber();
    copyNodeInNewTree(node);

    newTree->set(AST_TAG_NUMCHILDREN, Value((double)numChildren));

    for (int i = 0; i < numChildren; i++) {
        auto tmp = (node[i]->toObjectNoConst())->getAndRemove(COPIED_TREE);
        newTree->set(i, tmp);
    }

    if(&node != treeToCopy)
        node.set(COPIED_TREE, newTree);

}

void CopyTreeVisitor::visitStmts(Object& node) { 
    visitChildren(node);
}

void CopyTreeVisitor::visitStmt(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD);
}

void CopyTreeVisitor::visitExpr(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD); 
}

void CopyTreeVisitor::visitBinaryExpr(Object& node){
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_LEFTEXPR); 
    stealFieldFrom(node, AST_TAG_RIGHTEXPR); 
}

void CopyTreeVisitor::visitArithExpr(Object& node) { 
    visitBinaryExpr(node);
}

void CopyTreeVisitor::visitRelExpr(Object& node) { 
    visitBinaryExpr(node);  
}

void CopyTreeVisitor::visitBoolExpr(Object& node) { 
    visitBinaryExpr(node);
}

void CopyTreeVisitor::visitTerm(Object& node) { 
    copyNodeInNewTree(node);  
    stealFieldFrom(node, AST_TAG_CHILD);  
}

void CopyTreeVisitor::visitTermExpr(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_EXPR);  
}

void CopyTreeVisitor::visitTermParensExpr(Object& node) { 
    visitTermExpr(node);
}

void CopyTreeVisitor::visitTermMinusExpr(Object& node) { 
    visitTermExpr(node);
}

void CopyTreeVisitor::visitTermNotExpr(Object& node) { 
    visitTermExpr(node);
}

void CopyTreeVisitor::visitTermLvalue(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_LVALUE);
}

void CopyTreeVisitor::visitTermPlusPlusLvalue(Object& node) { 
    visitTermLvalue(node);
}

void CopyTreeVisitor::visitTermMinusMinusLvalue(Object& node) {
    visitTermLvalue(node);
}

void CopyTreeVisitor::visitTermLvaluePlusPlus(Object& node) { 
    visitTermLvalue(node);
}

void CopyTreeVisitor::visitTermLvalueMinusMinus(Object& node) { 
    visitTermLvalue(node);
}  
    
void CopyTreeVisitor::visitAssignExpr(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_LVALUE);
    stealFieldFrom(node, AST_TAG_EXPR);
}

void CopyTreeVisitor::visitPrimary(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD);
}

void CopyTreeVisitor::visitLvalueId(Object& node) {
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitLvalueGlobalId(Object& node) {
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitLvalueLocalId(Object& node) { 
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitLvalueMember(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_MEMBER);
}

void CopyTreeVisitor::visitMemberId(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CALLER);
}

void CopyTreeVisitor::visitMemberExpr(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CALLER);
    stealFieldFrom(node, AST_TAG_EXPR);    
}

void CopyTreeVisitor::visitCall(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_LVALUE);
    stealFieldFrom(node, AST_TAG_CALLSUFFIX);     
}

void CopyTreeVisitor::visitMultiCall(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CALL);
    stealFieldFrom(node, AST_TAG_ELIST);        
}

void CopyTreeVisitor::visitFdefCall(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_FUNCDEF);
    stealFieldFrom(node, AST_TAG_ELIST);     
}

void CopyTreeVisitor::visitNormCallSuffix(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_NORMCALL);    
}

void CopyTreeVisitor::visitMethodCallSuffix(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_METHODCALL);        
}

void CopyTreeVisitor::visitNormCall(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_ELIST);
}

void CopyTreeVisitor::visitMethodCall(Object& node) {
    visitNormCall(node);
}

void CopyTreeVisitor::visitElist(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_ELISTNOTEMPTY);    
}

void CopyTreeVisitor::visitElistNotEmpty(Object& node) { 
    visitChildren(node);
}

void CopyTreeVisitor::visitArgument(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_EXPR);           
}

void CopyTreeVisitor::visitObjectDef(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_OBJECTDINNER);     
}

void CopyTreeVisitor::visitObjElistNotEmpty( Object& node) { 
    visitChildren(node);
}

void CopyTreeVisitor::visitObjectDinnerObjElistnotempty( Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_OBJELISTNOTEMPTY);        
}

void CopyTreeVisitor::visitObjectDinnerIndexed(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_INDEXED);      
}

void CopyTreeVisitor::visitCommaIndexed(Object& node) {
    visitChildren(node);
}

void CopyTreeVisitor::visitIndexedElem(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_OBJECT_KEY);       
    stealFieldFrom(node, AST_TAG_OBJECT_VALUE);   
}

void CopyTreeVisitor::visitBlock(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_STMTS);       
}

void CopyTreeVisitor::visitFuncDef(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_IDLIST);       
    stealFieldFrom(node, AST_TAG_BLOCK);
    stealFieldFrom(node, AST_TAG_FUNCPREFIX);
}

void CopyTreeVisitor::visitFuncPrefix(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD);       
}

void CopyTreeVisitor::visitFuncName(Object& node) { 
    copyNodeInNewTree(node);
     stealFieldFrom(node, AST_TAG_CHILD);
}

void CopyTreeVisitor::visitConst(Object& node) { 
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitConstNumconst(Object& node) { 
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitConstStringconst(Object& node) { 
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitConstBoolconst(Object& node) { 
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitConstNil(Object& node) { 
    copyNodeInNewTree(node);
}   

void CopyTreeVisitor::visitID(Object& node) { 
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitCommaIdList(Object& node) { 
    visitChildren(node);
}

void CopyTreeVisitor::visitFormal(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_EXPR);
}

void CopyTreeVisitor::visitIfPrefix(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_EXPR);     
}

void CopyTreeVisitor::visitElsePrefix(Object& node) { 
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitIfStmt(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_IFPREFIX); 
    stealFieldFrom(node, AST_TAG_IFSTMT_IFBODY);  
}

void CopyTreeVisitor::visitIfStmtElseStmt(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_IFPREFIX); 
    stealFieldFrom(node, AST_TAG_IFSTMT_IFBODY);
    stealFieldFrom(node, AST_TAG_ELSEPREFIX); 
    stealFieldFrom(node, AST_TAG_IFSTMT_ELSEBODY);   
}

void CopyTreeVisitor::visitWhileStart(Object& node) {
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitWhileCond(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_EXPR);
}

void CopyTreeVisitor::visitWhileStmt(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_WHILESTART);
    stealFieldFrom(node, AST_TAG_WHILECOND);
    stealFieldFrom(node, AST_TAG_STMT); 
}

void CopyTreeVisitor::visitForPrefix(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_ELIST);    
    stealFieldFrom(node, AST_TAG_EXPR);
}

void CopyTreeVisitor::visitForStmt(Object&node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_FORPREFIX);    
    stealFieldFrom(node, AST_TAG_ELIST);    
    stealFieldFrom(node, AST_TAG_STMT);   
}   

void CopyTreeVisitor::visitReturnStmt(Object& node) { 
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitReturnStmtExpr(Object& node) { 
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_EXPR);
}  

void CopyTreeVisitor::visitBreak(Object& node) {
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitContinue(Object& node) {
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitInline(Object& node){
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD);
}

void CopyTreeVisitor::visitUnparsed(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD);
}

void CopyTreeVisitor::visitCompiledString(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD);
}

void CopyTreeVisitor::visitQuasiQuotes(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD);
}
void CopyTreeVisitor::visitQuotedRules(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_CHILD);
}

void CopyTreeVisitor::visitEscapeId(Object& node) {
    copyNodeInNewTree(node);
}

void CopyTreeVisitor::visitEscapeExpr(Object& node) {
    copyNodeInNewTree(node);
    stealFieldFrom(node, AST_TAG_EXPR);
}

void CopyTreeVisitor::visitValueStorage(Object& node) {
    copyNodeInNewTree(node);
}

TreeVisitor* CopyTreeVisitor::Clone(void) const {
    return new CopyTreeVisitor(treeToCopy);
}

Object* CopyTreeVisitor::getResult(){
    return newTree;
}