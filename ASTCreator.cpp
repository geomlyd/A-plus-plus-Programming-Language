#include "ASTCreator.h"
#include "alpha_yyFlexLexer.h"
#include "alpha_parser.hpp"
#include "TreeHost.h"
#include "SetParentTreeVisitor.h"
#include "ControlFlowVisitor.h"

alpha_yyFlexLexer * lexer = nullptr;
extern Object* __astRoot;
extern bool errorExists;

Interpreter *ASTCreator::usedInterp = nullptr;
Object *ASTCreator::parentAST = nullptr;

Object *ASTCreator::parseToAST(bool useForEval, std::istream *in , std::ostream *out) {
    auto oldLexer = lexer;
    if(out != nullptr)
        lexer = new alpha_yyFlexLexer(in, out, useForEval);
    else if(in != nullptr)
        lexer = new alpha_yyFlexLexer(in, 0, useForEval);
    else
        lexer = new alpha_yyFlexLexer(0, 0, useForEval);
    auto *oldAst = __astRoot;
    auto oldErrorStatus = errorExists;
    __astRoot = nullptr;
    //lexer->yypush_buffer_state()
    yyparse();
    delete lexer;
    if (!errorExists) {
        TreeHost host = TreeHost();
        SetParentTreeVisitor setparvis(false);
        host.accept(&setparvis, *__astRoot);
    }
    else {
        exit(-1);
    }
    auto retTree = __astRoot;
    retTree->incRefCounter(); //because no child pointers point to root node, this is necessary
    __astRoot = oldAst;
    errorExists = oldErrorStatus;
    lexer = oldLexer;
    return retTree;
}

void ASTCreator::validateAST(Object *ast){
    TreeHost host = TreeHost();
    ControlFlowVisitor controflowvis = ControlFlowVisitor();
    host.accept(&controflowvis, *ast);
}

void ASTCreator::setInterpreterToUse(Interpreter *i){
    usedInterp = i;
}

const Value ASTCreator::interpretAST(Object *ast){
    assert(usedInterp != nullptr);
    return usedInterp->interpret(*ast);
}

void ASTCreator::destroyAST(Object *ast){
    TreeHost host = TreeHost();
    SetParentTreeVisitor setparvis(true);
    host.accept(&setparvis, *ast);
    assert(ast->getRefCounter() == 1);
    ast->decRefCounter();
    delete ast;
}

void ASTCreator::setOptionalParent(Object *ast){
    parentAST = ast;
}

Object *ASTCreator::getOptionalParent(){
    return parentAST;
}