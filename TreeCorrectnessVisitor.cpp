#include "TreeCorrectnessVisitor.h"
#include <regex>

void TreeCorrectnessVisitor::checkNodeCorrectness(Object &node, std::vector<std::string> indices, 
    std::vector<std::set<std::string>> expectedTypes, std::vector<bool> isOptional){
        assert(indices.size() == expectedTypes.size() && expectedTypes.size() == isOptional.size());
        if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
            throw std::runtime_error("invalid line number in AST node");
        for(unsigned i = 0; i < expectedTypes.size(); i++){
            if (isOptional[i] && node[indices[i]] == nullptr)
                continue;
            auto actualType = (*node[indices[i]]->toObjectNoConst())[AST_TAG_TYPE_KEY]->toString();
            if(!isOptional[i] && expectedTypes[i].find(actualType) == expectedTypes[i].end())
                throw std::runtime_error("AST structure not congruent with a++ syntax");
        }
}

void TreeCorrectnessVisitor::visitProgram( Object& node){
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_STMTS}}, {true});
}

void TreeCorrectnessVisitor::visitStmts( Object& node){
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");    
    for(int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++){
        if( (*node[(double)i]->toObjectNoConst())[AST_TAG_TYPE_KEY]->toString() != std::string(AST_TAG_STMT) )
            throw std::runtime_error("AST structure not congruent with a++ syntax");
    }
}

void TreeCorrectnessVisitor::visitStmt( Object& node){
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_EXPR, AST_TAG_IFSTMT, AST_TAG_WHILESTMT,
        AST_TAG_FORSTMT, AST_TAG_RETURNSTMT, AST_TAG_BREAKSTMT, AST_TAG_CONTINUESTMT, AST_TAG_BLOCK,
        AST_TAG_FUNCDEF}}, {true});
}

void TreeCorrectnessVisitor::visitBreak( Object& node){}

void TreeCorrectnessVisitor::visitContinue( Object& node){}

void TreeCorrectnessVisitor::visitExpr( Object& node){
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_EXPR, AST_TAG_TERM}}, {false});
}

void TreeCorrectnessVisitor::visitArithExpr( Object& node){
    std::set<std::string> legalOps = {"+", "-", "*", "/", "%"};
    if(node[AST_TAG_ARITHOP_TYPE] == nullptr || !node[AST_TAG_ARITHOP_TYPE]->isString() ||
        legalOps.find(node[AST_TAG_ARITHOP_TYPE]->toString()) == legalOps.end())
        throw std::runtime_error("unrecognized arithmetic operator");
    checkNodeCorrectness(node, {AST_TAG_LEFTEXPR, AST_TAG_RIGHTEXPR}, {{AST_TAG_EXPR}, {AST_TAG_EXPR}}, {false, false});
}

void TreeCorrectnessVisitor::visitRelExpr( Object& node){
    std::set<std::string> legalOps = {">", ">=", "<", "<=", "==", "!="};
    if(node[AST_TAG_RELOP_TYPE] == nullptr || !node[AST_TAG_RELOP_TYPE]->isString() ||
        legalOps.find(node[AST_TAG_RELOP_TYPE]->toString()) == legalOps.end())
        throw std::runtime_error("unrecognized relational operator");    
    checkNodeCorrectness(node, {AST_TAG_LEFTEXPR, AST_TAG_RIGHTEXPR}, {{AST_TAG_EXPR}, {AST_TAG_EXPR}}, {false, false});
}

void TreeCorrectnessVisitor::visitBoolExpr( Object& node){
    std::set<std::string> legalOps = {"and", "or"};
    if(node[AST_TAG_BOOLOP_TYPE] == nullptr || !node[AST_TAG_BOOLOP_TYPE]->isString() ||
        legalOps.find(node[AST_TAG_BOOLOP_TYPE]->toString()) == legalOps.end())
        throw std::runtime_error("unrecognized boolean operator");        
    checkNodeCorrectness(node, {AST_TAG_LEFTEXPR, AST_TAG_RIGHTEXPR}, {{AST_TAG_EXPR}, {AST_TAG_EXPR}}, {false, false});
}

void TreeCorrectnessVisitor::visitTerm( Object& node){
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_PRIMARY}}, {false});
}

void TreeCorrectnessVisitor::visitTermParensExpr( Object& node){
    checkNodeCorrectness(node, {AST_TAG_EXPR}, {{AST_TAG_EXPR}}, {false});
}

void TreeCorrectnessVisitor::visitTermMinusExpr( Object& node){
    checkNodeCorrectness(node, {AST_TAG_EXPR}, {{AST_TAG_EXPR}}, {false});
}

void TreeCorrectnessVisitor::visitTermNotExpr( Object& node){
    checkNodeCorrectness(node, {AST_TAG_EXPR}, {{AST_TAG_EXPR}}, {false});   
}

void TreeCorrectnessVisitor::visitTermPlusPlusLvalue( Object& node){
    checkNodeCorrectness(node, {AST_TAG_LVALUE}, {{AST_TAG_LVALUE}}, {false});   
}

void TreeCorrectnessVisitor::visitTermMinusMinusLvalue( Object& node){
    checkNodeCorrectness(node, {AST_TAG_LVALUE}, {{AST_TAG_LVALUE}}, {false});   
}

void TreeCorrectnessVisitor::visitTermLvaluePlusPlus( Object& node){
    checkNodeCorrectness(node, {AST_TAG_LVALUE}, {{AST_TAG_LVALUE}}, {false});   
}

void TreeCorrectnessVisitor::visitTermLvalueMinusMinus( Object& node){
    checkNodeCorrectness(node, {AST_TAG_LVALUE}, {{AST_TAG_LVALUE}}, {false});   
} 


void TreeCorrectnessVisitor::visitCommaIndexed( Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    for (int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        if ((*node[(double) i]->toObjectNoConst())[AST_TAG_TYPE_KEY]->toString() != std::string(AST_TAG_INDEXEDELEM))
            throw std::runtime_error("function's arguments are not of formal type");
    }
}

void TreeCorrectnessVisitor::visitIndexedElem( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_OBJECT_KEY, AST_TAG_OBJECT_VALUE}, {{AST_TAG_EXPR}, {AST_TAG_EXPR}}, {false, false});
}

void TreeCorrectnessVisitor::visitBlock( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_STMTS}, {{AST_TAG_STMTS}}, {true});
}

void TreeCorrectnessVisitor::visitFuncDef( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_FUNCPREFIX, AST_TAG_IDLIST, AST_TAG_BLOCK}, {{AST_TAG_FUNCPREFIX}, {AST_TAG_COMMAIDLIST}, {AST_TAG_BLOCK}}, {false, true, false});
    
    if (node[AST_TAG_IDLIST] != nullptr) {
        Object *idlist = node[AST_TAG_IDLIST]->toObjectNoConst();
        std::map<std::string, bool> idMap = std::map<std::string, bool>();
        
        auto numFormals = (*idlist)[AST_TAG_NUMCHILDREN]->toNumber();
        bool idflag = false;
        for (unsigned int i = 0; i < numFormals; i++) {
            auto currFormalName = (*((*idlist)[i]->toObjectNoConst()))[AST_TAG_ID]->toString();
            if (idMap.find(currFormalName) == idMap.end())
                idMap[currFormalName] = true;
            else 
                throw std::runtime_error("A++ Syntax Error: same argument many times\n");               
            auto formalExpr = (*((*idlist)[i]->toObjectNoConst()))[AST_TAG_EXPR];
            if (idflag && formalExpr == nullptr) 
                throw std::runtime_error("A++ Syntax Error: required arguments cannot be after optional arguments\n");                
            
            if (!idflag && formalExpr != nullptr) idflag = true;
        }
    }
}

void TreeCorrectnessVisitor::visitFuncPrefix( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_FUNCNAME}}, {true});
}

void TreeCorrectnessVisitor::visitFuncName(Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    Value *v = node[AST_TAG_ID];

    if (v == nullptr || !v->isString())
        throw std::runtime_error("function identifier is invalid");
    
    std::string name = v->toString();

    std::regex id("[a-zA-Z][a-zA-Z_0-9]*");         
        
    if(!(std::regex_match(name, id))) {
        throw std::runtime_error("function identifier is invalid");
    }
}

void TreeCorrectnessVisitor::visitConst( Object& node) {
    throw std::runtime_error("visitConst should not be called");
}

void TreeCorrectnessVisitor::visitConstNumconst( Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    Value *v = node[AST_TAG_VALUE];

    if (v == nullptr || !v->isNumber())
        throw std::runtime_error("numconst was not a number");
}

void TreeCorrectnessVisitor::visitConstStringconst( Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    Value *v = node[AST_TAG_VALUE];

    if (v == nullptr || !v->isString())
        throw std::runtime_error("stringconst was not a string");
}

void TreeCorrectnessVisitor::visitConstBoolconst( Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    Value *v = node[AST_TAG_VALUE];

    if (v == nullptr || !v->isBoolean())
        throw std::runtime_error("boolconst was not a boolean");
}

void TreeCorrectnessVisitor::visitConstNil( Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    Value *v = node[AST_TAG_VALUE];

    if (v == nullptr || !v->isNil())
        throw std::runtime_error("nilconst was not nil");
}    

void TreeCorrectnessVisitor::visitID( Object& node) {
    throw std::runtime_error("visitID should not be called");
}

void TreeCorrectnessVisitor::visitCommaIdList( Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    for (int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        if ((*node[(double) i]->toObjectNoConst())[AST_TAG_TYPE_KEY]->toString() != std::string(AST_TAG_FORMAL))
            throw std::runtime_error("function's arguments are not of formal type");
    }
}

void TreeCorrectnessVisitor::visitFormal( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_EXPR}, {{AST_TAG_EXPR}}, {true});

    Value *v = node[AST_TAG_ID];

    if (v == nullptr || !v->isString())
        throw std::runtime_error("formal identifier is invalid");
    
    std::string name = v->toString();

    std::regex id("[a-zA-Z][a-zA-Z_0-9]*");         
        
    if(!(std::regex_match(name, id))) {
        throw std::runtime_error("formal identifier is invalid");
    }
}

void TreeCorrectnessVisitor::visitIfPrefix( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_EXPR}, {{AST_TAG_EXPR}}, {false});
}

void TreeCorrectnessVisitor::visitElsePrefix( Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    return;
}

void TreeCorrectnessVisitor::visitIfStmt( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_IFPREFIX, AST_TAG_IFSTMT_IFBODY}, {{AST_TAG_IFPREFIX}, {AST_TAG_STMT}}, {false, false});
}

void TreeCorrectnessVisitor::visitIfStmtElseStmt( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_IFPREFIX, AST_TAG_ELSEPREFIX, AST_TAG_IFSTMT_IFBODY, AST_TAG_IFSTMT_ELSEBODY}, {{AST_TAG_IFPREFIX}, {AST_TAG_ELSEPREFIX}, {AST_TAG_STMT}, {AST_TAG_STMT}}, {false, false, false, false});
}

void TreeCorrectnessVisitor::visitWhileStart( Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    return;
}

void TreeCorrectnessVisitor::visitWhileCond( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_EXPR}, {{AST_TAG_EXPR}}, {false});
}

void TreeCorrectnessVisitor::visitWhileStmt( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_WHILESTART, AST_TAG_WHILECOND,AST_TAG_STMT }, {{AST_TAG_WHILESTART}, {AST_TAG_WHILECOND}, {AST_TAG_STMT}}, {false, false, false});
}

void TreeCorrectnessVisitor::visitForPrefix( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_ELIST, AST_TAG_EXPR}, {{AST_TAG_ELISTNOTEMPTY, AST_TAG_ELIST}, {AST_TAG_EXPR}}, {true, false});
}

void TreeCorrectnessVisitor::visitForStmt( Object&node) {
    checkNodeCorrectness(node, {AST_TAG_FORPREFIX, AST_TAG_ELIST, AST_TAG_STMT}, {{AST_TAG_FORPREFIX}, {AST_TAG_ELISTNOTEMPTY, AST_TAG_ELIST}, {AST_TAG_STMT}}, {false, true, false});
}

void TreeCorrectnessVisitor::visitReturnStmt( Object& node) {
    if(node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");

    return;
}

void TreeCorrectnessVisitor::visitReturnStmtExpr( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_EXPR}, {{AST_TAG_EXPR}}, {false});
}

void TreeCorrectnessVisitor::visitInline( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_EXPR}}, {false});
}

void TreeCorrectnessVisitor::visitUnparsed(Object& node) {
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_EXPR}}, {false});
}

void TreeCorrectnessVisitor::visitCompiledString(Object& node) {
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_EXPR}}, {false});
}

void TreeCorrectnessVisitor::visitEscapeId(Object& node) {
    Value *v = node[AST_TAG_ID];

    if (v == nullptr || !v->isString())
        throw std::runtime_error("escaped identifier is invalid");
    
    std::string name = v->toString();

    std::regex id("[a-zA-Z][a-zA-Z_0-9]*");         
        
    if(!(std::regex_match(name, id))) {
        throw std::runtime_error("escaped identifier is invalid");
    }
}

void TreeCorrectnessVisitor::visitEscapeExpr(Object& node) {
    checkNodeCorrectness(node, {AST_TAG_EXPR}, {{AST_TAG_EXPR}}, {false});
}

void TreeCorrectnessVisitor::visitValueStorage(Object& node) {
    if (node[AST_TAG_VALUE] == nullptr)
        throw std::runtime_error("valuestorage has no value");
}

void TreeCorrectnessVisitor::visitAssignExpr( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_LVALUE, AST_TAG_EXPR}, 
    {{AST_TAG_LVALUE}, {AST_TAG_EXPR}},
    {false, false});
}
void TreeCorrectnessVisitor::visitPrimary( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_CHILD},
    {{AST_TAG_QUASIQUOTES, AST_TAG_ESCAPE, AST_TAG_INLINE, AST_TAG_UNPARSED, AST_TAG_COMPILEDSTRING, AST_TAG_LVALUE, AST_TAG_CALL, AST_TAG_OBJECTDEF, AST_TAG_FUNCDEF, AST_TAG_CONST}},
    {false});
}
void TreeCorrectnessVisitor::visitLvalueId( Object& node) {
    if (node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");
    if (!node[AST_TAG_ID] || !node[AST_TAG_ID]->isString()) 
        throw std::runtime_error("AST structure not congruent with a++ syntax");
    
}
void TreeCorrectnessVisitor::visitLvalueGlobalId( Object& node) {
    if (node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");
    if (!node[AST_TAG_GLOBALID] || !node[AST_TAG_GLOBALID]->isString()) 
        throw std::runtime_error("AST structure not congruent with a++ syntax");
}
void TreeCorrectnessVisitor::visitLvalueLocalId( Object& node) {
    if (node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");
    if (!node[AST_TAG_LOCALID] || !node[AST_TAG_LOCALID]->isString()) 
        throw std::runtime_error("AST structure not congruent with a++ syntax");
}
void TreeCorrectnessVisitor::visitLvalueMember( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_MEMBER}, {{AST_TAG_MEMBER}}, {false});
}
void TreeCorrectnessVisitor::visitMemberId( Object& node) {
    if (node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invalid line number in AST node");
    if (!node[AST_TAG_ID] || !node[AST_TAG_ID]->isString()) 
        throw std::runtime_error("AST structure not congruent with a++ syntax");

    checkNodeCorrectness(node, {AST_TAG_CALLER}, {{AST_TAG_LVALUE, AST_TAG_CALL}}, {false});
}
void TreeCorrectnessVisitor::visitMemberExpr( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_CALLER, AST_TAG_EXPR}, {{AST_TAG_LVALUE, AST_TAG_CALL}, {AST_TAG_EXPR}}, {false, false});
}
void TreeCorrectnessVisitor::visitCall( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_LVALUE, AST_TAG_CALLSUFFIX}, {{AST_TAG_LVALUE}, {AST_TAG_CALLSUFFIX}}, {false, false});
}
void TreeCorrectnessVisitor::visitMultiCall( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_CALL, AST_TAG_ELIST}, {{AST_TAG_CALL}, {AST_TAG_ELIST}}, {false, true});
}
void TreeCorrectnessVisitor::visitFdefCall( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_FUNCDEF, AST_TAG_ELIST}, {{AST_TAG_FUNCDEF}, {AST_TAG_ELIST}}, {false, true});
}
void TreeCorrectnessVisitor::visitNormCallSuffix( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_NORMCALL}, {{AST_TAG_NORMCALL}}, {false});
}
void TreeCorrectnessVisitor::visitMethodCallSuffix( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_METHODCALL}, {{AST_TAG_METHODCALL}}, {false});
}
void TreeCorrectnessVisitor::visitNormCall( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_ELIST}, {{AST_TAG_ELIST}}, {true});
}
void TreeCorrectnessVisitor::visitMethodCall( Object& node) {
    if (node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invlud line number in AST node");
    if (!node[AST_TAG_ID] || !node[AST_TAG_ID]->isString()) 
        throw std::runtime_error("AST structure not congruent with a++ syntax");
    checkNodeCorrectness(node, {AST_TAG_ELIST}, {{AST_TAG_ELIST}}, {false});
}
void TreeCorrectnessVisitor::visitElist( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_ELISTNOTEMPTY}, {{AST_TAG_ELISTNOTEMPTY}}, {true});
}
void TreeCorrectnessVisitor::visitElistNotEmpty( Object& node) {
    if (node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invlud line number in AST node");
    bool idflag = false;
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        if ((*node[(double)i]->toObjectNoConst())[AST_TAG_TYPE_KEY]->toString() != std::string(AST_TAG_ARGUMENT))
            throw std::runtime_error("AST structure not congruent with a++ syntax");
        auto argName = (*(*(node[i])).toObjectNoConst())[AST_TAG_ID];
        if (idflag && argName == nullptr) {
            throw std::runtime_error("A++ Syntax Error: positional arguments after keyword arguments are not allowed\n");
        }
        if (!idflag && argName != nullptr) idflag = true;
    }
}
void TreeCorrectnessVisitor::visitArgument( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_EXPR}, {{AST_TAG_EXPR}}, {false});
    if (node[AST_TAG_ID] != nullptr && !node[AST_TAG_ID]->isString()) 
        throw std::runtime_error("AST structure not congruent with a++ syntax");
}
void TreeCorrectnessVisitor::visitObjectDef( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_OBJECTDINNER}, {{AST_TAG_OBJECTDINNER}}, {true});
}
void TreeCorrectnessVisitor::visitObjElistNotEmpty( Object& node) {
    if (node[AST_TAG_LINE_KEY] == nullptr || !node[AST_TAG_LINE_KEY]->isNumber())
        throw std::runtime_error("invlud line number in AST node");
    for (int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        if ((*node[(double)i]->toObjectNoConst())[AST_TAG_TYPE_KEY]->toString() != std::string(AST_TAG_EXPR))
            throw std::runtime_error("AST structure not congruent with a++ syntax");

    }
}
void TreeCorrectnessVisitor::visitObjectDinnerObjElistnotempty( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_OBJELISTNOTEMPTY}, {{AST_TAG_OBJELISTNOTEMPTY}}, {false});
}
void TreeCorrectnessVisitor::visitObjectDinnerIndexed( Object& node) {
    checkNodeCorrectness(node, {AST_TAG_INDEXED}, {{AST_TAG_INDEXED, AST_TAG_COMMAINDEXED}}, {false});
}    

void TreeCorrectnessVisitor::visitQuasiQuotes(Object& node) {
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_QUOTEDRULES}}, {false});
}
void TreeCorrectnessVisitor::visitQuotedRules(Object& node) {
    checkNodeCorrectness(node, {AST_TAG_CHILD}, {{AST_TAG_STMTS, AST_TAG_OBJELISTNOTEMPTY}}, {false});
}

TreeCorrectnessVisitor::~TreeCorrectnessVisitor() {}

TreeVisitor* TreeCorrectnessVisitor::Clone(void) const {
    return new TreeCorrectnessVisitor();
}
