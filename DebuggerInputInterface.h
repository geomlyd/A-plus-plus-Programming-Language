#ifndef __DEBUGGER_INPUT_INTERFACE_H__
#define __DEBUGGER_INPUT_INTERFACE_H__


class DebugDispatcher;

class DebuggerInputInterface{
public:
    virtual void setInitialBreakpoints(DebugDispatcher *d) = 0;
    virtual void handleInput(DebugDispatcher *d) = 0;
};

#endif