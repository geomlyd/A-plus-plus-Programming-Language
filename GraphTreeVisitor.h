#ifndef GRAPHVISITOR_H
#define GRAPHVISITOR_H

#include "TreeVisitor.h"
#include <vector>
#include <stack>
#include <string>

class GraphTreeVisitor : public TreeVisitor {
    private:
    std::vector<std::string> edges;
    std::vector<std::string> vertices;
    std::stack<int> idstack;
    unsigned id = 0;
    public:
    GraphTreeVisitor();

    std::string getGraph();

    virtual void visitProgram( Object& node) override;
    virtual void visitStmts( Object& node) override;
    virtual void visitStmt( Object& node) override;
    virtual void visitBreak( Object& node) override;
    virtual void visitContinue( Object& node) override;

    virtual void visitExpr( Object& node) override;
    virtual void visitArithExpr( Object& node) override;
    virtual void visitRelExpr( Object& node) override;
    virtual void visitBoolExpr( Object& node) override;

    virtual void visitTerm( Object& node) override;
    virtual void visitTermParensExpr( Object& node) override;
    virtual void visitTermMinusExpr( Object& node) override;
    virtual void visitTermNotExpr( Object& node) override;
    virtual void visitTermPlusPlusLvalue( Object& node) override;
    virtual void visitTermMinusMinusLvalue( Object& node) override;
    virtual void visitTermLvaluePlusPlus( Object& node) override;
    virtual void visitTermLvalueMinusMinus( Object& node) override;  
        
    virtual void visitAssignExpr( Object& node) override;
    virtual void visitPrimary( Object& node) override;
    virtual void visitLvalueId( Object& node) override;
    virtual void visitLvalueGlobalId( Object& node) override;
    virtual void visitLvalueLocalId( Object& node) override;
    virtual void visitLvalueMember( Object& node) override;
    virtual void visitMemberId( Object& node) override;
    virtual void visitMemberExpr( Object& node) override;
    virtual void visitCall( Object& node) override;
    virtual void visitMultiCall( Object& node) override;
    virtual void visitFdefCall( Object& nElistode) override;
    virtual void visitNormCallSuffix( Object& node) override;
    virtual void visitMethodCallSuffix( Object& node) override;
    virtual void visitNormCall( Object& node) override;
    virtual void visitMethodCall( Object& node) override;
    virtual void visitElist( Object& node) override;
    virtual void visitElistNotEmpty( Object& node) override;
    virtual void visitArgument(Object& node) override;
    virtual void visitObjectDef( Object& node) override;
    virtual void visitObjElistNotEmpty( Object& node) override;
    virtual void visitObjectDinnerObjElistnotempty( Object& node) override;
    virtual void visitObjectDinnerIndexed( Object& node) override;
    
    virtual void visitCommaIndexed( Object& node) override;
    virtual void visitIndexedElem( Object& node) override;    
    virtual void visitBlock( Object& node) override;
    virtual void visitFuncDef( Object& node) override;
    virtual void visitFuncPrefix( Object& node) override;
    virtual void visitFuncName( Object& node) override;
    virtual void visitConst( Object& node) override;
    virtual void visitConstNumconst( Object& node) override;
    virtual void visitConstStringconst( Object& node) override;
    virtual void visitConstBoolconst( Object& node) override;
    virtual void visitConstNil( Object& node) override;   
    virtual void visitID( Object& node) override;
    virtual void visitCommaIdList( Object& node) override;
    virtual void visitFormal( Object& node) override;
    virtual void visitIfPrefix( Object& node) override;
    virtual void visitElsePrefix( Object& node) override;
    virtual void visitIfStmt( Object& node) override;
    virtual void visitIfStmtElseStmt( Object& node) override;
    virtual void visitWhileStart( Object& node) override;
    virtual void visitWhileCond( Object& node) override;
    virtual void visitWhileStmt( Object& node) override;
    virtual void visitForPrefix( Object& node) override;
    virtual void visitForStmt( Object&node) override;
    virtual void visitReturnStmt( Object& node) override;
    virtual void visitReturnStmtExpr( Object& node) override;

    virtual void visitQuasiQuotes(Object& node) override;
    virtual void visitQuotedRules(Object& node) override;  
    virtual void visitEscapeId(Object& node) override;
    virtual void visitEscapeExpr(Object& node) override;  
    virtual void visitInline( Object& node) override;
    virtual void visitUnparsed( Object& node) override;
    virtual void visitCompiledString( Object& node) override;

    virtual void visitValueStorage(Object& node) override;
    
    virtual TreeVisitor* Clone(void) const override;
};

#endif