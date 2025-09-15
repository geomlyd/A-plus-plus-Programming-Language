#include "DebugDispatcher.h"
#include <iostream>

DebugDispatcher::DebugDispatcher(DebuggerInputInterface *_inputController){
    pausableNodeTypes = {AST_TAG_STMT, AST_TAG_CALL};
    breakpoints = {};
    mode = NORMAL;
    skipCalls = false;
    newInlines = false;
    inputController = _inputController;
    stackTrace = std::vector<std::pair<unsigned, const Object*>>();
}

const Value DebugDispatcher::eval(Object &node){
    std::string nodeType = node[AST_TAG_TYPE_KEY]->toString();
    unsigned nodeLine = node[AST_TAG_LINE_KEY]->toNumber();
    currLine = nodeLine;
    Value ret = Value(Value::NilType);
    if(nodeType == AST_TAG_CALL)
        stackTrace.push_back(std::pair<unsigned, const Object *>(currLine, getTopEnvinroment()));
    if(nodeType == AST_TAG_INLINE)
        newInlines = true;

    if(pausableNodeTypes.find(nodeType) != pausableNodeTypes.end() && 
        (breakpoints.find(nodeLine) != breakpoints.end() || mode != NORMAL) && !skipCalls && (nodeType != AST_TAG_CALL || mode != NORMAL)){
        inputController->handleInput(this);
        if(mode == EARLY_EXIT){
            exit(0);
        }
        if(nodeType == AST_TAG_CALL && mode == STEP_OVER)
                skipCalls = true;
        ret = evals[node[AST_TAG_SUBTYPE_KEY]->toString()](node);
        skipCalls = false;
    }
    else
        ret =  evals[node[AST_TAG_SUBTYPE_KEY]->toString()](node);

    if(nodeType == AST_TAG_CALL)
        stackTrace.pop_back();        
    
    return ret;
}

void DebugDispatcher::addBreakpoint(unsigned lineNo){
    breakpoints.insert(lineNo);
}

void DebugDispatcher::removeBreakpoint(unsigned lineNo){
    breakpoints.erase(lineNo);
}

void DebugDispatcher::removeAllBreakpoints(){
    breakpoints.clear();
}

void DebugDispatcher::setExecutionMode(ExecutionModes m){
    mode = m;
}

DebugDispatcher::ExecutionModes DebugDispatcher::getExecutionMode(){
    return mode;
}

unsigned DebugDispatcher::getCurrLine(){
    return currLine;
}

void DebugDispatcher::setInterpreter(Interpreter *_i){
    i = _i;
}

const Value* DebugDispatcher::getVarByName(std::string id){
    return i->getVarByName(id);
}

const Value* DebugDispatcher::getGlobalVarByName(std::string id){
    return i->getGlobalVarByName(id);
}

const Value* DebugDispatcher::getLocalVarByName(std::string id){
    return i->getLocalVarByName(id);
}

const Object* DebugDispatcher::getTopEnvinroment(){
    return i->getTopEnvinroment();
}

const Object* DebugDispatcher::getGlobalEnvinroment(){
    return i->getGlobalEnvinroment();
}

const std::vector<std::pair<unsigned, const Object*>>& DebugDispatcher::getStackTrace(){
    return stackTrace;
}

bool DebugDispatcher::hasNewInlines(){
    return newInlines;
}

void DebugDispatcher::allInlinesProcessed(){
    newInlines = false;
}