#include "CLIDebuggerInputController.h"
#include "DebugDispatcher.h"
#include <iostream>

void CLIDebuggerInputController::setInitialBreakpoints(DebugDispatcher *d){
    while(true){
        printf("Enter a positive number to set a new breakpoint, 0 or negative to continue\n");
        int n = 0;
        std::cin >> n;
        if(n > 0)
            d->addBreakpoint(n);
        else
            break;
    }
}

void CLIDebuggerInputController::handleInput(DebugDispatcher *d){
    std::string command;
    printf("Paused at line %d. Waiting for input...\n", d->getCurrLine());
    std::cin >> command;
    if(command == "c")
        d->setExecutionMode(DebugDispatcher::ExecutionModes::NORMAL);
    else if(command == "si")
        d->setExecutionMode(DebugDispatcher::ExecutionModes::STEP_IN);
    else if(command == "so")
        d->setExecutionMode(DebugDispatcher::ExecutionModes::STEP_OVER);
    else if(command == "sb"){
        unsigned lineNo;
        std::cin >> lineNo;
        d->addBreakpoint(lineNo);
    }
    else if(command == "rb"){
        unsigned lineNo;
        std::cin >> lineNo;
        d->removeBreakpoint(lineNo);        
    }
    else if(command == "pr"){
        std::string varName;
        std::cin >> varName;
        const Value *var = d->getVarByName(varName);
        if(var != nullptr)
            std::cout<<var->makeString()<<"\n";
        else
            std::cout<<"Variable not found\n";
    }
    else if(command == "st"){
        auto stackTrace = d->getStackTrace();
        for(unsigned i = 0; i < stackTrace.size(); i++)
            printf("%d->", stackTrace[i].first);
        printf("%d\n", d->getCurrLine());
    }
    else
        printf("Unknown command \"%s\"\n", command.c_str());
}