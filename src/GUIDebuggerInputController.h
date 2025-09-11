#ifndef __GUIDEBUGGER_INPUT_CONTROLLER_H__
#define __GUIDEBUGGER_INPUT_CONTROLLER_H__

#include "DebuggerInputInterface.h"
#include "Interpreter.h"
#include "DebugDispatcher.h"
#include "ASTCreator.h"
#include <fstream>


class GUIDebuggerWindow;

class GUIDebuggerInputController : public DebuggerInputInterface{
private:
    bool inputEnabled, startupMode, refreshView;
    Interpreter *i;
    DebugDispatcher *d;
    Object *astRoot;
    GUIDebuggerWindow *win;
    std::string sourceCode;

    void onButtonClickContinue();
    void onButtonClickStepOver();
    void onButtonClickStepIn();
    void onButtonClickSetBreakpoint();
    void onButtonClickRemoveBreakpoint();
    void onButtonClickClearAllBreakpoints();
    void onTreeViewCallStackClick(int index);
    void addObjectFieldToView(const Value &name, const Value *val);

    bool onIdleView();
public:
    GUIDebuggerInputController();
    void launchGUI(std::ifstream *inputFile, Interpreter *_i, DebugDispatcher *_d, Object *_astRoot);
    virtual void setInitialBreakpoints(DebugDispatcher *d) override;
    virtual void handleInput(DebugDispatcher *d) override;
};

#endif