#include "TreeHost.h"
#include <vector>
#include <stdexcept>
#include "error_handler.h"

TreeHost::TreeHost() {
    installAllAcceptors();
}

void TreeHost::accept(Value *vnode) {
    if (vnode == nullptr)
        throw std::runtime_error("trying to accept null node");
    else if (!vnode->isObject())
        throw std::runtime_error("trying to accept non object node");
    
    Object *node = vnode->toObjectNoConst();

    if ((*node)[AST_TAG_SUBTYPE_KEY] == nullptr) {
        throw std::runtime_error("trying to accept node with no subtype");
    }
    else if (!((*node)[AST_TAG_SUBTYPE_KEY]->isString())) {
        throw std::runtime_error("trying to accept node with non string subtype");
    }
    else {
        if (acceptors.find((*node)[AST_TAG_SUBTYPE_KEY]->toString()) == acceptors.end())
            throw std::runtime_error("trying to accept node with non existent subtype");
    }

    acceptors[(*node)[AST_TAG_SUBTYPE_KEY]->toString()](*node);
}    

void TreeHost::installAcceptor(const std::string& tag, const Acceptor& f) {
    acceptors[tag] = f;
}

void TreeHost::acceptProgram( Object& node) {
    if(node[AST_TAG_CHILD] != nullptr)
        accept(node[AST_TAG_CHILD]);
    visitor->visitProgram(node);
}

void TreeHost::acceptStmts( Object& node){
    if (node[AST_TAG_NUMCHILDREN] == nullptr) {
        throw std::runtime_error("acceptStmts has no children");
    }

    for (int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        accept(node[i]);
    }
    visitor->visitStmts(node);
}

void TreeHost::acceptStmt( Object& node){    
    if(node[AST_TAG_CHILD] != nullptr)
        accept(node[AST_TAG_CHILD]);

    visitor->visitStmt(node);     
}

void TreeHost::acceptExpr( Object& node){
    if (node[AST_TAG_CHILD] == nullptr) 
        throw std::runtime_error("acceptExpr has no child");    

    accept(node[AST_TAG_CHILD]);

    visitor->visitExpr(node);
}

void TreeHost::acceptArithExpr( Object& node){
    if (node[AST_TAG_LEFTEXPR] == nullptr) 
        throw std::runtime_error("acceptArithExpr has no left expression");
    else if (node[AST_TAG_RIGHTEXPR] == nullptr)
        throw std::runtime_error("acceptArithExpr has no right expression");
    
    accept(node[AST_TAG_LEFTEXPR]);
    accept(node[AST_TAG_RIGHTEXPR]);
    
    visitor->visitArithExpr(node);
}

void TreeHost::acceptRelExpr( Object& node){
    if (node[AST_TAG_LEFTEXPR] == nullptr) 
        throw std::runtime_error("acceptRelExpr has no left expression");
    else if (node[AST_TAG_RIGHTEXPR] == nullptr)
        throw std::runtime_error("acceptRelExpr has no right expression");   

    accept(node[AST_TAG_LEFTEXPR]);
    accept(node[AST_TAG_RIGHTEXPR]);
    
    visitor->visitRelExpr(node);
}

void TreeHost::acceptBoolExpr( Object& node){
    if (node[AST_TAG_LEFTEXPR] == nullptr) 
        throw std::runtime_error("acceptBoolExpr has no left expression");
    else if (node[AST_TAG_RIGHTEXPR] == nullptr)
        throw std::runtime_error("acceptBoolExpr has no right expression");       

    accept(node[AST_TAG_LEFTEXPR]);
    accept(node[AST_TAG_RIGHTEXPR]);
    
    visitor->visitBoolExpr(node);
}

void TreeHost::acceptTerm( Object& node){
    if (node[AST_TAG_CHILD] == nullptr)
        throw std::runtime_error("acceptTerm has no child");     

    accept(node[AST_TAG_CHILD]);

    visitor->visitTerm(node);
}

void TreeHost::acceptTermParensExpr( Object& node){
    if (node[AST_TAG_EXPR] == nullptr)
        throw std::runtime_error("acceptTermParensExpr has no expr");

    accept(node[AST_TAG_EXPR]);

    visitor->visitTermParensExpr(node);
}

void TreeHost::acceptTermMinusExpr( Object& node){
    if (node[AST_TAG_EXPR] == nullptr)
        throw std::runtime_error("acceptTermMinusExpr has no expr");      

    accept(node[AST_TAG_EXPR]);

    visitor->visitTermMinusExpr(node);
}

void TreeHost::acceptTermNotExpr( Object& node){
    if (node[AST_TAG_EXPR] == nullptr)
        throw std::runtime_error("acceptTermNotExpr has no expr");     

    accept(node[AST_TAG_EXPR]);

    visitor->visitTermNotExpr(node);
}

void TreeHost::acceptTermPlusPlusLvalue( Object& node){
    if (node[AST_TAG_LVALUE] == nullptr)
        throw std::runtime_error("acceptTermPlusPlusLvalue has no lvalue");     

    accept(node[AST_TAG_LVALUE]);

    visitor->visitTermPlusPlusLvalue(node);
}

void TreeHost::acceptTermMinusMinusLvalue( Object& node){
    if (node[AST_TAG_LVALUE] == nullptr)
        throw std::runtime_error("acceptTermMinusMinusLvalue has no lvalue");   

    accept(node[AST_TAG_LVALUE]);

    visitor->visitTermMinusMinusLvalue(node);
}

void TreeHost::acceptTermLvaluePlusPlus( Object& node){
    if (node[AST_TAG_LVALUE] == nullptr)
        throw std::runtime_error("acceptTermLvaluePlusPlus has no lvalue");    

    accept(node[AST_TAG_LVALUE]);

    visitor->visitTermLvaluePlusPlus(node);
}

void TreeHost::acceptTermLvalueMinusMinus( Object& node){
    if (node[AST_TAG_LVALUE] == nullptr)
        throw std::runtime_error("acceptTermLvalueMinusMinus has no lvalue");        

    accept(node[AST_TAG_LVALUE]);

    visitor->visitTermLvalueMinusMinus(node);
}

void TreeHost::acceptAssignExpr( Object& node) {
    if (node[AST_TAG_LVALUE] == nullptr)
        throw std::runtime_error("acceptAssignExpr has no lvalue");
    else if (node[AST_TAG_EXPR] == nullptr)
        throw std::runtime_error("acceptAssignExpr has no expr");       

    accept(node[AST_TAG_LVALUE]);
    accept(node[AST_TAG_EXPR]);
    visitor->visitAssignExpr(node);
}

void TreeHost::acceptPrimary( Object& node) {
     if (node[AST_TAG_CHILD] == nullptr)
        throw std::runtime_error("acceptPrimary has no child");        

    accept(node[AST_TAG_CHILD]);
    visitor->visitPrimary(node);
}

void TreeHost::acceptLvalueId( Object& node) {
    visitor->visitLvalueId(node);
}

void TreeHost::acceptLvalueGlobalId( Object& node) {
    visitor->visitLvalueGlobalId(node);
}

void TreeHost::acceptLvalueLocalId( Object& node) {
    visitor->visitLvalueLocalId(node);
}

void TreeHost::acceptLvalueMember( Object& node) {
    if (node[AST_TAG_MEMBER] == nullptr)
        throw std::runtime_error("acceptLvalueMember has no member");       

    accept(node[AST_TAG_MEMBER]);
    visitor->visitLvalueMember(node);
}

void TreeHost::acceptMemberId( Object& node){
    if (node[AST_TAG_CALLER] == nullptr)
        throw std::runtime_error("acceptMemberId has no caller");        

    accept(node[AST_TAG_CALLER]);
    visitor->visitMemberId(node);
}

void TreeHost::acceptMemberExpr( Object& node){
    if (node[AST_TAG_CALLER] == nullptr)
        throw std::runtime_error("acceptMemberExpr has no caller");
    else if (node[AST_TAG_EXPR] == nullptr)
        throw std::runtime_error("acceptMemberExpr has no expr");       

    accept(node[AST_TAG_CALLER]);
    accept(node[AST_TAG_EXPR]);
    visitor->visitMemberExpr(node);
}

void TreeHost::acceptMultiCall( Object& node){
    if (node[AST_TAG_CALL] == nullptr)
        throw std::runtime_error("acceptMultiCall has no call");        

    accept(node[AST_TAG_CALL]);

    if (node[AST_TAG_ELIST] != nullptr)
        accept(node[AST_TAG_ELIST]);
    
    visitor->visitMultiCall(node);
}

void TreeHost::acceptFdefCall( Object& node){
    if (node[AST_TAG_FUNCDEF] == nullptr)
        throw std::runtime_error("acceptFdefCall has no funcdef");      

    accept(node[AST_TAG_FUNCDEF]);

    if(node[AST_TAG_ELIST] != nullptr)
        accept(node[AST_TAG_ELIST]);
    
    visitor->visitFdefCall(node);
}

void TreeHost::acceptCall( Object& node){
    if (node[AST_TAG_LVALUE] == nullptr)
        throw std::runtime_error("acceptCall has no lvalue");
    else if (node[AST_TAG_CALLSUFFIX] == nullptr)
        throw std::runtime_error("acceptCall has no callsuffix");      

    accept(node[AST_TAG_LVALUE]);
    accept(node[AST_TAG_CALLSUFFIX]);
    visitor->visitCall(node);
}

void TreeHost::acceptNormCallsuffix( Object& node) {
     if (node[AST_TAG_NORMCALL] == nullptr)
        throw std::runtime_error("acceptNormCallsuffix has no normcall");       

    accept(node[AST_TAG_NORMCALL]);
    visitor->visitNormCallSuffix(node);
}

void TreeHost::acceptMethodCallsuffix( Object& node) {
    if (node[AST_TAG_METHODCALL] == nullptr)
        throw std::runtime_error("acceptMethodCallsuffix has no methodcall");       

    accept(node[AST_TAG_METHODCALL]);
    visitor->visitMethodCallSuffix(node);
}

void TreeHost::acceptNormCall( Object& node) {
    if(node[AST_TAG_ELIST] != nullptr)
        accept(node[AST_TAG_ELIST]);
    visitor->visitNormCall(node);
}

void TreeHost::acceptMethodCall( Object& node) {
    if(node[AST_TAG_ELIST] != nullptr)
        accept(node[AST_TAG_ELIST]);
    visitor->visitMethodCall(node);
}

void TreeHost::acceptElist( Object& node) {
    if(node[AST_TAG_ELISTNOTEMPTY] != nullptr)
        accept(node[AST_TAG_ELISTNOTEMPTY]);
    visitor->visitElist(node);
}

void TreeHost::acceptElistNotEmpty( Object& node) {
    if (node[AST_TAG_NUMCHILDREN] == nullptr) 
        throw std::runtime_error("acceptElistNotEmpty has no children");        

    for (int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        accept(node[i]);
    }
    visitor->visitElistNotEmpty(node);
}

void TreeHost::acceptArgument(Object& node) {
    if (node[AST_TAG_EXPR] == nullptr) 
        throw std::runtime_error("acceptArgument has no expr");       

    accept(node[AST_TAG_EXPR]);
    visitor->visitArgument(node);
}

void TreeHost::acceptObjectDef( Object& node) {
    if(node[AST_TAG_OBJECTDINNER] != nullptr)
        accept(node[AST_TAG_OBJECTDINNER]);
    visitor->visitObjectDef(node);
}

void TreeHost::acceptObjElistNotEmpty(Object &node) {
    if (node[AST_TAG_NUMCHILDREN] == nullptr) 
        throw std::runtime_error("acceptObjElistNotEmpty has no children");       

    for (int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        accept(node[i]);
    }
    visitor->visitObjElistNotEmpty(node);
}

void TreeHost::acceptObjectDinnerObjElistNotEmpty( Object& node) {
    if (node[AST_TAG_OBJELISTNOTEMPTY] == nullptr) 
        throw std::runtime_error("acceptObjectDinnerObjElistNotEmpty has no objelistnotempty");         

    accept(node[AST_TAG_OBJELISTNOTEMPTY]);
    visitor->visitObjectDinnerObjElistnotempty(node);
}

void TreeHost::acceptObjectDinnerIndexed( Object& node) {
    if (node[AST_TAG_INDEXED] == nullptr) 
        throw std::runtime_error("acceptObjectDinnerIndexed has no indexed");     

    accept(node[AST_TAG_INDEXED]);
    visitor->visitObjectDinnerIndexed(node);
}

void TreeHost::acceptIndexed( Object& node) {
    if (node[AST_TAG_COMMAINDEXED] == nullptr) 
        throw std::runtime_error("acceptIndexed has no commaindexed");        

    accept(node[AST_TAG_COMMAINDEXED]);
}

void TreeHost::acceptCommaIndexed( Object& node) {
    if (node[AST_TAG_NUMCHILDREN] == nullptr) 
        throw std::runtime_error("acceptCommaIndexed has no children");       

    for (int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        accept(node[i]);
    }
    visitor->visitCommaIndexed(node);
}

void TreeHost::acceptIndexedElem( Object& node) {
    if (node[AST_TAG_OBJECT_KEY] == nullptr) 
        throw std::runtime_error("acceptIndexedElem has no key");
    else if (node[AST_TAG_OBJECT_VALUE] == nullptr) 
        throw std::runtime_error("acceptIndexedElem has no value");        
    
    accept(node[AST_TAG_OBJECT_KEY]); 
    accept(node[AST_TAG_OBJECT_VALUE]);
    visitor->visitIndexedElem(node);
}

void TreeHost::acceptBlock( Object& node) {
    if(node[AST_TAG_STMTS] != nullptr)
        accept(node[AST_TAG_STMTS]);
    visitor->visitBlock(node);
}

void TreeHost::acceptFuncDef( Object& node) {
   if (node[AST_TAG_FUNCPREFIX] == nullptr) 
        throw std::runtime_error("acceptFuncDef has no funcprefix");
    else if (node[AST_TAG_BLOCK] == nullptr) 
        throw std::runtime_error("acceptFuncDef has no block");   

    accept(node[AST_TAG_FUNCPREFIX]);

    if(node[AST_TAG_IDLIST] != nullptr)
        accept(node[AST_TAG_IDLIST]);

    accept(node[AST_TAG_BLOCK]);
    visitor->visitFuncDef(node);
}

void TreeHost::acceptFuncPrefix( Object& node) {
    if(node[AST_TAG_CHILD] != nullptr)
        accept(node[AST_TAG_CHILD]);

    visitor->visitFuncPrefix(node);
}

void TreeHost::acceptFuncName( Object& node) {
    if(node[AST_TAG_CHILD] != nullptr)
        accept(node[AST_TAG_CHILD]);
    
    visitor->visitFuncName(node);
}

void TreeHost::acceptConst( Object& node) {
    if (node[AST_TAG_SUBTYPE_KEY] == nullptr) 
        throw std::runtime_error("acceptConst has no subtype");        

    const Value *v = node[AST_TAG_SUBTYPE_KEY];
    std::string subtype = std::string(v->toString());

    if (subtype == std::string(AST_TAG_CONST_NUMCONST))
        visitor->visitConstNumconst(node);
    else if (subtype == std::string(AST_TAG_CONST_STRCONST))
        visitor->visitConstStringconst(node);
    else if (subtype == std::string(AST_TAG_CONST_NIL))
        visitor->visitConstNil(node);
    else if (subtype == std::string(AST_TAG_CONST_BOOLCONST))
        visitor->visitConstBoolconst(node);
    else
        throw std::runtime_error("acceptConst has wrong subtype");
    
}

void TreeHost::acceptID( Object& node) {
    visitor->visitID(node);
}

void TreeHost::acceptCommaIdList( Object& node) {
    if (node[AST_TAG_NUMCHILDREN] == nullptr) 
        throw std::runtime_error("acceptCommaIdList has no children");        

    for (int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        accept(node[i]);
    }
    visitor->visitCommaIdList(node);
}

void TreeHost::acceptFormal(Object& node) {
    if(node[AST_TAG_EXPR] != nullptr)
        accept(node[AST_TAG_EXPR]);
    visitor->visitFormal(node);
}

void TreeHost::acceptIfPrefix( Object& node) {
    if (node[AST_TAG_EXPR] == nullptr) 
        throw std::runtime_error("acceptIfPrefix has no ifprefix");        

    accept(node[AST_TAG_EXPR]);
    visitor->visitIfPrefix(node);
}

void TreeHost::acceptElsePrefix( Object& node) {
    visitor->visitElsePrefix(node);
}

void TreeHost::acceptIfStmt( Object& node) {
    if (node[AST_TAG_IFPREFIX] == nullptr) 
        throw std::runtime_error("acceptIfStmt has no ifprefix");
    else if (node[AST_TAG_IFSTMT_IFBODY] == nullptr) 
        throw std::runtime_error("acceptIfStmt has no ifstmtifbody");        

    accept(node[AST_TAG_IFPREFIX]);
    accept(node[AST_TAG_IFSTMT_IFBODY]); //install stmt

    if(node[AST_TAG_ELSEPREFIX] != nullptr) {
        accept(node[AST_TAG_ELSEPREFIX]);

        if (node[AST_TAG_IFSTMT_ELSEBODY] == nullptr) 
            throw std::runtime_error("acceptIfStmt has no elsebody");            

        accept(node[AST_TAG_IFSTMT_ELSEBODY]);
        visitor->visitIfStmtElseStmt(node);
    }
    else
        visitor->visitIfStmt(node);
}

void TreeHost::acceptWhileStart( Object& node) {
    visitor->visitWhileStart(node);
}

void TreeHost::acceptWhileCond( Object& node) {
    if (node[AST_TAG_EXPR] == nullptr) 
        throw std::runtime_error("acceptWhileCond has no expr");       

    accept(node[AST_TAG_EXPR]);
    visitor->visitWhileCond(node);
}

void TreeHost::acceptWhileStmt( Object& node) {
    if (node[AST_TAG_WHILESTART] == nullptr) 
        throw std::runtime_error("acceptWhileStmt has no whilestart");
    else if (node[AST_TAG_WHILECOND] == nullptr) 
        throw std::runtime_error("acceptWhileStmt has no whilecond");
    else if (node[AST_TAG_STMT] == nullptr) 
        throw std::runtime_error("acceptWhileStmt has no stmt");
        
    accept(node[AST_TAG_WHILESTART]);
    accept(node[AST_TAG_WHILECOND]);
    accept(node[AST_TAG_STMT]);
    visitor->visitWhileStmt(node);
}

void TreeHost::acceptForPrefix( Object& node) {
    if(node[AST_TAG_ELIST] != nullptr)
        accept(node[AST_TAG_ELIST]);

    if (node[AST_TAG_EXPR] == nullptr) 
        throw std::runtime_error("acceptForPrefix has no expr");        

    accept(node[AST_TAG_EXPR]);
    visitor->visitForPrefix(node);
}

void TreeHost::acceptForStmt( Object& node) {
   if (node[AST_TAG_FORPREFIX] == nullptr) 
        throw std::runtime_error("acceptForStmt has no forprefix");       

    accept(node[AST_TAG_FORPREFIX]);

    if(node[AST_TAG_ELIST] != nullptr)
        accept(node[AST_TAG_ELIST]);

    if (node[AST_TAG_STMT] == nullptr) 
        throw std::runtime_error("acceptForStmt has no stmt");       

    accept(node[AST_TAG_STMT]);
    visitor->visitForStmt(node);
}

void TreeHost::acceptReturnStmt( Object& node) {
    if (node[AST_TAG_EXPR] != nullptr) {
        accept(node[AST_TAG_EXPR]);
        visitor->visitReturnStmtExpr(node);
    }
    else
        visitor->visitReturnStmt(node);
}

void TreeHost::acceptBreak( Object &node) {
    visitor->visitBreak(node);
}

void TreeHost::acceptContinue( Object& node) {
    visitor->visitContinue(node);
}

void TreeHost::acceptQuasiQuotes(Object& node) {
    if (node[AST_TAG_CHILD] == nullptr) 
        throw std::runtime_error("acceptQuasiQuotes has no child");       

    accept(node[AST_TAG_CHILD]);

    visitor->visitQuasiQuotes(node);
}

void TreeHost::acceptQuotedRules(Object& node) {
    if (node[AST_TAG_CHILD] == nullptr) 
        throw std::runtime_error("acceptQuotedRules has no child");      

    accept(node[AST_TAG_CHILD]);

    visitor->visitQuotedRules(node);
}

void TreeHost::acceptEscapeId(Object& node) {   
    visitor->visitEscapeId(node);
}

void TreeHost::acceptEscapeExpr(Object& node) {
    if (node[AST_TAG_EXPR] == nullptr) 
        throw std::runtime_error("acceptEscapeExpr has no expr");         

    accept(node[AST_TAG_EXPR]);
    
    visitor->visitEscapeExpr(node);
}

void TreeHost::acceptInline( Object& node) {
    if (node[AST_TAG_CHILD] == nullptr) 
        throw std::runtime_error("acceptInline has no child");         

    accept(node[AST_TAG_CHILD]);
    visitor->visitInline(node);
}

void TreeHost::acceptUnparsed( Object& node) {
    if (node[AST_TAG_CHILD] == nullptr) 
        throw std::runtime_error("acceptUnparsed has no child");    

    accept(node[AST_TAG_CHILD]);
    visitor->visitUnparsed(node);
}

void TreeHost::acceptCompiledString( Object& node) {
    if (node[AST_TAG_CHILD] == nullptr) 
        throw std::runtime_error("acceptCompiledString has no child");
    
    accept(node[AST_TAG_CHILD]);

    visitor->visitCompiledString(node);
}

void TreeHost::acceptValueStorage(Object& node) {
    visitor->visitValueStorage(node);
}

void TreeHost::installAllAcceptors() {

    //installations of acceptors by geomlyd
    installAcceptor(AST_TAG_PROGRAM, [this]( Object& node)
        {acceptProgram(node);});
    installAcceptor(AST_TAG_STMTS, [this]( Object& node)
        {acceptStmts(node);});
    installAcceptor(AST_TAG_STMT, [this]( Object& node)
        {acceptStmt(node);});  

    installAcceptor(AST_TAG_EXPR, [this]( Object& node)
        {acceptExpr(node);});              
    installAcceptor(AST_TAG_ARITHEXPR, [this]( Object& node)
        {acceptArithExpr(node);});
    installAcceptor(AST_TAG_RELEXPR, [this]( Object& node)
        {acceptRelExpr(node);});    
    installAcceptor(AST_TAG_BOOLEXPR, [this]( Object& node)
        {acceptBoolExpr(node);});    

    installAcceptor(AST_TAG_TERM, [this]( Object& node)
        {acceptTerm(node);});  
    installAcceptor(AST_TAG_TERM_PARENS_EXPR, [this]( Object& node)
        {acceptTermParensExpr(node);});    
    installAcceptor(AST_TAG_TERM_MINUS_EXPR, [this]( Object& node)
        {acceptTermMinusExpr(node);});      
    installAcceptor(AST_TAG_TERM_NOT_EXPR, [this]( Object& node)
        {acceptTermNotExpr(node);});    
    installAcceptor(AST_TAG_TERM_PLUS_PLUS_LVALUE, [this]( Object& node)
        {acceptTermPlusPlusLvalue(node);}); 
    installAcceptor(AST_TAG_TERM_MINUS_MINUS_LVALUE, [this]( Object& node)
        {acceptTermMinusMinusLvalue(node);});         
    installAcceptor(AST_TAG_TERM_LVALUE_PLUS_PLUS, [this]( Object& node)
        {acceptTermLvaluePlusPlus(node);});  
    installAcceptor(AST_TAG_TERM_LVALUE_MINUS_MINUS, [this]( Object& node)
        {acceptTermLvalueMinusMinus(node);});
    
    //installations of acceptors by alivas
    installAcceptor(AST_TAG_ASSIGNEXPR, [this]( Object& node) {acceptAssignExpr(node);});
    installAcceptor(AST_TAG_PRIMARY, [this]( Object& node) {acceptPrimary(node);});
    installAcceptor(AST_TAG_LVALUE_ID, [this]( Object& node) {acceptLvalueId(node);});
    installAcceptor(AST_TAG_LVALUE_GLOBAL_ID, [this]( Object& node) {acceptLvalueGlobalId(node);});
    installAcceptor(AST_TAG_LVALUE_LOCAL_ID, [this]( Object& node) {acceptLvalueLocalId(node);});
    installAcceptor(AST_TAG_LVALUE_MEMBER, [this]( Object& node) {acceptLvalueMember(node);});
    installAcceptor(AST_TAG_MEMBER_ID, [this]( Object& node) {acceptMemberId(node);});
    installAcceptor(AST_TAG_MEMBER_EXPR, [this]( Object& node) {acceptMemberExpr(node);});
    installAcceptor(AST_TAG_MULTICALL, [this]( Object& node) {acceptMultiCall(node);});
    installAcceptor(AST_TAG_FDEFCALL, [this]( Object& node) {acceptFdefCall(node);});
    installAcceptor(AST_TAG_CALL, [this]( Object& node) {acceptCall(node);});
    installAcceptor(AST_TAG_NORMCALLSUFFIX, [this]( Object& node) {acceptNormCallsuffix(node);});
    installAcceptor(AST_TAG_METHODCALLSUFFIX, [this]( Object& node) {acceptMethodCallsuffix(node);});
    installAcceptor(AST_TAG_NORMCALL, [this]( Object& node) {acceptNormCall(node);});
    installAcceptor(AST_TAG_METHODCALL, [this]( Object& node) {acceptMethodCall(node);});
    installAcceptor(AST_TAG_ELIST, [this]( Object& node) {acceptElist(node);});
    installAcceptor(AST_TAG_ELISTNOTEMPTY, [this]( Object& node) {acceptElistNotEmpty(node);});
    installAcceptor(AST_TAG_ARGUMENT, [this]( Object& node) {acceptArgument(node);});    
    installAcceptor(AST_TAG_OBJECTDEF, [this]( Object& node) {acceptObjectDef(node);});
    installAcceptor(AST_TAG_OBJELISTNOTEMPTY, [this]( Object& node) {acceptObjElistNotEmpty(node);});
    installAcceptor(AST_TAG_CONT_LIST, [this]( Object& node) {acceptObjectDinnerObjElistNotEmpty(node);});
    installAcceptor(AST_TAG_CONT_INDEXED, [this]( Object& node) {acceptObjectDinnerIndexed(node);});
    //installations of acceptors by manosgior   
    installAcceptor(AST_TAG_COMMAINDEXED, [this]( Object& node) {acceptCommaIndexed(node);});
    installAcceptor(AST_TAG_INDEXEDELEM, [this]( Object& node) {acceptIndexedElem(node);});
    installAcceptor(AST_TAG_OBJECT_KEY, [this]( Object& node) {acceptExpr(node);});
    installAcceptor(AST_TAG_OBJECT_VALUE, [this]( Object& node) {acceptExpr(node);});
    installAcceptor(AST_TAG_BLOCK, [this]( Object& node) {acceptBlock(node);});
    installAcceptor(AST_TAG_FUNCDEF, [this]( Object& node) {acceptFuncDef(node);});
    installAcceptor(AST_TAG_FUNCPREFIX, [this]( Object& node) {acceptFuncPrefix(node);});
    installAcceptor(AST_TAG_FUNCNAME_ID, [this]( Object& node) {acceptFuncName(node);});   
    installAcceptor(AST_TAG_CONST, [this]( Object& node) {acceptConst(node);});
    installAcceptor(AST_TAG_CONST_NUMCONST, [this]( Object& node) {acceptConst(node);});
    installAcceptor(AST_TAG_CONST_STRCONST, [this]( Object& node) {acceptConst(node);});
    installAcceptor(AST_TAG_CONST_NIL, [this]( Object& node) {acceptConst(node);});
    installAcceptor(AST_TAG_CONST_BOOLCONST, [this]( Object& node) {acceptConst(node);});    
    installAcceptor(AST_TAG_ID, [this]( Object& node) {acceptID(node);});
    installAcceptor(AST_TAG_COMMAIDLIST, [this]( Object& node) {acceptCommaIdList(node);});
    installAcceptor(AST_TAG_FORMAL, [this]( Object& node) {acceptFormal(node);});
    installAcceptor(AST_TAG_IFPREFIX, [this]( Object& node) {acceptIfPrefix(node);});
    installAcceptor(AST_TAG_ELSEPREFIX, [this]( Object& node) {acceptElsePrefix(node);});
    installAcceptor(AST_TAG_IFSTMT, [this]( Object& node) {acceptIfStmt(node);});
    installAcceptor(AST_TAG_IFSTMT_IFBODY, [this]( Object& node) {acceptStmt(node);});
    installAcceptor(AST_TAG_IFSTMT_ELSEBODY, [this]( Object& node) {acceptStmt(node);});
    installAcceptor(AST_TAG_WHILESTART, [this]( Object& node) {acceptWhileStart(node);});
    installAcceptor(AST_TAG_WHILECOND, [this]( Object& node) {acceptWhileCond(node);});   
    installAcceptor(AST_TAG_WHILESTMT, [this]( Object& node) {acceptWhileStmt(node);});   
    installAcceptor(AST_TAG_FORPREFIX, [this]( Object& node) {acceptForPrefix(node);});
    installAcceptor(AST_TAG_FORSTMT, [this]( Object& node) {acceptForStmt(node);});
    installAcceptor(AST_TAG_RETURNSTMT, [this]( Object& node) {acceptReturnStmt(node);});
    installAcceptor(AST_TAG_BREAKSTMT, [this]( Object& node) {acceptBreak(node);});
    installAcceptor(AST_TAG_CONTINUESTMT, [this]( Object& node) {acceptContinue(node);});

    installAcceptor(AST_TAG_QUASIQUOTES, [this]( Object& node) {acceptQuasiQuotes(node);});
    installAcceptor(AST_TAG_QUOTEDRULES, [this]( Object& node) {acceptQuotedRules(node);});
    installAcceptor(AST_TAG_ESCAPE_ID, [this]( Object& node) {acceptEscapeId(node);});
    installAcceptor(AST_TAG_ESCAPE_EXPR, [this]( Object& node) {acceptEscapeExpr(node);});
    installAcceptor(AST_TAG_INLINE, [this]( Object& node) {acceptInline(node);});
    installAcceptor(AST_TAG_UNPARSED, [this]( Object& node) {acceptUnparsed(node);});
    installAcceptor(AST_TAG_COMPILEDSTRING, [this]( Object& node) {acceptCompiledString(node);});
    installAcceptor(AST_TAG_VALUESTORAGE, [this]( Object& node) {acceptValueStorage(node);});
}

    
void TreeHost::accept(TreeVisitor* _visitor,  Object& node) {
    visitor = _visitor;
    Value tmp = Value(&node);
    node.incRefCounter();
    accept(&tmp);
    tmp = Value(false); //hacky way of preventing node deletion when tmp goes out of scope
    node.decRefCounter();
}