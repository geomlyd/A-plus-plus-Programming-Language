#include "GUIDebuggerInputController.h"
#include "GUIDebuggerWindow.h"
#include <iostream>
#include <thread>
#include <glibmm/main.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treestore.h>
#include "error_handler.h"
#include "TreeHost.h"
#include <locale.h>

void GUIDebuggerInputController::onButtonClickContinue(){
    if(inputEnabled || startupMode){
        d->setExecutionMode(DebugDispatcher::ExecutionModes::NORMAL);
        inputEnabled = false;
        if(startupMode){
            startupMode = false;

            auto tmp = new std::thread([this]{

                std::setlocale(LC_NUMERIC, "en_US.utf8");
                ASTCreator::setInterpreterToUse(i);
                ASTCreator::interpretAST(astRoot);
                ASTCreator::destroyAST(astRoot);
                error_handler_destroy();
                std::cout<<"------------Program execution finished------------\n";
            });            
        }
    }
}

void GUIDebuggerInputController::onButtonClickStepOver(){
    if(inputEnabled){
        d->setExecutionMode(DebugDispatcher::ExecutionModes::STEP_OVER);
        inputEnabled = false;
    }
}

void GUIDebuggerInputController::onButtonClickStepIn(){
    if(inputEnabled){
        d->setExecutionMode(DebugDispatcher::ExecutionModes::STEP_IN);
        inputEnabled = false;
    }
}

void GUIDebuggerInputController::onButtonClickSetBreakpoint(){
    int lineNo = win->getBreakPointValueFromEntry();
    if(lineNo != 0){
        d->addBreakpoint(lineNo);
        win->brlines.insert(lineNo);
        win->updateBuffer(-1, 0);
    }
}

void GUIDebuggerInputController::onButtonClickRemoveBreakpoint(){
    int lineNo = win->getBreakPointValueFromEntry();
    if(lineNo != 0){
        d->removeBreakpoint(lineNo);    
        win->brlines.erase(lineNo);
        win->updateBuffer(-1, 0);
    }
}

void GUIDebuggerInputController::onTreeViewCallStackClick(int index) {   
    if(inputEnabled){
        win->clearVariables();
        auto currEnv = (index == 0) ? (d->getTopEnvinroment()) : (d->getStackTrace()[index - 1].second);
        currEnv->visit([this] (const Value& key, const Value *val){
            if(!val->isObject())
                win->addVariableRow(key.makeString(), val->makeString());
            else {
                win->addVariableRow(key.makeString(), "Object");
                val->toObject()->visit([this](const Value &objKey, const Value *objVal){
                    addObjectFieldToView(objKey, objVal);
                });
            }
        });
    }
}

void GUIDebuggerInputController::onButtonClickClearAllBreakpoints(){
    if(inputEnabled || startupMode){
        d->removeAllBreakpoints();
        win->brlines.clear();
        win->updateBuffer(-1, 0);
    }
}

bool GUIDebuggerInputController::onIdleView(){
    if(refreshView){
        win->clearVariables();
        win->updateBuffer(d->getCurrLine(), 0);
        auto callStack = d->getStackTrace();
        std::vector<int> calledFuncs = {(int)d->getCurrLine()};
        for(unsigned j = 0; j < callStack.size(); j++){
            if(callStack[j].second != d->getTopEnvinroment())
                calledFuncs.push_back(callStack[j].first);
        }
        win->updateCallStack(calledFuncs);
        auto currEnv = d->getTopEnvinroment();
        currEnv->visit([this] (const Value& key, const Value *val){
            if(!val->isObject())
                win->addVariableRow(key.makeString(), val->makeString());
            else {
                win->addVariableRow(key.makeString(), "Object");
                val->toObject()->visit([this](const Value &objKey, const Value *objVal){
                    addObjectFieldToView(objKey, objVal);
                });            
            }
        });
        if(d->hasNewInlines()){
            d->allInlinesProcessed();
            UnparseTreeVisitor unparsevis = UnparseTreeVisitor();
            TreeHost host = TreeHost();
            host.accept(&unparsevis, *astRoot);
            win->fillBuffer(unparsevis.getSourceText(), 1);
            //update the view to show unparsed code
        }
        refreshView = false;
    }
    return true;
}

GUIDebuggerInputController::GUIDebuggerInputController(){
    inputEnabled = false;
    startupMode = true;
}

void GUIDebuggerInputController::launchGUI(std::ifstream *inputFile, Interpreter *_i, DebugDispatcher *_d, Object *_astRoot) {
    i = _i;
    d = _d;
    astRoot = _astRoot;
    int argc = 0;
    char **argv = nullptr;
    auto app = Gtk::Application::create(argc, argv, "org.alpha_plus_plus.debugger");    
    win = new GUIDebuggerWindow();
    win->continueButton.signal_clicked().connect(sigc::mem_fun(this, &GUIDebuggerInputController::onButtonClickContinue));
    win->stepOverButton.signal_clicked().connect(sigc::mem_fun(this, &GUIDebuggerInputController::onButtonClickStepOver));
    win->stepInButton.signal_clicked().connect(sigc::mem_fun(this, &GUIDebuggerInputController::onButtonClickStepIn));
    win->addBreakPointButton.signal_clicked().connect(sigc::mem_fun(this, &GUIDebuggerInputController::onButtonClickSetBreakpoint));
    win->removeBreakPointButton.signal_clicked().connect(sigc::mem_fun(this, &GUIDebuggerInputController::onButtonClickRemoveBreakpoint));
    win->clearAllBreakpointsButton.signal_clicked().connect(sigc::mem_fun(this, &GUIDebuggerInputController::onButtonClickClearAllBreakpoints));
    Glib::signal_idle().connect(sigc::mem_fun(this, &GUIDebuggerInputController::onIdleView));
    win->callStackView.signal_row_activated().connect([this](const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* c){
        int res = win->getCallIndex(path, c);
        onTreeViewCallStackClick(res);              
    });

    inputFile->seekg(0, std::ios::beg);
    std::stringstream sourceText;
    std::string sourceCode, line;
    while (getline(*inputFile, line)) 
        sourceText << line << std::endl;
    sourceCode = sourceText.str();
    win->fillBuffer(sourceCode, 0);
    refreshView = false;
    app->run(*win);
}

void GUIDebuggerInputController::setInitialBreakpoints(DebugDispatcher *d){

}

void GUIDebuggerInputController::addObjectFieldToView(const Value &name, const Value *val){
    if(!val->isObject()) {
        win->addVariableChildRow(name.makeString(), val->makeString());
        win->popOut();
    }
    else{
        win->addVariableChildRow(name.makeString(), "Object");
        val->toObject()->visit([this] (const Value& key, const Value *objVal){
            addObjectFieldToView(key, objVal);
        });
        win->popOut();
    }    
}

void GUIDebuggerInputController::handleInput(DebugDispatcher *d){
    inputEnabled = true;
    refreshView = true;
}