#ifndef __DEBUG_DISPATCHER_H__
#define __DEBUG_DISPATCHER_H__

#include "EvalDispatcher.h"
#include <set>
#include <mutex>
#include <condition_variable>
#include "TreeTags.h"
#include "DebuggerInputInterface.h"
#include "Interpreter.h"


class DebugDispatcher : public EvalDispatcher {
public:
    enum ExecutionModes{
        NORMAL = 0, PAUSED, STEP_OVER, STEP_IN
    };
private:
    std::set<std::string> pausableNodeTypes;
    std::set<unsigned> breakpoints;

    ExecutionModes mode;
    std::mutex mode_mutex;
    std::condition_variable mode_is_not_paused;    

    DebuggerInputInterface *inputController;
    bool skipCalls, newInlines;
    std::vector<std::pair<unsigned, const Object*>> stackTrace;
    unsigned currLine;
    Interpreter *i;

public:
    DebugDispatcher(DebuggerInputInterface *_inputController);
    virtual const Value eval (Object& node) override;

    void addBreakpoint(unsigned lineNo);
    void removeBreakpoint(unsigned lineNo);
    void removeAllBreakpoints();
    void setExecutionMode(ExecutionModes m);
    unsigned getCurrLine();
    void setInterpreter(Interpreter *_i);
   
    const Value*  getVarByName(std::string id);
    const Value*  getGlobalVarByName(std::string id);
    const Value*  getLocalVarByName(std::string id); 
    const Object* getTopEnvinroment();
    const Object* getGlobalEnvinroment();    
    const std::vector<std::pair<unsigned, const Object*>> &getStackTrace();
    bool hasNewInlines();
    void allInlinesProcessed();
};

#endif