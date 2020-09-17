#ifndef TREEVISITOR_H
#define TREEVISITOR_H

#include "Object.h"
#include "TreeTags.h"

class TreeVisitor {
	public:
    virtual void visitProgram( Object& node) = 0;
    virtual void visitStmts( Object& node) = 0;
    virtual void visitStmt( Object& node) = 0;
    virtual void visitBreak( Object& node) = 0;
    virtual void visitContinue( Object& node) = 0;

    virtual void visitExpr( Object& node) = 0;
    virtual void visitArithExpr( Object& node) = 0;
    virtual void visitRelExpr( Object& node) = 0;
    virtual void visitBoolExpr( Object& node) = 0;

    virtual void visitTerm( Object& node) = 0;
    virtual void visitTermParensExpr( Object& node) = 0;
    virtual void visitTermMinusExpr( Object& node) = 0;
    virtual void visitTermNotExpr( Object& node) = 0;
    virtual void visitTermPlusPlusLvalue( Object& node) = 0;
    virtual void visitTermMinusMinusLvalue( Object& node) = 0;
    virtual void visitTermLvaluePlusPlus( Object& node) = 0;
    virtual void visitTermLvalueMinusMinus( Object& node) = 0;  
        
    virtual void visitAssignExpr( Object& node) = 0;
    virtual void visitPrimary( Object& node) = 0;
    virtual void visitLvalueId( Object& node) = 0;
    virtual void visitLvalueGlobalId( Object& node) = 0;
    virtual void visitLvalueLocalId( Object& node) = 0;
    virtual void visitLvalueMember( Object& node) = 0;
    virtual void visitMemberId( Object& node) = 0;
    virtual void visitMemberExpr( Object& node) = 0;
    virtual void visitCall( Object& node) = 0;
    virtual void visitMultiCall( Object& node) = 0;
    virtual void visitFdefCall( Object& node) = 0;
    virtual void visitNormCallSuffix( Object& node) = 0;
    virtual void visitMethodCallSuffix( Object& node) = 0;
    virtual void visitNormCall( Object& node) = 0;
    virtual void visitMethodCall( Object& node) = 0;
    virtual void visitElist( Object& node) = 0;
    virtual void visitElistNotEmpty( Object& node) = 0;
    virtual void visitArgument( Object& node) = 0;
    virtual void visitObjectDef( Object& node) = 0;
    virtual void visitObjElistNotEmpty( Object& node) = 0;
    virtual void visitObjectDinnerObjElistnotempty( Object& node) = 0;
    virtual void visitObjectDinnerIndexed( Object& node) = 0;   
    virtual void visitCommaIndexed( Object& node) = 0;
    virtual void visitIndexedElem( Object& node) = 0;   
    virtual void visitBlock( Object& node) = 0;
    virtual void visitFuncDef( Object& node) = 0;
    virtual void visitFuncPrefix( Object& node) = 0;
    virtual void visitFuncName( Object& node) = 0;
    virtual void visitConst( Object& node) = 0;
    virtual void visitConstNumconst( Object& node) = 0;
    virtual void visitConstStringconst( Object& node) = 0;
    virtual void visitConstBoolconst( Object& node) = 0;
    virtual void visitConstNil( Object& node) = 0;    
    virtual void visitID( Object& node) = 0;
    virtual void visitCommaIdList( Object& node) = 0;
    virtual void visitFormal( Object& node) = 0;
    virtual void visitIfPrefix( Object& node) = 0;
    virtual void visitElsePrefix( Object& node) = 0;
    virtual void visitIfStmt( Object& node) = 0;
    virtual void visitIfStmtElseStmt( Object& node) = 0;
    virtual void visitWhileStart( Object& node) = 0;
    virtual void visitWhileCond( Object& node) = 0;
    virtual void visitWhileStmt( Object& noverrideode) = 0;
    virtual void visitForPrefix( Object& node) = 0;
    virtual void visitForStmt( Object&node) = 0;
    virtual void visitReturnStmt( Object& node) = 0;
    virtual void visitReturnStmtExpr( Object& node) = 0;    
    
    virtual void visitInline( Object& node) = 0;
    virtual void visitUnparsed(Object& node) = 0;
    virtual void visitCompiledString(Object& node) = 0;

    virtual void visitQuasiQuotes(Object& node) = 0;
    virtual void visitQuotedRules(Object& node) = 0; 
    virtual void visitEscapeId(Object& node) = 0;
    virtual void visitEscapeExpr(Object& node) = 0;

    virtual void visitValueStorage(Object& node) = 0;


   virtual TreeVisitor* Clone(void) const = 0;
   TreeVisitor(void) {
       
   }
   TreeVisitor(const TreeVisitor&)=default;
};

#endif