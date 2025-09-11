#ifndef TREEHOST_H
#define TREEHOST_H

#include "TreeVisitor.h"

class TreeHost {
    private:
    using Acceptor = std::function<void( Object&)>;
    using Acceptors = std::map<std::string, Acceptor>;

    Acceptors acceptors;
    TreeVisitor* visitor = nullptr;

    void accept(Value* vnode);
    
    void acceptProgram( Object& node);
    void acceptStmts( Object& node);
    void acceptStmt( Object& node);

    void acceptExpr( Object& node);
    void acceptArithExpr( Object& node);
    void acceptRelExpr( Object& node);
    void acceptBoolExpr( Object& node); 

    void acceptTerm( Object& node);
    void acceptTermParensExpr( Object& node);
    void acceptTermMinusExpr( Object& node);
    void acceptTermNotExpr( Object& node);
    void acceptTermPlusPlusLvalue( Object& node);
    void acceptTermMinusMinusLvalue( Object& node);
    void acceptTermLvaluePlusPlus( Object& node);
    void acceptTermLvalueMinusMinus( Object& node);   

    void acceptAssignExpr( Object& node);
    void acceptPrimary( Object& node);
    void acceptLvalueId( Object& node);
    void acceptLvalueGlobalId( Object& node);
    void acceptLvalueLocalId( Object& node);
    void acceptLvalueMember( Object& node);
    void acceptMemberId( Object& node);
    void acceptMemberExpr( Object& node);
    void acceptMultiCall( Object& node);
    void acceptCall( Object& node);
    void acceptFdefCall( Object& node);
    void acceptNormCallsuffix( Object& node);
    void acceptMethodCallsuffix( Object& node);
    void acceptNormCall( Object& node);
    void acceptMethodCall( Object& node);
    void acceptElist( Object& node);
    void acceptElistNotEmpty( Object& node);
    void acceptArgument(Object& node);
    void acceptObjElistNotEmpty(Object &node);
    void acceptObjectDef( Object& node);
    void acceptObjectDinnerObjElistNotEmpty( Object& node);
    void acceptObjectDinnerIndexed( Object& node);
    
    void acceptIndexed( Object& node);
    void acceptCommaIndexed( Object& node);
    void acceptIndexedElem( Object& node);   
    void acceptBlock( Object& node);
    void acceptFuncDef( Object& node);
    void acceptFuncPrefix( Object& node);
    void acceptFuncName( Object& node);
    void acceptConst( Object& node);
    void acceptID( Object& node);
    void acceptCommaIdList( Object& node);
    void acceptFormal(Object& node);
    void acceptIfPrefix( Object& node);   
    void acceptElsePrefix( Object& node);   
    void acceptIfStmt( Object& node);      
    void acceptWhileStart( Object& node);
    void acceptWhileCond( Object& node);
    void acceptWhileStmt( Object& node);
    void acceptForPrefix( Object& node);
    void acceptForStmt( Object& node);
    void acceptReturnStmt( Object& node);
    void acceptBreak( Object& node);
    void acceptContinue( Object& node);

    void acceptQuasiQuotes(Object& node);
    void acceptQuotedRules(Object& node);
    void acceptEscapeId(Object& node);
    void acceptEscapeExpr(Object& node);
    void acceptInline(Object& node);
    void acceptUnparsed( Object& node);
    void acceptCompiledString( Object& node);

    void acceptValueStorage(Object& node);

    void installAcceptor(const std::string& tag, const Acceptor& f);
    void installAllAcceptors();

    public:
    TreeHost();
    void accept(TreeVisitor* _visitor, Object& node);
};

#endif