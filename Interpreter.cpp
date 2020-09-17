#include "Interpreter.h"
#include "TreeTags.h"
#include "error_handler.h"
#include <stdexcept>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
#include <string.h>
#include <regex>
#include <algorithm> 
#include <iostream>
#include <sstream>
#include "ASTCreator.h"
#include "CopyTreeVisitor.h"
#include "TreeHost.h"
#include "SetParentTreeVisitor.h"
#include "EvalEscapesTreeVisitor.h"
#include "ControlFlowVisitor.h"
#include "TreeCorrectnessVisitor.h"

struct BreakException {};
struct ContinueException {};

struct ReturnException{ 
    public:
    Value v = (Value::Type::UndefType);   
    ReturnException(const Value _v) {
        v = _v;
    }
};

Interpreter::Interpreter(EvalDispatcher *d) : retVal(Value::Type::UndefType), objField(Value::Type::UndefType) {
    noScope = false;
    dispatcher = d;   
    install();
    installBinaryOpDispatcher();
    validDollarFields = {"$previous", "$outer", "$local", "$closure", "$local"};
    validDollarIdents = {"$lambda", "$env"};
    currentFunction = nullptr;
}

Interpreter::~Interpreter() {
    valRegister = nullptr;
}

const Value Interpreter::interpret(Object& node) {
    return dispatcher->eval(node);
}

const Value* Interpreter::getVarByName(std::string id){
    return lookupId(id);
}

const Value* Interpreter::getGlobalVarByName(std::string id){
    return lookupGlobalId(id);
}

const Value* Interpreter::getLocalVarByName(std::string id){
    return lookupIdCurrEnvOnly(id);
}   

const Object* Interpreter::getTopEnvinroment(){
    return envs.top().toObject();
}

const Object* Interpreter::getGlobalEnvinroment(){
    return globalScope;
}

void Interpreter::pushScopeSpace(Object* scope) {
    envs.push(Value(scope));
}

void Interpreter::pushNested() {
    Object* tmp = new Object();
    auto topEnv = envs.getTopAndPop();
    tmp->set(std::string("$outer"), topEnv);
    envs.push(Value(tmp));
}

void Interpreter::pushSlice() {
    Object *tmp = new Object();
    tmp->set(std::string("$previous"), envs.getTopAndPop());    
    envs.push(Value(tmp));
    if(envs.size() == 1)
        globalScope = tmp;
}

void Interpreter::popScopeSpace() {
    envs.getTopAndPop();
}

Value *Interpreter::lookupId(std::string id) {
    assert(!envs.isEmpty());
    Object *currChain = envs.top().toObjectNoConst();
    while(true){
        Value *possibleId = (*currChain)[id];
        if(possibleId != nullptr)
            return possibleId;
        if ((*currChain)["$local"] != nullptr) {
            auto localenv = (*currChain)["$local"]->toObjectNoConst();
            possibleId = (*localenv)[id];
            if (possibleId != nullptr) {
                return possibleId;
            }
        }
        if((*currChain)["$previous"] != nullptr){
            assert((*currChain)["$outer"] == nullptr);
            currChain = (*currChain)["$previous"]->toObjectNoConst();
        }
        else if((*currChain)["$outer"] != nullptr)
            currChain = (*currChain)["$outer"]->toObjectNoConst();
        else
            return lookupGlobalId(id);
    }
}

Value *Interpreter::declareId(std::string id){
    assert(!envs.isEmpty());
    Object *currChain = envs.top().toObjectNoConst();
    currChain->set(id, Value(Value::Type::UndefType)); 
    return (*currChain)[id];
}

Value *Interpreter::lookupGlobalId(std::string id){
    Object *currChain = globalScope;
    while(true){
        Value *possibleId = (*currChain)[id];
        if(possibleId != nullptr)
            return possibleId;
        if((*currChain)["$previous"] != nullptr){
            assert((*currChain)["$outer"] == nullptr);
            currChain = (*currChain)["$previous"]->toObjectNoConst();
        }  
        else
            return nullptr;
    }       
}

Value *Interpreter::lookupIdCurrEnvOnly(std::string id){
    assert(!envs.isEmpty());
    Object *currChain = envs.top().toObjectNoConst(); 
    while(true){
        Value *possibleId = (*currChain)[id];
        if(possibleId != nullptr)
            return possibleId;
        if ((*currChain)["$local"] != nullptr) {
            auto localenv = (*currChain)["$local"]->toObjectNoConst();
            possibleId = (*localenv)[id];
            if (possibleId != nullptr) {
                return possibleId;
            }
        }
        if((*currChain)["$previous"] != nullptr){
            assert((*currChain)["$outer"] == nullptr);
            currChain = (*currChain)["$previous"]->toObjectNoConst();
        }  
        else
            return nullptr;    
    }         
}

const Value* Interpreter::getArgument(Object& env, unsigned argNo, const std::string& optArgName) {
    auto* arg = env[optArgName];
    if (!arg) arg = env[argNo];
    return arg;
}

void Interpreter::forceClosureClear(Object& env){
    env.apply([this](const Value& key, Value *val){
        if(val->isProgramFunction()) {
            val->clear();
        }
        else if(val->isObject() && val->toObject()->getRefCounter() == 1){
            auto tmp = (key.isString())?(std::string(key.toString())):(std::string(""));
            if(!key.isString() || validDollarFields.find(tmp) == validDollarFields.end() || tmp == "$local")
                forceClosureClear(*val->toObjectNoConst());
        }
    });
}

const Value Interpreter::evalProgram(Object& node){
    valRegister = nullptr;
    currentFunction = nullptr;
    currentFuncNumArgs = -1;
    currFuncArgsEnv = nullptr;
    objField = Value(Value::Type::UndefType);
    globalScope = new Object();
    pushScopeSpace(globalScope);
    globalScope->set("print", Value(libfuncPrint, "print"));
    globalScope->set("typeOf", Value(libfuncTypeOf, "typeOf"));
    globalScope->set("objectKeys", Value(libfuncObjectKeys, "objectKeys"));
    globalScope->set("objectSize", Value(libfuncObjectSize, "objectSize"));
    globalScope->set("input", Value(libfuncInput, "input"));
    globalScope->set("strToNum", Value(libfuncStrToNum, "strToNum"));
    globalScope->set("sqrt", Value(libfuncSqrt, "sqrt"));
    globalScope->set("cos", Value(libfuncCos, "cos"));
    globalScope->set("sin", Value(libfuncSin, "sin"));
    globalScope->set("floor", Value(libfuncFloor, "floor"));
    globalScope->set("ceil", Value(libfuncCeiling, "ceil"));
    globalScope->set("totalArguments", Value(libfuncTotalArguments, "totalArguments"));
    globalScope->set("getArgument", Value(libfuncGetArgument, "getArgument"));
    globalScope->set("objectCopy", Value(libfuncObjectCopy, "objectCopy"));
    globalScope->set("fileOpen", Value(libfuncFileOpen, "fileOpen"));
    globalScope->set("fileClose", Value(libfuncFileClose, "fileClose"));
    globalScope->set("fileGetLine", Value(libfuncFileGetLine, "fileGetLine"));
    globalScope->set("fileGetWord", Value(libfuncFileGetWord, "fileGetWord"));
    globalScope->set("fileRead", Value(libfuncFileRead, "fileRead"));
    globalScope->set("eval", Value(libfuncEval, "eval"));
    globalScope->set("exit", Value(libfuncExit, "exit"));

    dispatcher->eval(*(node[AST_TAG_CHILD]->toObjectNoConst()));
    retVal.clear();
    auto currEnv = envs.getTopAndPop();   
    while ((*currEnv.toObject())["$previous"] != nullptr) {        
        currEnv = *((*currEnv.toObjectNoConst())["$previous"]); 
        forceClosureClear(*currEnv.toObjectNoConst());              
    }

    return Value(Value::Type::NilType);
}

const Value Interpreter::evalStmts(Object& node){
    for(unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++){
        Object* stmt = node[i]->toObjectNoConst();
        dispatcher->eval(*stmt);
    }
    return Value(Value::Type::NilType);
}

const Value Interpreter::evalReduction(Object& node){
    if(node[AST_TAG_CHILD] != nullptr)
        return dispatcher->eval(*(node[AST_TAG_CHILD]->toObjectNoConst()));
    return Value(Value::Type::NilType);   
}

const Value Interpreter::evalBinaryOp(const Value leftOp, const Value rightOp, std::string op){
    auto operatorFunc = binaryOpDispatcher[op];
    Value res = Value(Value::Type::UndefType);
    try{
        res = operatorFunc(leftOp, rightOp);
    }
    catch(std::runtime_error &e){
        auto tmp = ("A++ runtime error: " + std::string(e.what()) + "\n");
        error(ErrorType::Error, currLineNo, tmp.c_str());
        exit(1);
    }
    return res;
}

const Value Interpreter::evalArithExpr(Object& node){
    auto leftOperandNode = node[AST_TAG_LEFTEXPR]->toObjectNoConst();
    auto rightOperandNode = node[AST_TAG_RIGHTEXPR]->toObjectNoConst();
    auto val1 = dispatcher->eval(*leftOperandNode);
    auto val2 = dispatcher->eval(*rightOperandNode);
    currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
    return evalBinaryOp(val1, val2, node[AST_TAG_ARITHOP_TYPE]->toString());
}

const Value Interpreter::evalRelExpr(Object& node){
    auto leftOperandNode = node[AST_TAG_LEFTEXPR]->toObjectNoConst();
    auto rightOperandNode = node[AST_TAG_RIGHTEXPR]->toObjectNoConst();
    auto val1 = dispatcher->eval(*leftOperandNode);
    auto val2 = dispatcher->eval(*rightOperandNode);
    currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
    return evalBinaryOp(val1, val2, node[AST_TAG_RELOP_TYPE]->toString());
}

const Value Interpreter::evalBoolExpr(Object& node){
    auto leftOperandNode = node[AST_TAG_LEFTEXPR]->toObjectNoConst();
    auto rightOperandNode = node[AST_TAG_RIGHTEXPR]->toObjectNoConst();    
    auto val1 = dispatcher->eval(*leftOperandNode);
    auto op = std::string(node[AST_TAG_BOOLOP_TYPE]->toString());
    try {
        if (val1){
            if (op == "or")
                return Value(true);
        } 
        else {
            if (op == "and")
                return Value(false);
        }
    }
    catch (const std::exception& e) {
        error(ErrorType::Error, currLineNo, e.what());
        exit(-1);
    }
    
    auto val2 = dispatcher->eval(*rightOperandNode);
    currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
    return evalBinaryOp(val1, val2, node[AST_TAG_BOOLOP_TYPE]->toString());
}

const Value Interpreter::evalTermParensExpr(Object& node){
    auto exprNode = node[AST_TAG_EXPR]->toObjectNoConst();
    return dispatcher->eval(*exprNode);
}

const Value Interpreter::evalTermMinusExpr(Object& node){
    auto exprNode = node[AST_TAG_EXPR]->toObjectNoConst();
    auto val = dispatcher->eval(*exprNode);

    if(val.isNumber())
        return Value(-val.toNumber());
    else{
        auto tmp = "A++ runtime error: non-arithmetic operand to unary minus\n";
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
        exit(1);  
    }
}

const Value Interpreter::evalTermNotExpr(Object& node){
    auto exprNode = node[AST_TAG_EXPR]->toObjectNoConst();
    auto val = dispatcher->eval(*exprNode);

    try{
        return Value(!val);
    }
    catch(std::runtime_error &e){
        auto tmp = ("A++ runtime error: " + std::string(e.what()) + "\n");
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp.c_str());
        exit(1);  
    }
}

void Interpreter::indexValRegIfTableOrFunc(){
    if(!objField.isUndef()){
        if(valRegister->isObject())
            valRegister = (*valRegister->toObjectNoConst())[&objField];
        else if(valRegister->isProgramFunction() && 
            !(objField.isString() && std::string(objField.toString()) == "$closure"))
            valRegister = (*valRegister->toProgramFunctionClosureNoConst())[&objField];
        if(valRegister == nullptr){
            error(ErrorType::Error, currLineNo, "A++ runtime error: Non-existent object field \"%s\"\n", objField.makeString().c_str());
            exit(1);
        }
    }
}

const Value Interpreter::evalTermPlusPlusLvalue(Object& node){
    auto lvalueNode = node[AST_TAG_LVALUE]->toObjectNoConst();
    dispatcher->eval(*lvalueNode);
    currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
    indexValRegIfTableOrFunc();
    //pre-increment
    if(!valRegister->isNumber()){
        auto tmp = "A++ runtime error: non-numeric operand to ++\n";
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
        exit(1);         
    }
    valRegister->fromDouble(valRegister->toNumber() + 1);
    return *valRegister;
}

const Value Interpreter::evalTermMinusMinusLvalue(Object& node){
    auto lvalueNode = node[AST_TAG_LVALUE]->toObjectNoConst();
    dispatcher->eval(*lvalueNode);
    currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
    indexValRegIfTableOrFunc();
    if(!valRegister->isNumber()){
        auto tmp = "A++ runtime error: non-numeric operand to --\n";
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
        exit(1);         
    }    
    //pre-decrement
    valRegister->fromDouble(valRegister->toNumber() - 1);
    return *valRegister;    
}

const Value Interpreter::evalTermLvaluePlusPlus(Object& node){
    auto lvalueNode = node[AST_TAG_LVALUE]->toObjectNoConst();
    dispatcher->eval(*lvalueNode);
    currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
    indexValRegIfTableOrFunc();
    if(!valRegister->isNumber()){
        auto tmp = "A++ runtime error: non-numeric operand to ++\n";
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
        exit(1);         
    }      
    auto retVal = *valRegister;
    //post-increment
    valRegister->fromDouble(valRegister->toNumber() + 1);
    return retVal;
}

const Value Interpreter::evalTermLvalueMinusMinus(Object& node){
    auto lvalueNode = node[AST_TAG_LVALUE]->toObjectNoConst();
    dispatcher->eval(*lvalueNode);
    currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
    indexValRegIfTableOrFunc();
    if(!valRegister->isNumber()){
        auto tmp = "A++ runtime error: non-numeric operand to --\n";
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
        exit(1);         
    }
    auto retVal = *valRegister;
    //post-decrement
    valRegister->fromDouble(valRegister->toNumber() - 1);
    return retVal;    
}

const Value Interpreter::evalAssignExpr(Object& node) {
    objField = Value(Value::Type::UndefType);
    auto lvalueNode = *(node[AST_TAG_LVALUE]->toObjectNoConst());
    Value lvalue = dispatcher->eval(lvalueNode);
    Value* lvalue_md = valRegister;
    Value lvalueObjField = objField;
    
    if(lvalueNode[AST_TAG_ID] != nullptr && validDollarIdents.find(lvalueNode[AST_TAG_ID]->toString()) != validDollarIdents.end()){
        auto tmp = lvalueNode[AST_TAG_ID]->toString();
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ Runtime Error: \"%s\" is not an lvalue\n", tmp);
        exit(1);        
    }
    if (lvalue_md->isLibraryFunction()) {
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ Runtime Error: Cannot assign expression to library function\n");
        exit(1);
    }
    Value expr = dispatcher->eval(*(node[AST_TAG_EXPR]->toObjectNoConst()));

    if(!lvalueObjField.isUndef()&& !(lvalueObjField.isString() 
        && std::string(lvalueObjField.toString()) == "$closure")){ //trying to index something
        assert(lvalue_md->isObject() || lvalue_md->isProgramFunction());
        if(lvalueObjField.isString()){
            std::string idString = lvalueObjField.toString();
            if(idString.length() >= 1 && idString[0] == '$' && validDollarFields.find(idString) == validDollarFields.end()){
                error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ Runtime Error: invalid \"$\" index\n");
                exit(1);
            }
        }    
        Object *affectedObject = (lvalue_md->isObject()) ? (lvalue_md->toObjectNoConst()) : (lvalue_md->toProgramFunctionClosureNoConst());
        if(expr.isNil())
            affectedObject->remove(&lvalueObjField);    //field removal
        else
            affectedObject->set(&lvalueObjField, expr); //field modification
    }
    else if(lvalueObjField.isString() && std::string(lvalueObjField.toString()) == "$closure") {//trying to modify function.$closure
            assert(lvalue_md->isProgramFunction());
            auto tmp = strdup(lvalue_md->toProgramFunctionName());
            lvalue_md->fromProgramFunction(lvalue_md->toProgramFunctionASTNoConst(), 
                expr.toObjectNoConst(), tmp);
            free(tmp);
    }
    else
        *lvalue_md = expr;
    
    return expr;
}

const Value Interpreter::evalLvalueId(Object& node) {
    auto id = node[AST_TAG_ID]->toString();
    //lookup id in env
    if (std::string(id).size() >= 1 && id[0] == '$') {
        if (validDollarIdents.find(std::string(id)) == validDollarIdents.end()) {
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ Runtime Error: %s keyword not supported as lvalue\n", id);
            exit(1);
        }
    }
    if (std::string(id) == "$env") {
        retVal = envs.top();
        valRegister = &retVal;
        return retVal;
    }
    if (std::string(id) == "$lambda") {
        return *currentFunction;
    }
    Value *existentSymbol = lookupId(id);
    if(existentSymbol == nullptr)
        existentSymbol = declareId(id);
    valRegister = existentSymbol;
    Value v = *existentSymbol;
    return *existentSymbol;
}

const Value Interpreter::evalLvalueGlobalId(Object& node) {
    auto id = node[AST_TAG_GLOBALID]->toString();
    //lookup id in global env
    Value *existentSymbol = lookupGlobalId(id);
    if(existentSymbol == nullptr){
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: reference to undeclared global id \"%s\"\n", id);
        exit(1);
    }    
    valRegister = existentSymbol;
    return *existentSymbol;
}

const Value Interpreter::evalLvalueLocalId(Object& node) {
    auto id = node[AST_TAG_LOCALID]->toString();
    //lookup id in current env
    Value *existentSymbol = lookupIdCurrEnvOnly(id);
    if(existentSymbol == nullptr)
        existentSymbol = declareId(id);
    valRegister = existentSymbol;
    return *existentSymbol;
}

const Value Interpreter::evalLvalueMember(Object& node) {
    const Value member = dispatcher->eval(*(node[AST_TAG_MEMBER]->toObjectNoConst()));
    return member;
}

const Value Interpreter::fieldAccess(const Value caller, const Value* id, double lineNo) {
    Object* object;
    if(id->isString()){ //checks for valid $ indices
        auto idString = std::string(id->toString());
  
        if (caller.isProgramFunction() && idString == "$closure") {
            objField = *id;
            return Value(caller.toProgramFunctionClosureNoConst());
        }        
        else if(idString == "$closure"){
            error(ErrorType::Error, lineNo, "A++ Runtime Error: only functions support \"$closure\" indices\n");
            exit(1);         
        }
    }
    
    if (caller.isObject()) object = caller.toObjectNoConst();
    else if (caller.isProgramFunction()) object = caller.toProgramFunctionClosureNoConst();
    else {
        error(ErrorType::Error, lineNo, "A++ Runtime Error: indexing non-table variable\n");
        exit(1);
    }
    if(!id->isNumber() && !id->isString()){
        error(ErrorType::Error, lineNo, "A++ Runtime Error: Unsupported key type, supported key types are: number, string\n");
        exit(1);
    }
    Value *fieldContents = (*object)[id];
    objField = *id;
    if(fieldContents == nullptr) {//field not found  
        return Value(Value::Type::NilType);      
    }

    return *fieldContents;
}

const Value Interpreter::evalMemberId(Object& node) {
    objField = Value(Value::Type::UndefType);
    const Value caller = dispatcher->eval(*(node[AST_TAG_CALLER]->toObjectNoConst()));
    currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
    indexValRegIfTableOrFunc();
    Value* id = node[AST_TAG_ID];
    return fieldAccess(caller, id, node[AST_TAG_LINE_KEY]->toNumber());
    
}

const Value Interpreter::evalMemberExpr(Object& node) {
    objField = Value(Value::Type::UndefType);
    Value *indexedObj = nullptr;
    const Value caller = dispatcher->eval(*(node[AST_TAG_CALLER]->toObjectNoConst()));
    currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
    indexValRegIfTableOrFunc();
    indexedObj = valRegister;
    const Value expr = dispatcher->eval(*(node[AST_TAG_EXPR]->toObjectNoConst()));
    valRegister = indexedObj;
    return fieldAccess(caller, &expr, node[AST_TAG_LINE_KEY]->toNumber());
}

Value Interpreter::makeCallFromObject(const Value* calledFunc, const Value callsuffix, double lineNo) {
    auto func = (*(calledFunc->toObjectNoConst()))["()"];
    if (func != nullptr) {
        //add calledFunc to callsuffix
        const Object *oldCallsuffix = callsuffix.toObjectNoConst();
        Object* newCallsuffix = new Object();
        Object *lvalueArg = new Object();
        lvalueArg->set("$$value", *calledFunc);
        newCallsuffix->set((double) 0, Value(lvalueArg));
            
        if (callsuffix.isObject()) {
            for (unsigned int i = 0; i < oldCallsuffix->getTotal(); i++) {
                newCallsuffix->set((double) i + 1, (*(*oldCallsuffix)[i]));
            }
        }            
        return makeCall(func, newCallsuffix, lineNo);
    } else {
        error(ErrorType::Error, lineNo, "A++ Runtime Error: Object is not a functor\n");
        exit(1);
    }
}

Value Interpreter::makeCallFromLibFunc(const Value* calledFunc, const Value callsuffix, double lineNo) {
    Object fscope = Object();
    if (!callsuffix.isNil()) {
        for (unsigned int i = 0; i < callsuffix.toObject()->getTotal(); i++) {
            auto argPair = *(*callsuffix.toObjectNoConst())[i];
            if (((*(argPair.toObjectNoConst()))["$$key"] != nullptr)) {
                error(ErrorType::Error, lineNo, "A++ Runtime Error: Keyword arguments are not allowed in library functions\n");
                exit(1);
            }
            fscope.set(i, *((*(argPair.toObjectNoConst()))["$$value"]));
        }
    }
    if(currentFunction == nullptr)
        fscope.set("$caller", Value("@_invalid"));
    else fscope.set("$caller", *currentFunction);
    fscope.set("$lineNo", lineNo);
    if(currFuncArgsEnv == nullptr)
        fscope.set("$callerEnv", Value("@_invalid"));
    else fscope.set("$callerEnv", Value(currFuncArgsEnv));
    fscope.set("$numCallerArgs", (double)currentFuncNumArgs);
    //call lvalue
    (calledFunc->toLibraryFunction())(fscope);
    if (fscope["$retval"] != nullptr) {
        return *fscope["$retval"];
    }

    return Value(Value::Type::NilType);
}

Value Interpreter::makeCallFromProgFunc(const Value* calledFunc, const Value callsuffix, double lineNo) {
    auto idlist = (*calledFunc->toProgramFunctionAST())[AST_TAG_IDLIST];
    Object *node = nullptr;
    //std::vector<Object*> *formals = nullptr;
    unsigned formalsLen = 0;
    if (idlist != nullptr) {
        node = idlist->toObjectNoConst();
        formalsLen = (*node)[AST_TAG_NUMCHILDREN]->toNumber();
    }
    Object *actuals = nullptr;
    unsigned actualsLen = 0;
    if (!callsuffix.isNil()) {
        actuals = callsuffix.toObjectNoConst();  
        actualsLen = actuals->getTotal();          
    } 
    unsigned int i;
    pushScopeSpace(calledFunc->toProgramFunctionClosureNoConst());
    pushNested();
    Value* prevFunc = currentFunction;
    int prevNumArgs = currentFuncNumArgs;
    Object *prevEnv = currFuncArgsEnv;
    currentFunction = const_cast<Value*>(calledFunc);
    currentFuncNumArgs = actualsLen;
    currFuncArgsEnv = envs.top().toObjectNoConst();
    std::set<std::string> insertedArgs;
    std::vector<std::string> formalsNames;
    for (i = 0; i < formalsLen; i++)
        formalsNames.push_back((*(*node)[i]->toObjectNoConst())[AST_TAG_ID]->toString());    
    //this loop inserts the actuals in the function scope    
    for (i = 0; i < actualsLen; i++) {
        auto arg = ((*actuals)[i]->toObjectNoConst());
        std::string newIdName;
        if ((*arg)["$$key"] == nullptr) { //positional arg
            if (i < formalsLen) { //is matched to an actual
                newIdName = (*((*node)[i]->toObjectNoConst()))[AST_TAG_ID]->toString();
                auto newId = declareId(newIdName);
                *newId = *((*arg)["$$value"]);
            } else {
                newIdName = std::to_string(i);
                auto newId = declareId(newIdName);
                *newId = *((*arg)["$$value"]);
            }
            insertedArgs.insert(newIdName);
        } 
        else { //keyword arg
            std::string newIdName = std::string((*arg)["$$key"]->toString());
            if(insertedArgs.find(newIdName) != insertedArgs.end()){
                error(ErrorType::Error, lineNo, "A++ runtime error: argument set more than once\n");
                exit(1);  
            }
            auto it = find(formalsNames.begin(), formalsNames.end(), newIdName);
            if(it == formalsNames.end()){
                error(ErrorType::Error, lineNo, "A++ runtime error: unexpected keyword argument\n");
                exit(1);                    
            }
            int index = std::distance(formalsNames.begin(), it);
            auto newId = declareId(formalsNames[index]);
            *newId = *((*arg)["$$value"]);
            insertedArgs.insert(newIdName);
        }
    }
    for (i = 0; i < formalsLen; i++) {
        auto formalName = formalsNames[i];
        if(lookupIdCurrEnvOnly(formalName) == nullptr){
            auto formal = declareId(formalName);
            auto defaultValueNode = ((*(*node)[i]->toObjectNoConst()))[AST_TAG_EXPR];
            if(defaultValueNode != nullptr){
                auto defaultValue = dispatcher->eval(*defaultValueNode->toObjectNoConst());
                *formal = defaultValue;
            }
            else{
                *formal = Value(Value::Type::UndefType);
                error(ErrorType::Warning, lineNo, "Argument %s is undefined\n", formalName.c_str());
            }
        }
    }
    auto funcNode = calledFunc->toProgramFunctionASTNoConst();
    noScope = true;
    Value toReturn = Value(Value::Type::NilType);
    try {
        dispatcher->eval(*((*funcNode)[AST_TAG_BLOCK]->toObjectNoConst()));
    }
    catch (const ReturnException& e) {
        toReturn = e.v;
    }
    currentFunction = prevFunc;
    currentFuncNumArgs = prevNumArgs;
    currLineNo = lineNo;
    currFuncArgsEnv = prevEnv;
    tmpFunc();
    popScopeSpace();   
    return toReturn;
}

const Value Interpreter::makeCall(const Value* calledFunc, const Value callsuffix, double lineNo) {
    //check if lvalue function (user or lib)
    if (calledFunc->isLibraryFunction()) {
        retVal =  makeCallFromLibFunc(calledFunc, callsuffix, lineNo);
    } else if (calledFunc->isProgramFunction()){
        retVal =  makeCallFromProgFunc(calledFunc, callsuffix, lineNo);
    } else if (calledFunc->isObject()) {
        retVal = makeCallFromObject(calledFunc, callsuffix, lineNo);
    } else {
        error(ErrorType::Error, lineNo, "A++ Runtime Error: Not a function\n");
        exit(1);
    }
    valRegister = &retVal;
    objField = Value(Value::Type::UndefType);
    return retVal;
}

const Value Interpreter::evalCall(Object& node) {
    ASTCreator::setOptionalParent(&node);
    const Value lvalue = dispatcher->eval(*(node[AST_TAG_LVALUE]->toObjectNoConst()));
    Value* caller = new Value(lvalue);
    const Value tmpCallsuffix = dispatcher->eval(*(node[AST_TAG_CALLSUFFIX]->toObjectNoConst()));
    bool isMethodCall = false;
    Object *newCallsuffix;        
    Value* calledFunc = valRegister;
    if (calledFunc != nullptr) {
        if(!caller->isObject()){
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: method caller is not an object\n");
            exit(1);            
        }
        calledFunc = (*caller->toObject())[calledFunc->toString()];
        
        if (calledFunc == nullptr) {
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: non-existent object field\n");
            exit(1);
        }      

        if ((*(node[AST_TAG_CALLSUFFIX]->toObject()))[AST_TAG_METHODCALL] != nullptr) {
            isMethodCall = true;
            const Object *oldCallsuffix; 
            newCallsuffix = new Object();
            Object *lvalueArg = new Object();
            lvalueArg->set("$$value", *caller);

            newCallsuffix->set((double) 0, Value(lvalueArg));
            if (tmpCallsuffix.isObject()) {
                oldCallsuffix = tmpCallsuffix.toObjectNoConst();
                for (unsigned int i = 0; i < oldCallsuffix->getTotal(); i++) {
                    newCallsuffix->set((double) i + 1, (*(*oldCallsuffix)[i]));
                }
            }
                        
        }
    } else {
        calledFunc = caller;       
    }

    const Value callsuffix = (isMethodCall) ? Value(newCallsuffix) : tmpCallsuffix;
    auto ret = makeCall(calledFunc, callsuffix, (node[AST_TAG_LINE_KEY]->toNumber()));
    caller->clear();
    delete caller;

    return ret;
}

const Value Interpreter::evalMultiCall(Object& node) {
    ASTCreator::setOptionalParent(&node);
    const Value call = dispatcher->eval(*(node[AST_TAG_CALL]->toObjectNoConst()));
    Value elist = Value(Value::Type::NilType);
    if (node[AST_TAG_ELIST] != nullptr) elist = dispatcher->eval(*(node[AST_TAG_ELIST]->toObjectNoConst()));
    return makeCall(&call, elist, node[AST_TAG_LINE_KEY]->toNumber());
}
const Value Interpreter::evalFdefCall(Object& node) {
    const Value funcdef = dispatcher->eval(*(node[AST_TAG_FUNCDEF]->toObjectNoConst()));
    Value elist = Value(Value::Type::NilType);
    if (node[AST_TAG_ELIST] != nullptr) elist = dispatcher->eval(*(node[AST_TAG_ELIST]->toObjectNoConst()));
    return makeCall(&funcdef, elist, node[AST_TAG_LINE_KEY]->toNumber());
}
const Value Interpreter::evalNormCallSuffix(Object& node) {
    const Value normcall = dispatcher->eval(*(node[AST_TAG_NORMCALL]->toObjectNoConst()));
    return normcall;
}
const Value Interpreter::evalMethodCallSuffix(Object& node) {
    const Value methodcall = dispatcher->eval(*(node[AST_TAG_METHODCALL]->toObjectNoConst()));
    return methodcall;
}
const Value Interpreter::evalNormCall(Object& node) {
    if (node[AST_TAG_ELIST] != nullptr) {
        const Value elist = dispatcher->eval(*(node[AST_TAG_ELIST]->toObjectNoConst()));
        valRegister = nullptr;
        return elist;
    }
    valRegister = nullptr;
    return Value(Value::Type::NilType);
}
const Value Interpreter::evalMethodCall(Object& node) {
    Value *tmp =  node[AST_TAG_ID];   
    valRegister = tmp;
    if (node[AST_TAG_ELIST] != nullptr) {
        const Value toReturn = dispatcher->eval(*(node[AST_TAG_ELIST]->toObjectNoConst()));
        valRegister = tmp;
        return toReturn;
    }
    return Value(Value::Type::NilType);
}
const Value Interpreter::evalElist(Object& node) {
    if (node[AST_TAG_ELISTNOTEMPTY] != nullptr) {
        return dispatcher->eval(*node[AST_TAG_ELISTNOTEMPTY]->toObjectNoConst());
    }
    return Value(Value::Type::NilType);
}

const Value Interpreter::evalElistNotEmpty(Object& node) {
    Object *tmp = new Object();
    for (unsigned i = 0; i < (node[AST_TAG_NUMCHILDREN]->toNumber()); i++) {
        auto e = node[i]->toObjectNoConst();
        assert(std::string((*e)[AST_TAG_SUBTYPE_KEY]->toString()) == std::string(AST_TAG_ARGUMENT));
        const Value val = dispatcher->eval(*((*e)[AST_TAG_EXPR]->toObjectNoConst()));
        Object* argPair = new Object();
        if ((*e)[AST_TAG_ID] != nullptr) 
            argPair->set("$$key", (*e)[AST_TAG_ID]->toString());
        argPair->set("$$value", val);
        tmp->set(i, Value(argPair));
    }
    return Value(tmp);
}

const Value Interpreter::evalObjElistNotEmpty(Object& node) {
    Object *tmp = new Object();
    for (unsigned i = 0; i < (node[AST_TAG_NUMCHILDREN]->toNumber()); i++) {
        auto e = node[i]->toObjectNoConst();
        const Value val = dispatcher->eval(*e);
        if(!val.isNil())
            tmp->set(i, Value(val));
    }
    return Value(tmp);
}

const Value Interpreter::evalObjectDef(Object& node) {
    if (node[AST_TAG_OBJECTDINNER] != nullptr)
        return dispatcher->eval(*node[AST_TAG_OBJECTDINNER]->toObjectNoConst());
    
    return Value(new Object());
}
const Value Interpreter::evalObjectDinnerElistnotempty(Object& node) {
    return dispatcher->eval(*(node[AST_TAG_OBJELISTNOTEMPTY]->toObjectNoConst()));
}
const Value Interpreter::evalObjectDinnerIndexed(Object& node) {
    return dispatcher->eval(*(node[AST_TAG_INDEXED]->toObjectNoConst()));
} 

const Value Interpreter::evalIndexed(Object& node){
    return dispatcher->eval(*(node[AST_TAG_COMMAINDEXED]->toObjectNoConst()));    
}

const Value Interpreter::evalCommaIndexed(Object& node){    
    Object* toReturn = new Object();
    Object* tmp;
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        Object* e = node[i]->toObjectNoConst();
        auto v = dispatcher->eval(*e);
        tmp = v.toObjectNoConst();
        if (!((*tmp)["$$key"]->isNumber() || (*tmp)["$$key"]->isString())) {
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ Runtime Error: Unsupported key type, supported key types are: number, string\n");
            exit(1);
        }        
        if(!(*tmp)["$$val"]->isNil())
            toReturn->set((*tmp)["$$key"], *(*tmp)["$$val"]);
    }
   return Value(toReturn);
}

const Value Interpreter::evalIndexedElem(Object& node){ 
    const Value key = dispatcher->eval(*(node[AST_TAG_OBJECT_KEY]->toObjectNoConst()));
    const Value value = dispatcher->eval(*(node[AST_TAG_OBJECT_VALUE]->toObjectNoConst()));    
    
    Object *tmp = new Object();
    tmp->set(std::string("$$key"), key);
    tmp->set(std::string("$$val"), value);

    return Value(tmp);
}

void Interpreter::tmpFunc() {
    auto currEnv = envs.getTopAndPop();
    bool shouldSliceOuter = (*currEnv.toObject())["$previous"] != nullptr;
    retVal.clear();
    while ((*currEnv.toObject())["$previous"] != nullptr){
        currEnv = *((*currEnv.toObjectNoConst())["$previous"]);
        forceClosureClear(*currEnv.toObjectNoConst());        
    }
    if ((*currEnv.toObjectNoConst())["$outer"] == nullptr) {
        error(ErrorType::Error, currLineNo, "A++ Runtime Error: Corrupted outer environment chain\n");
        exit(1);
    }
    envs.push(*(*currEnv.toObjectNoConst())["$outer"]);
    if (shouldSliceOuter) {
        pushSlice();
    }
}

const Value Interpreter::evalBlock(Object& node){
    try {
        if (node[AST_TAG_STMTS] != nullptr) {
            if (noScope){
                noScope = false;
                dispatcher->eval(*(node[AST_TAG_STMTS]->toObjectNoConst()));
            }
            else {
                pushNested();
                dispatcher->eval(*(node[AST_TAG_STMTS]->toObjectNoConst()));
                currLineNo = node[AST_TAG_LINE_KEY]->toNumber();
                tmpFunc();
            }
        }       
    }
    catch (const BreakException&) {
        throw;
    }
    catch (const ContinueException&) {
        throw;
    } 
    catch (const ReturnException&) {
        throw;
    }
    return Value(Value::Type::NilType);    
}

const Value Interpreter::evalFuncDef(Object& node){
    Value fvalue = Value(Value::Type::UndefType);
    Value fname = dispatcher->eval(*(node[AST_TAG_FUNCPREFIX]->toObjectNoConst()));
    if (valRegister != nullptr) {
        valRegister->fromProgramFunction(&node, envs.top().toObjectNoConst(), fname.toString());
        fvalue = *valRegister;
    } else {
        fvalue.fromProgramFunction(&node, envs.top().toObjectNoConst(), "<ANONYMOUS_FUNCTION>");
    }
    valRegister = nullptr;
    pushSlice();
    return fvalue;
}

const Value Interpreter::evalFuncPrefix(Object& node){ 
    if (node[AST_TAG_CHILD] != nullptr) 
        return dispatcher->eval(*(node[AST_TAG_CHILD]->toObjectNoConst()));
    valRegister = nullptr;
    return Value(Value::Type::NilType);
}

const Value Interpreter::evalFuncNameId(Object& node){ 
    auto fname = node[AST_TAG_ID];
   
    if (lookupIdCurrEnvOnly(fname->toString()) != nullptr) {
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), 
        "A++ runtime error: identifier %s has already been declared\n", fname->toString());
        exit(1);
    }
    valRegister = declareId(fname->toString());
    return Value(fname->toString());
}

const Value Interpreter::evalConst(Object& node){
    return *(node[AST_TAG_VALUE]);    
}

const Value Interpreter::evalCommaIdList(Object& node){
    for (unsigned int i = 0; i < node[AST_TAG_NUMCHILDREN]->toNumber(); i++) {
        Object* e = node[i]->toObjectNoConst();
        dispatcher->eval(*((*e)[AST_TAG_ID]->toObjectNoConst()));
    }
    return Value(Value::Type::NilType);
}

const Value Interpreter::evalIfPrefix(Object& node){
    return dispatcher->eval(*(node[AST_TAG_EXPR]->toObjectNoConst()));    
}

const Value Interpreter::evalIfStmt(Object& node){
    const Value cond = dispatcher->eval(*node[AST_TAG_IFPREFIX]->toObjectNoConst());    
    bool condBool;

    try {
        condBool = cond;
    }
    catch (const std::exception& e) {
        error(ErrorType::Error, currLineNo, e.what());
        exit(-1);
    }
    if (condBool)
        dispatcher->eval(*(node[AST_TAG_IFSTMT_IFBODY]->toObjectNoConst()));
    else {
        if (node[AST_TAG_IFSTMT_ELSEBODY] != nullptr)
            dispatcher->eval(*(node[AST_TAG_IFSTMT_ELSEBODY]->toObjectNoConst()));        
    }
    return Value(Value::Type::NilType);
}

const Value Interpreter::evalWhileCond(Object& node){
    const Value cond = dispatcher->eval(*node[AST_TAG_EXPR]->toObjectNoConst());    
    bool condBool;

    try {
        condBool = cond;
    }
    catch (const std::exception& e) {
        error(ErrorType::Error, currLineNo, e.what());
        exit(-1);
    }
    return Value(condBool);    
}

const Value Interpreter::evalWhileStmt(Object& node){    
    while(dispatcher->eval(*(node[AST_TAG_WHILECOND]->toObjectNoConst()))) {
        try {
            dispatcher->eval(*node[AST_TAG_STMT]->toObjectNoConst());
        }
        catch (const BreakException&) {
            break;
        }
        catch (const ContinueException&) {
            continue;
        }
    }
    return Value(Value::Type::NilType);
}

const Value Interpreter::evalForStmt(Object& node){
    Object *forPrefix = node[AST_TAG_FORPREFIX]->toObjectNoConst();

    if ((*forPrefix)[AST_TAG_ELIST] != nullptr)
        dispatcher->eval(*(*forPrefix)[AST_TAG_ELIST]->toObjectNoConst());

    Object *forCond = (*forPrefix)[AST_TAG_EXPR]->toObjectNoConst();       
    bool condBool;

    while (1) {
        try {
            condBool = dispatcher->eval(*forCond);
            if (!condBool)
                break;
            dispatcher->eval(*node[AST_TAG_STMT]->toObjectNoConst());
        }
        catch (const BreakException&) {
            break;
        }
        catch (const ContinueException&) {
            continue;
        }
        catch (const std::exception& e) {
            error(ErrorType::Error, currLineNo, e.what());
            exit(-1);
        }
        if (node[AST_TAG_ELIST] != nullptr)
            dispatcher->eval(*node[AST_TAG_ELIST]->toObjectNoConst());
    }
    return Value(Value::Type::NilType);
}

const Value Interpreter::evalReturnStmt(Object& node){ 
    if (node[AST_TAG_EXPR] != nullptr)
        throw ReturnException(dispatcher->eval(*node[AST_TAG_EXPR]->toObjectNoConst()));
    else 
        throw ReturnException(Value(Value::Type::NilType));    
}

const Value Interpreter::evalBreak(Object& node){ 
    throw BreakException();
}

const Value Interpreter::evalContinue(Object& node){ 
    throw ContinueException();
}

const Value Interpreter::evalValueStorage(Object& node){
    return *(node[AST_TAG_VALUE]);
}

const Value Interpreter::evalQuasiQuotes(Object& node){
    auto code = dispatcher->eval(*(node[AST_TAG_CHILD]->toObjectNoConst()));
    CopyTreeVisitor cpVis( code.toObjectNoConst() );
    TreeHost h = TreeHost();
    h.accept(&cpVis, *code.toObjectNoConst());
    Object *res = cpVis.getResult();
    SetParentTreeVisitor tempParentSetter(false);
    h.accept(&tempParentSetter, *res);
    EvalEscapesTreeVisitor escVis;
    escVis.evalEscape = ([this](Object &n) { return this->evalEscape(n); });
    h.accept(&escVis, *res);
    tempParentSetter.setIsRemoval(true);
    h.accept(&tempParentSetter, *res);
    //res->incRefCounter();
    //assert(res->getRefCounter() == 1);

    return Value(res);
}

const Value Interpreter::evalQuotedRules(Object& node){
    return *node[AST_TAG_CHILD];
}

int Interpreter::stealManyChildren(Object *insertionPoint, Object *stealPoint, Object *stealAncestor){
    auto oldNumChildren = (*insertionPoint)[AST_TAG_NUMCHILDREN]->toNumber();
    bool childFound = false;    
    int insertionIndex = -1;
    std::vector<Value> childrenVector = std::vector<Value>();
    for(int i = 0; i < oldNumChildren; i++){ //find all children that are after inline stmt
        auto currChild = (*insertionPoint)[i];
        if(currChild->toObjectNoConst() == stealAncestor){
            insertionIndex = i;
            childFound = true;
        }
        if(childFound)
            childrenVector.push_back(insertionPoint->getAndRemove(i));
    }      
    assert(insertionIndex >= 0);
    int numChildrenToInsert = (*stealPoint)[AST_TAG_NUMCHILDREN]->toNumber();
    for(int i = 0; i < numChildrenToInsert; i++){ //insert all new children
        insertionPoint->set(insertionIndex + i, *((*stealPoint)[i]));
        (*(*stealPoint)[i]).toObjectNoConst()->set(PARENT_FIELD, Value(insertionPoint));
    }
    for(unsigned i = 1; i < childrenVector.size(); i++){ //append the previous children
        insertionPoint->set(insertionIndex + i + numChildrenToInsert - 1, 
            childrenVector[i]);
    }
    insertionPoint->set(AST_TAG_NUMCHILDREN, Value(oldNumChildren - 1 + numChildrenToInsert)); 
    return insertionIndex;   
}

Object *Interpreter::insertStmtsAst(Object *node, Object *stmtsRoot){
    assert((*stmtsRoot)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_STMTS));
    Object *stmtsAncestor = node, *stmtAncestor = node;
    for(int i = 0; i < 5; i++){ //[something] -> stmt -(parent of)-> expr -> term -> primary -> inline = node
        stmtAncestor = stmtsAncestor;
        if((*stmtsAncestor)[PARENT_FIELD] == nullptr){
            std::string tmp = "A++ staging error: statements cannot be injected in this context\n";
            error(ErrorType::Error, (*stmtsAncestor)[AST_TAG_LINE_KEY]->toNumber(), tmp.c_str());
            exit(1);
        }
        stmtsAncestor = (*stmtsAncestor)[PARENT_FIELD]->toObjectNoConst();
    }
    std::set<std::string> allowedTypes = {AST_TAG_FORSTMT, AST_TAG_WHILESTMT, AST_TAG_IFSTMT};
    bool singleStmtConstruct = false;
    if(allowedTypes.find((*stmtsAncestor)[AST_TAG_SUBTYPE_KEY]->toString()) != allowedTypes.end()){
        //belongs to a single-line if, for, while
        singleStmtConstruct = true;
        if((*stmtsRoot)[AST_TAG_NUMCHILDREN]->toNumber() == 1){
            Object *stmtAncestorChild = (*stmtAncestor)[AST_TAG_CHILD]->toObjectNoConst();
            stmtAncestor->set(AST_TAG_CHILD, *(*stmtsRoot)[(double)0]);
            (*stmtAncestor)[AST_TAG_CHILD]->toObjectNoConst()->set(PARENT_FIELD, stmtAncestor);
            assert(stmtAncestorChild->getRefCounter() == 1);
            stmtAncestorChild->incRefCounter();
            ASTCreator::destroyAST(stmtAncestorChild);    
            return stmtAncestor;        
        }
        
        Object *newBlock = new Object(), *newStmts = new Object(), *newStmt = new Object();
        newBlock->set(AST_TAG_TYPE_KEY, Value(AST_TAG_BLOCK)); //make block
        newBlock->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_BLOCK));
        newBlock->set(AST_TAG_LINE_KEY, *((*stmtAncestor)[AST_TAG_LINE_KEY]));

        newStmts->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMTS)); //make stmts
        newStmts->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMTS));
        newStmts->set(AST_TAG_LINE_KEY, *((*stmtAncestor)[AST_TAG_LINE_KEY]));
        newStmts->set(AST_TAG_NUMCHILDREN, Value((double)1));      

        newStmt->set(AST_TAG_TYPE_KEY, Value(AST_TAG_STMT)); //make stmt
        newStmt->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_STMT));
        newStmt->set(AST_TAG_LINE_KEY, *((*stmtAncestor)[AST_TAG_LINE_KEY]));
        //create a construction of the form if, for, while -> stmt -> block -> stmts -> old stmt

        newBlock->set(AST_TAG_STMTS, Value(newStmts)); //block <-> stmts
        newStmts->set(PARENT_FIELD, Value(newBlock));

        newStmts->set((double)0, Value(newStmt)); //stmts -> stmt (and steal child)
        newStmt->set(PARENT_FIELD, Value(newStmts));
        newStmt->set(AST_TAG_CHILD, *(*stmtAncestor)[AST_TAG_CHILD]);
        ((*stmtAncestor)[AST_TAG_CHILD]->toObjectNoConst())->set(PARENT_FIELD, newStmt);

        //stmt <-> block
        newBlock->set(PARENT_FIELD, Value(stmtAncestor));
        stmtAncestor->set(AST_TAG_CHILD, Value(newBlock));
        
        newBlock->set(PARENT_FIELD, *((*stmtAncestor)[PARENT_FIELD]));
        stmtsAncestor = newStmts;
        stmtAncestor = newStmt;
    }
    if(!((*stmtsAncestor)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_STMTS))){
        std::string tmp = "A++ staging error: statements cannot be injected in this context\n";
        error(ErrorType::Error, (*stmtsAncestor)[AST_TAG_LINE_KEY]->toNumber(), tmp.c_str());
        exit(1);
    }
    assert((*stmtAncestor)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_STMT));
    
    int index = stealManyChildren(stmtsAncestor, stmtsRoot, stmtAncestor);
    // stmtAncestor is in fact an ancestor of "node"
    assert(stmtAncestor->getRefCounter() == 1);
    stmtAncestor->incRefCounter();
    ASTCreator::destroyAST(stmtAncestor);
    if(singleStmtConstruct)
        return (*stmtsAncestor)[PARENT_FIELD]->toObjectNoConst();
    else
        return ((*stmtsAncestor)[index])->toObjectNoConst();
}

Object *Interpreter::insertExprAst(Object *node, Object *exprRoot){
    assert((*exprRoot)[AST_TAG_TYPE_KEY]->toString() == std::string(AST_TAG_EXPR) || 
        (*exprRoot)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_VALUESTORAGE));
    Object *exprParent = node, *oldExprChild;
    for(int i = 0; i < 3; i++){
        oldExprChild = exprParent;
        exprParent = (*exprParent)[PARENT_FIELD]->toObjectNoConst();
    }
    assert((*exprParent)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_EXPR));
    exprRoot->set(PARENT_FIELD, Value(exprParent));
    exprParent->set(AST_TAG_CHILD, Value(exprRoot)); 
    assert(oldExprChild->getRefCounter() == 1); //inline node should die here
    oldExprChild->incRefCounter();
    ASTCreator::destroyAST(oldExprChild);    
    return exprRoot;
}

Object *Interpreter::insertExprListAst(Object *node, Object *elistRoot){
    assert((*elistRoot)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_OBJELISTNOTEMPTY));
    Object *elistAncestor = node, *exprAncestor = node;
    for(int i = 0; i < 4; i++){ //(possibly) arg/objelistnotempty-> expr -> term -> primary -> inline = node
        exprAncestor = elistAncestor;
        if((*elistAncestor)[PARENT_FIELD] == nullptr){
            std::string tmp = "A++ staging error: expression list cannot be injected in this context\n";
            error(ErrorType::Error, (*elistAncestor)[AST_TAG_LINE_KEY]->toNumber(), tmp.c_str());
            exit(1);   
        }
        elistAncestor = (*elistAncestor)[PARENT_FIELD]->toObjectNoConst();
    }  
    std::string listAncestorType = (*elistAncestor)[AST_TAG_SUBTYPE_KEY]->toString();
    if(!( listAncestorType == std::string(AST_TAG_ARGUMENT) || 
        listAncestorType == std::string(AST_TAG_OBJELISTNOTEMPTY))){
        std::string tmp = "A++ staging error: expression list cannot be injected in this context\n";
        error(ErrorType::Error, (*elistAncestor)[AST_TAG_LINE_KEY]->toNumber(), tmp.c_str());
        exit(1);            
    }
    if((*elistAncestor)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_ARGUMENT)){
        exprAncestor = elistAncestor;
        elistAncestor = (*elistAncestor)[PARENT_FIELD]->toObjectNoConst();
        auto numChildren = (*elistRoot)[AST_TAG_NUMCHILDREN]->toNumber();
        for(int i = 0; i < numChildren; i++){ //convert expr children to args
            auto newArg = new Object();
            newArg->set(AST_TAG_TYPE_KEY, Value(AST_TAG_ARGUMENT));
            newArg->set(AST_TAG_SUBTYPE_KEY, Value(AST_TAG_ARGUMENT));
            newArg->set(AST_TAG_LINE_KEY, Value((*node)[AST_TAG_LINE_KEY]->toNumber()));
            newArg->set(AST_TAG_EXPR, *((*elistRoot)[i]));
            elistRoot->set(i, Value(newArg));
            newArg->set(PARENT_FIELD, elistRoot);
        }
    }
    listAncestorType = (*elistAncestor)[AST_TAG_SUBTYPE_KEY]->toString();
 
    int index = stealManyChildren(elistAncestor, elistRoot, exprAncestor);
    assert(exprAncestor->getRefCounter() == 1);
    exprAncestor->incRefCounter();
    ASTCreator::destroyAST(exprAncestor);  //exprAncestor will also destroy node
    if(listAncestorType == AST_TAG_ELISTNOTEMPTY)
        return (*((*elistAncestor)[index])->toObjectNoConst())[AST_TAG_EXPR]->toObjectNoConst();
    return ((*elistAncestor)[index])->toObjectNoConst();    
}

Object* Interpreter::insertAst(Object& node, Object *ast){
    TreeHost h = TreeHost();
    SetParentTreeVisitor v(false);
    h.accept(&v, *ast); //form parent links for the new tree    

    if((*ast)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_STMTS))
        return  insertStmtsAst(&node, ast);
    else if((*ast)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_VALUESTORAGE))
        return insertExprAst(&node, ast);
    else if((*ast)[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_OBJELISTNOTEMPTY)){
        if((*ast)[AST_TAG_NUMCHILDREN]->toNumber() == 1)
            return insertExprAst(&node, (*ast)[(double) 0]->toObjectNoConst());    
        else
            return insertExprListAst(&node, ast);
    }
    else{
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ staging error: inlining or escaping something "
                "that is neither statements nor a list of expressions\n");
        exit(-1);
    }
}

const Value Interpreter::evalEscape(Object& node){
    Value code = Value(Value::Type::NilType);
    if(node[AST_TAG_SUBTYPE_KEY]->toString() == std::string(AST_TAG_ESCAPE_EXPR)){
        code = dispatcher->eval(*(node[AST_TAG_EXPR]->toObjectNoConst()));
    }
    else{
        auto codePtr = lookupId(std::string(node[AST_TAG_ID]->toString()));
        if(codePtr == nullptr){
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: identifier not found\n");
            exit(-1);            
        }
        code = *codePtr;
    }    
    Object *ast = nullptr;
    Value tmp = Value(Value::Type::NilType);
    try {
        if(!code.isObject())
            throw std::runtime_error("");
        auto originalAst = code.toObjectNoConst();
        TreeHost h;
        CopyTreeVisitor cpVis(originalAst);
        h.accept(&cpVis, *originalAst);
        ast = cpVis.getResult();
    }    
    catch (std::runtime_error &e) { //escaping some non-AST value
        ast = new Object();
        ast->set(AST_TAG_TYPE_KEY, AST_TAG_TERM);
        ast->set(AST_TAG_SUBTYPE_KEY, AST_TAG_VALUESTORAGE);
        ast->set(AST_TAG_LINE_KEY, Value(node[AST_TAG_LINE_KEY]->toNumber()));
        ast->set(AST_TAG_VALUE, code);
        tmp = Value(ast);
    }        
    insertAst(node, ast);      

    return Value(Value::Type::NilType);
}

const Value Interpreter::evalInline(Object& node){
    auto code = dispatcher->eval(*(node[AST_TAG_CHILD]->toObjectNoConst()));
    
    if (!(code.isObject())) {
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: inlined expression is not valid code\n");
        exit(-1);
    }   
    Object *ast = nullptr;
    try {
        auto originalAst = code.toObjectNoConst();
        TreeHost h;
        CopyTreeVisitor cpVis(originalAst);
        h.accept(&cpVis, *originalAst);
        ast = cpVis.getResult();
        TreeCorrectnessVisitor corVis;
        h.accept(&corVis, *ast);
    }    
    catch (std::runtime_error &e) { //inlining some non-AST value
        auto tmp = ("A++ runtime error: " + std::string(e.what()) + "\n");
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp.c_str());
        exit(1);
    }  

    auto newNode = insertAst(node, ast);
    ASTCreator::validateAST((*newNode)[PARENT_FIELD]->toObjectNoConst());
    return dispatcher->eval(*newNode);
}

const Value Interpreter::evalUnparsed(Object& node) {
    auto tmp = dispatcher->eval(*(node[AST_TAG_CHILD]->toObjectNoConst()));
    UnparseTreeVisitor unparsevis = UnparseTreeVisitor();
    TreeHost host = TreeHost();
    host.accept(&unparsevis, *(tmp.toObjectNoConst()));
    return Value((unparsevis.getSourceText()).c_str());
}

const Value Interpreter::evalCompiledString(Object& node) {
    auto code = dispatcher->eval(*(node[AST_TAG_CHILD]->toObjectNoConst()));
    if (!(code.isString())) {
        error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), "A++ Runtime Error: @ operator only works on strings\n");
        exit(-1);
    }
    std::string codeString = code.toString();
    std::istringstream codeStream = std::istringstream(codeString);
    if(std::all_of(codeString.begin(), codeString.end(), isspace)){
        return Value(new Object());
    }

    auto evalAst = ASTCreator::parseToAST(true, &codeStream);
    TreeHost h = TreeHost();
    SetParentTreeVisitor tempParentSetter(true);
    h.accept(&tempParentSetter, *evalAst);
   
    if((*evalAst)[AST_TAG_TYPE_KEY]->toString() == std::string(AST_TAG_EXPR)){
        auto newNode = new Object();
        newNode->set(AST_TAG_TYPE_KEY, AST_TAG_OBJELISTNOTEMPTY);
        newNode->set(AST_TAG_SUBTYPE_KEY, AST_TAG_OBJELISTNOTEMPTY);
        newNode->set(AST_TAG_LINE_KEY, *node[AST_TAG_LINE_KEY]);
        newNode->set(AST_TAG_NUMCHILDREN, (double)1);
        newNode->set((double)0, evalAst);
        evalAst->decRefCounter();
        assert(evalAst->getRefCounter() == 1);
        return Value(newNode);
    }
    Value retVal = Value(evalAst);
    evalAst->decRefCounter();
    assert(evalAst->getRefCounter() == 1);   
    return retVal;
}

void Interpreter::install() {
    //geomlyd evals
    dispatcher->install(AST_TAG_PROGRAM, [this](Object &node) { return evalProgram(node); });
    dispatcher->install(AST_TAG_STMTS, [this](Object &node) { return evalStmts(node); });
    dispatcher->install(AST_TAG_STMT, [this](Object &node) { return evalReduction(node); });
    dispatcher->install(AST_TAG_EXPR, [this](Object &node) { return evalReduction(node); });
    dispatcher->install(AST_TAG_ARITHEXPR, [this](Object &node) { return evalArithExpr(node); });
    dispatcher->install(AST_TAG_RELEXPR, [this](Object &node) { return evalRelExpr(node); });
    dispatcher->install(AST_TAG_BOOLEXPR, [this](Object &node) { return evalBoolExpr(node); });
    dispatcher->install(AST_TAG_TERM, [this](Object &node) { return evalReduction(node); });
    dispatcher->install(AST_TAG_TERM_PARENS_EXPR, [this](Object &node) { return evalTermParensExpr(node); });
    dispatcher->install(AST_TAG_TERM_MINUS_EXPR, [this](Object &node) { return evalTermMinusExpr(node); });
    dispatcher->install(AST_TAG_TERM_NOT_EXPR, [this](Object &node) { return evalTermNotExpr(node); });
    dispatcher->install(AST_TAG_TERM_PLUS_PLUS_LVALUE, [this](Object &node) { return evalTermPlusPlusLvalue(node); });
    dispatcher->install(AST_TAG_TERM_MINUS_MINUS_LVALUE, [this](Object &node) { return evalTermMinusMinusLvalue(node); });
    dispatcher->install(AST_TAG_TERM_LVALUE_PLUS_PLUS, [this](Object &node) { return evalTermLvaluePlusPlus(node); });
    dispatcher->install(AST_TAG_TERM_LVALUE_MINUS_MINUS, [this](Object &node) { return evalTermLvalueMinusMinus(node); });
    dispatcher->install(AST_TAG_ASSIGNEXPR, [this](Object &node) { return evalAssignExpr(node); });
    dispatcher->install(AST_TAG_PRIMARY, [this](Object &node) { return evalReduction(node); });

    //alivas evals
    dispatcher->install(AST_TAG_LVALUE_ID, [this](Object &node) { return evalLvalueId(node); });
    dispatcher->install(AST_TAG_LVALUE_GLOBAL_ID, [this](Object &node) { return evalLvalueGlobalId(node); });
    dispatcher->install(AST_TAG_LVALUE_LOCAL_ID, [this](Object &node) { return evalLvalueLocalId(node); });
    dispatcher->install(AST_TAG_LVALUE_MEMBER, [this](Object &node) { return evalLvalueMember(node); });
    dispatcher->install(AST_TAG_MEMBER_ID, [this](Object &node) { return evalMemberId(node); });
    dispatcher->install(AST_TAG_MEMBER_EXPR, [this](Object &node) { return evalMemberExpr(node); });
    dispatcher->install(AST_TAG_CALL, [this](Object &node) { return evalCall(node); });
    dispatcher->install(AST_TAG_MULTICALL, [this](Object &node) { return evalMultiCall(node); });
    dispatcher->install(AST_TAG_FDEFCALL, [this](Object &node) { return evalFdefCall(node); });
    dispatcher->install(AST_TAG_NORMCALLSUFFIX, [this](Object &node) { return evalNormCallSuffix(node); });
    dispatcher->install(AST_TAG_METHODCALLSUFFIX, [this](Object &node) { return evalMethodCallSuffix(node); });
    dispatcher->install(AST_TAG_NORMCALL, [this](Object &node) { return evalNormCall(node); });
    dispatcher->install(AST_TAG_METHODCALL, [this](Object &node) { return evalMethodCall(node); });
    dispatcher->install(AST_TAG_ELIST, [this](Object &node) { return evalElist(node); });
    dispatcher->install(AST_TAG_ELISTNOTEMPTY, [this](Object &node) { return evalElistNotEmpty(node); });
    dispatcher->install(AST_TAG_OBJECTDEF, [this](Object &node) { return evalObjectDef(node); });
    dispatcher->install(AST_TAG_OBJELISTNOTEMPTY, [this](Object &node) { return evalObjElistNotEmpty(node); });
    dispatcher->install(AST_TAG_CONT_LIST, [this](Object &node) { return evalObjectDinnerElistnotempty(node); });
    dispatcher->install(AST_TAG_CONT_INDEXED, [this](Object &node) { return evalObjectDinnerIndexed(node); });
    
    //manosgior evals
    dispatcher->install(AST_TAG_COMMAINDEXED, [this](Object &node) { return evalCommaIndexed(node); });
    dispatcher->install(AST_TAG_INDEXEDELEM, [this](Object &node) { return evalIndexedElem(node); });   
    dispatcher->install(AST_TAG_OBJECT_KEY, [this](Object &node) { return evalReduction(node); });
    dispatcher->install(AST_TAG_OBJECT_VALUE, [this](Object &node) { return evalReduction(node); });
    dispatcher->install(AST_TAG_BLOCK, [this](Object &node) { return evalBlock(node); });   
    dispatcher->install(AST_TAG_FUNCDEF, [this](Object &node) { return evalFuncDef(node); });
    dispatcher->install(AST_TAG_FUNCPREFIX, [this](Object &node) { return evalFuncPrefix(node); });
    dispatcher->install(AST_TAG_FUNCNAME_ID, [this](Object &node) { return evalFuncNameId(node); });    
    dispatcher->install(AST_TAG_CONST, [this](Object &node) { return evalConst(node); });
    dispatcher->install(AST_TAG_CONST_NUMCONST, [this](Object &node) { return evalConst(node); }); 
    dispatcher->install(AST_TAG_CONST_STRCONST, [this](Object &node) { return evalConst(node); });     
    dispatcher->install(AST_TAG_CONST_NIL, [this](Object &node) { return evalConst(node); });     
    dispatcher->install(AST_TAG_CONST_BOOLCONST, [this](Object &node) { return evalConst(node); });     
    dispatcher->install(AST_TAG_COMMAIDLIST, [this](Object &node) { return evalCommaIdList(node); });
    dispatcher->install(AST_TAG_IFPREFIX, [this](Object &node) { return evalIfPrefix(node); });   
    dispatcher->install(AST_TAG_IFSTMT, [this](Object &node) { return evalIfStmt(node); });  
    dispatcher->install(AST_TAG_IFSTMT_IFBODY, [this](Object &node) { return evalReduction(node); });  
    dispatcher->install(AST_TAG_IFSTMT_ELSEBODY, [this](Object &node) { return evalReduction(node); });  
    dispatcher->install(AST_TAG_WHILECOND, [this](Object &node) { return evalWhileCond(node); });
    dispatcher->install(AST_TAG_WHILESTMT, [this](Object &node) { return evalWhileStmt(node); });   
    dispatcher->install(AST_TAG_FORSTMT, [this](Object &node) { return evalForStmt(node); });
    dispatcher->install(AST_TAG_RETURNSTMT, [this](Object &node) { return evalReturnStmt(node); });
    dispatcher->install(AST_TAG_BREAKSTMT, [this](Object &node) { return evalBreak(node); });
    dispatcher->install(AST_TAG_CONTINUESTMT, [this](Object &node) { return evalContinue(node); });

    dispatcher->install(AST_TAG_VALUESTORAGE, [this](Object &node) {return evalValueStorage(node);});
    dispatcher->install(AST_TAG_QUASIQUOTES, [this](Object &node) {return evalQuasiQuotes(node);});
    dispatcher->install(AST_TAG_QUOTEDRULES, [this](Object &node) {return evalQuotedRules(node);});
    dispatcher->install(AST_TAG_INLINE, [this](Object &node){return evalInline(node);});
    dispatcher->install(AST_TAG_UNPARSED, [this](Object &node){return evalUnparsed(node);});
    dispatcher->install(AST_TAG_COMPILEDSTRING, [this](Object &node){return evalCompiledString(node);});
}

void Interpreter::installBinaryOpDispatcher(){
    binaryOpDispatcher["+"] = ( [](Value x, Value y)->Value {return x + y;} );
    binaryOpDispatcher["-"] = ( [](Value x, Value y)->Value {return x - y;} );
    binaryOpDispatcher["*"] = ( [](Value x, Value y)->Value {return x * y;} );
    binaryOpDispatcher["/"] = ( [](Value x, Value y)->Value {return x / y;} );
    binaryOpDispatcher["%"] = ( [](Value x, Value y)->Value {return x % y;} );

    binaryOpDispatcher[">"] = ( [](Value x, Value y)->Value {return x > y;} );
    binaryOpDispatcher[">="] = ( [](Value x, Value y)->Value {return x >= y;} );
    binaryOpDispatcher["<"] = ( [](Value x, Value y)->Value {return x < y;} );
    binaryOpDispatcher["<="] = ( [](Value x, Value y)->Value {return x <= y;} );
    binaryOpDispatcher["=="] = ( [](Value x, Value y)->Value {return x == y;} );
    binaryOpDispatcher["!="] = ( [](Value x, Value y)->Value {return x != y;} );  

    binaryOpDispatcher["and"] = ( [](Value x, Value y)->Value {return x && y;} ); 
    binaryOpDispatcher["or"] = ( [](Value x, Value y)->Value {return x || y;} );
}