#ifndef OBJECT_H
#define OBJECT_H

#include <functional>
#include <map>
#include <vector>
#include "Value.h"

class Object {
    private:
    unsigned refCounter;
    std::map<const std::string, Value*> stringToValue;
    std::map<double, Value*> doubleToValue;
    void swap(Object&);
    void clear();

    public:
    Object();
    //rule of five
    Object(const Object& other);
    Object& operator=(const Object& other);
    ~Object();
    Object(Object&&);
    Object& operator=(Object&&);

    using Applier = std::function<void(const Value& key, Value* val)>;
    using Visitor = std::function<void(const Value& key, const Value* val)>;

    void            incRefCounter();
    void            decRefCounter();
    unsigned        getRefCounter() const;
    Value*          operator[](const std::string& key) const; //null = not found
    Value*          operator[](double key) const; // null = not found
    Value*          operator[](const Value* key) const; // null = not found
    Value           getAndRemove(const std::string& key);
    Value           getAndRemove(double key);
    void            set(const std::string& key, const Value& value);
    void            set(double key, const Value& value);
    void            set(const Value* key, const Value& value);
    void            remove(const std::string& key);
    void            remove(double key);
    void            remove(const Value* key);
    std::string     toString() const;

    unsigned        getTotal() const;   
    void            apply(const Applier& f); //RW access
    void            visit(const Visitor& f) const; //RO access
};

#endif