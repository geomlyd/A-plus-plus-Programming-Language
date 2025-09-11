#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "function_actions.h"
#include "alpha_parser.hpp"
#include "error_handler.h"
#include "TreeHost.h"
#include "UnparseTreeVisitor.h"
#include "GraphTreeVisitor.h"
#include "Interpreter.h"
#include "DebugDispatcher.h"
#include "ASTCreator.h"
#include "CLIDebuggerInputController.h"
#define BON "\e[1m"
#define BOFF "\e[0m"
//#define PHASE1

extern bool errorExists;

int main(int argc, char** argv) {
    std::ifstream ifs;
    std::ofstream ofs; 
    Object *astRoot = nullptr;
    if (argc > 1) {
        error_handler_init(argv[1]);
        ifs.open(argv[1],  std::ios::in);
        if (!ifs.is_open()) {
            //fprintf(stderr, "Unable to open input file \n");
            error(ErrorType::FatalError, 0, "Unable to open input file " BON "\'%s\'" BOFF "\n", argv[1]);
            return 1;
        }
        if (argc > 2) {
            ofs.open(argv[2], std::ios::out);
            if (!ofs.is_open()) {
                //fprintf(stderr, "Unable to open output file\n");
                error(ErrorType::FatalError, 0, "Unable to open output file " BON "\'%s\'" BOFF "\n", argv[2]);
                return 2;
            }
            astRoot = ASTCreator::parseToAST(false, &ifs, &ofs);
        } else { 
            astRoot = ASTCreator::parseToAST(false, &ifs);
        }
    } else {
        const char * dfname = "stdin";
        error_handler_init(dfname);
        astRoot = ASTCreator::parseToAST(false);
    }
    if (!errorExists) {
        /*
        UnparseTreeVisitor unparsevis = UnparseTreeVisitor();
        GraphTreeVisitor graphvis = GraphTreeVisitor();
        TreeHost host = TreeHost();
        host.accept(&unparsevis, *astRoot);
        host.accept(&graphvis, *astRoot);
        if (argc > 2) {
            std::ofstream ofs1;
            std::ofstream ofs2;
            ofs1.open(std::string(argv[2]) + "_unparse.txt", std::ios::out);
            ofs2.open(std::string(argv[2]) + "_graph.txt", std::ios::out);
            ofs1 << unparsevis.getSourceText() << std::endl;
            ofs2 << graphvis.getGraph() << std::endl;
        } else {
            std::cout << unparsevis.getSourceText() << std::endl;
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << graphvis.getGraph() << std::endl;
        }       
        */ 
        ASTCreator::validateAST(astRoot);
        CLIDebuggerInputController dbg;
        DebugDispatcher d(&dbg);
        Interpreter appInterpreter(&d);
        d.setInterpreter(&appInterpreter);
        dbg.setInitialBreakpoints(&d);
        ASTCreator::setInterpreterToUse(&appInterpreter);
        ASTCreator::interpretAST(astRoot);
        ASTCreator::destroyAST(astRoot);
        error_handler_destroy();
    }
    ifs.close();
    ofs.close();
    return 0;
}