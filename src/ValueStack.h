#ifndef VALUE_STACK
#define VALUE_STACK

#include <list>
#include <assert.h>
#include "Value.h"

class ValueStack {

    protected:
    std::list<Value> valueStack;

    public:
    bool            isEmpty() const     {return valueStack.empty();}
    void            clear()             {valueStack.clear();}
    void            push(const Value& v){valueStack.push_front(v);}
    void            pop() {assert(!isEmpty()); valueStack.pop_front();}
    int             size(){return valueStack.size();}
    const Value&    top() const {assert(!isEmpty()); return valueStack.front();}
    unsigned        size() const {return valueStack.size();}
    const Value    getTopAndPop() {
        assert(!isEmpty());
        auto v = valueStack.front();
        valueStack.pop_front();
        return v;
    }

    ValueStack() = default;
    ValueStack(const ValueStack&) = delete;
    ValueStack(ValueStack&&) = delete;
};

#endif