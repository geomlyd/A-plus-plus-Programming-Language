#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "EvalDispatcher.h"
#include "UnparseTreeVisitor.h"
#include "ValueStack.h"
#include <set>

//todo header
void libfuncPrint(Object& args);
void libfuncTypeOf(Object& args);
void libfuncObjectKeys(Object& args);
void libfuncObjectSize(Object &args);
void libfuncInput(Object &args);
void libfuncStrToNum(Object &args);
void libfuncSqrt(Object& args);
void libfuncCos(Object& args);
void libfuncSin(Object& args);
void libfuncTotalArguments(Object& args);
void libfuncGetArgument(Object& args);
void libfuncObjectCopy(Object& args);
void libfuncFileOpen(Object& args);
void libfuncFileClose(Object& args);
void libfuncFileGetLine(Object& args);
void libfuncFileGetWord(Object& args);
void libfuncFileRead(Object& args);
void libfuncEval(Object& args);
void libfuncFloor(Object& args);
void libfuncCeiling(Object& args);
void libfuncExit(Object& args);

class Interpreter {
private:
    EvalDispatcher *dispatcher;
    ValueStack envs;
    Object *globalScope;
    bool noScope;
    Value *valRegister;
    Value retVal;
    Value objField;
    unsigned currLineNo;
    Value* currentFunction;
    Object* currFuncArgsEnv;
    int currentFuncNumArgs;
    std::set<std::string> validDollarFields;
    std::set<std::string> validDollarIdents;

    std::map<std::string, std::function<Value(Value, Value)>> binaryOpDispatcher;

    void    pushScopeSpace(Object* scope);
    void    popScopeSpace();
    void    pushNested();
    void    pushSlice();


    Value*  lookupId(std::string id);
    Value*  lookupGlobalId(std::string id);
    Value*  lookupIdCurrEnvOnly(std::string id); 
    Value*  declareId(std::string id);
    void    tmpFunc();
    void    forceClosureClear(Object&);

    const Value* getArgument(Object& env, unsigned argNo, const std::string& optArgName);

    const Value evalReduction(Object& node);
    const Value evalBinaryOp(const Value leftOp, const Value rightOp, std::string op);

    const Value evalProgram(Object& node);
    const Value evalStmts(Object& node);

    const Value evalArithExpr(Object& node);
    const Value evalRelExpr(Object& node);
    const Value evalBoolExpr(Object& node); 

    const Value evalTermParensExpr(Object& node);
    const Value evalTermMinusExpr(Object& node);
    const Value evalTermNotExpr(Object& node);

    void        indexValRegIfTableOrFunc();

    const Value evalTermPlusPlusLvalue(Object& node);
    const Value evalTermMinusMinusLvalue(Object& node);
    const Value evalTermLvaluePlusPlus(Object& node);
    const Value evalTermLvalueMinusMinus(Object& node);

    const Value evalAssignExpr(Object& node);
    const Value evalLvalueId(Object& node);
    const Value evalLvalueGlobalId(Object& node);
    const Value evalLvalueLocalId(Object& node);
    const Value evalLvalueMember(Object& node);
    const Value fieldAccess(const Value caller, const Value* id, double lineNo);
    const Value evalMemberId(Object& node);
    const Value evalMemberExpr(Object& node);
    Value makeCallFromObject(const Value* calledFunc, const Value callsuffix, double lineNo);
    Value makeCallFromLibFunc(const Value* calledFunc, const Value callsuffix, double lineNo);
    Value makeCallFromProgFunc(const Value* calledFunc, const Value callsuffix, double lineNo);
    const Value makeCall(const Value*, const Value, double lineNo);
    const Value evalCall(Object& node);
    const Value evalMultiCall(Object& node);
    const Value evalFdefCall(Object& node);
    const Value evalNormCallSuffix(Object& node);
    const Value evalMethodCallSuffix(Object& node);
    const Value evalNormCall(Object& node);
    const Value evalMethodCall(Object& node);
    const Value evalElist(Object& node);
    const Value evalElistNotEmpty(Object& node);
    const Value evalObjElistNotEmpty(Object& node);
    const Value evalObjectDef(Object& node);
    const Value evalObjectDinnerElistnotempty(Object& node);
    const Value evalObjectDinnerIndexed(Object& node);

    const Value evalIndexed(Object& node);
    const Value evalCommaIndexed(Object& node);
    const Value evalIndexedElem(Object& node);   
    const Value evalBlock(Object& node);
    const Value evalFuncDef(Object& node);
    const Value evalFuncPrefix(Object& node);
    const Value evalFuncNameId(Object& node);   
    const Value evalConst(Object& node);
    const Value evalCommaIdList(Object& node);
    const Value evalIfPrefix(Object& node);   
    const Value evalIfStmt(Object& node);  
    const Value evalWhileCond(Object& node);
    const Value evalWhileStmt(Object& node);   
    const Value evalForStmt(Object& node);
    const Value evalReturnStmt(Object& node);
    const Value evalBreak(Object& node);
    const Value evalContinue(Object& node);

    int stealManyChildren(Object *insertionPoint, Object *stealPoint, Object *stealAncestor);
    Object *insertStmtsAst(Object *node, Object *stmtsRoot);
    Object *insertExprAst(Object *node, Object *exprRoot);
    Object *insertExprListAst(Object *node, Object *elistRoot);
    Object *insertAst(Object& node, Object *ast);

    const Value evalValueStorage(Object& node);
    const Value evalQuasiQuotes(Object& node);
    const Value evalQuotedRules(Object& node);
    const Value evalEscape(Object& node);
    const Value evalInline(Object& node);
    const Value evalUnparsed(Object& node);
    const Value evalCompiledString(Object& node);
    
    void install();
    void installBinaryOpDispatcher();

public:
    const Value interpret(Object& node);
    Interpreter(EvalDispatcher *d);
    ~Interpreter();
   
    const Value*  getVarByName(std::string id);
    const Value*  getGlobalVarByName(std::string id);
    const Value*  getLocalVarByName(std::string id); 
    const Object* getTopEnvinroment();
    const Object* getGlobalEnvinroment();
};

#endif