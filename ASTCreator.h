#ifndef __AST_CREATOR_H__
#define __AST_CREATOR_H__
#include "Object.h"
#include "Interpreter.h"

class ASTCreator{
private:
    static Interpreter *usedInterp;
    static Object *parentAST;

public:
    static Object *parseToAST(bool _useForEval = false, std::istream *in = nullptr, std::ostream *out = nullptr);
    static void setInterpreterToUse(Interpreter *i);
    static void setOptionalParent(Object *ast);
    static Object *getOptionalParent();
    static void validateAST(Object *ast);
    static const Value interpretAST(Object *ast);
    static void destroyAST(Object *ast);
};

#endif