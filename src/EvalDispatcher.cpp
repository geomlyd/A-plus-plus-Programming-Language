#include "EvalDispatcher.h"

void EvalDispatcher::install(const std::string& tag, const F& f) { 
    evals[tag] = f; 
}

const Value EvalDispatcher::eval(Object& node) {
    return evals[node[AST_TAG_SUBTYPE_KEY]->toString()](node);
}