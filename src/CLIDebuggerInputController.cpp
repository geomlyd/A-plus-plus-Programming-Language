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
    bool breakLoop = false;
    d->setExecutionMode(DebugDispatcher::ExecutionModes::PAUSED);
    while(!breakLoop){
        printf("Paused at line %d. Waiting for input...\n", d->getCurrLine());
        std::cin >> command;
        if(command == "c"){
            d->setExecutionMode(DebugDispatcher::ExecutionModes::NORMAL);
            breakLoop = true;
        }
        else if(command == "si"){
            d->setExecutionMode(DebugDispatcher::ExecutionModes::STEP_IN);
            breakLoop = true;
        }
        else if(command == "so"){
            d->setExecutionMode(DebugDispatcher::ExecutionModes::STEP_OVER);
            breakLoop = true;
        }
        else if(command == "sb"){
            unsigned lineNo = 0;
            while(lineNo == 0){
                printf("Enter a positive number to set a new breakpoint\n");
                std::cin >> lineNo;
            }
            d->addBreakpoint(lineNo);
        }
        else if(command == "rb"){
            unsigned lineNo = 0;
            while(lineNo == 0){
                printf("Enter a positive number to remove a breakpoint\n");
                std::cin >> lineNo;
            }
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
        else if(command == "help"){
            std::cout << ("Available commands:\n"
            "\tc - continue execution\n"
            "\tsi - step into next line\n"
            "\tso - step over next line\n"
            "\tsb <lineNumber> - set breakpoint at specified line\n"
            "\trb <lineNumber> - remove breakpoint at specified line\n"
            "\tpr <var_name> - print value of variable with name <var_name>\n"
            "\tst - print stack trace\n"
            "\tq - exit the debugger and terminate program execution\n"
            "\thelp - print this help message\n");
        }
        else if(command == "q"){
            d->setExecutionMode(DebugDispatcher::ExecutionModes::EARLY_EXIT);
            breakLoop = true;
        }
        else
            printf("Unknown command \"%s\"\n", command.c_str());
    }
}