#ifndef EVAL_DISPATCHER
#define EVAL_DISPATCHER

#include <functional>
#include <map>
#include "Value.h"
#include "Object.h"
#include "TreeTags.h"


class EvalDispatcher {
public:
    using F = std::function<const Value(Object&)>;

protected:
    std::map<std::string, F> evals;

public:
    void install(const std::string& tag, const F& f);
    virtual const Value eval (Object& node);
    EvalDispatcher() = default;
    EvalDispatcher(const EvalDispatcher&) = delete;
    EvalDispatcher(EvalDispatcher&&) = delete;
    virtual ~EvalDispatcher(){};
};

#endif