#ifndef __CLIDEBUGGER_INPUT_CONTROLLER_H__
#define __CLIDEBUGGER_INPUT_CONTROLLER_H__

#include "DebuggerInputInterface.h"

class CLIDebuggerInputController : public DebuggerInputInterface{
public:
    virtual void setInitialBreakpoints(DebugDispatcher *d) override;
    virtual void handleInput(DebugDispatcher *d) override;
};

#endif