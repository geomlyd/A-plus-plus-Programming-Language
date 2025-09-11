#include "SetParentTreeVisitor.h"

void SetParentTreeVisitor::visitProgram(Object& node) {
    if(node[AST_TAG_STMTS] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitStmts(Object& node) {    
    setParent(node, node[AST_TAG_NUMCHILDREN]->toNumber());
}

void SetParentTreeVisitor::visitStmt(Object& node) {
    if(node[AST_TAG_CHILD] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitMultiCall(Object& node) {
    if(node[AST_TAG_ELIST] != nullptr)
        setParent(node, 2);
    else
        setParent(node, 1);
}

void SetParentTreeVisitor::visitFdefCall(Object& node) {
    if(node[AST_TAG_ELIST] != nullptr)
        setParent(node, 2);
    else
        setParent(node, 1);
}

void SetParentTreeVisitor::visitNormCall(Object& node) {
    if(node[AST_TAG_ELIST] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitMethodCall(Object& node) {
    if(node[AST_TAG_ELIST] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitElist(Object& node) {
    if(node[AST_TAG_ELISTNOTEMPTY] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitElistNotEmpty(Object& node) {
    setParent(node, node[AST_TAG_NUMCHILDREN]->toNumber());
}

void SetParentTreeVisitor::visitObjectDef(Object& node) {
    if(node[AST_TAG_OBJECTDINNER] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitCommaIndexed(Object& node) {
    setParent(node, node[AST_TAG_NUMCHILDREN]->toNumber());
}

void SetParentTreeVisitor::visitBlock(Object& node) {
    if(node[AST_TAG_STMTS] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitFuncDef(Object& node) {
    if(node[AST_TAG_IDLIST] != nullptr)
        setParent(node, 3);
    else
        setParent(node, 2);
}

void SetParentTreeVisitor::visitFuncPrefix(Object& node) {
    if(node[AST_TAG_CHILD] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitFuncName(Object& node) {
    if(node[AST_TAG_CHILD] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitCommaIdList(Object& node) {
    setParent(node, node[AST_TAG_NUMCHILDREN]->toNumber());
}

void SetParentTreeVisitor::visitFormal(Object& node) {
    if(node[AST_TAG_EXPR] != nullptr)
        setParent(node, 1);
    else
        setParent(node, 0);
}

void SetParentTreeVisitor::visitObjElistNotEmpty(Object& node) {
    setParent(node, node[AST_TAG_NUMCHILDREN]->toNumber());    
}

void SetParentTreeVisitor::visitForStmt(Object& node) {
    if(node[AST_TAG_ELIST] != nullptr)
        setParent(node, 3);
    else
        setParent(node, 2);
}

void SetParentTreeVisitor::visitForPrefix(Object& node) {
    if(node[AST_TAG_ELIST] != nullptr)
        setParent(node, 2);
    else
        setParent(node, 1);
}