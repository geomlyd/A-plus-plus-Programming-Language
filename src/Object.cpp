#include "Object.h"
#include "Value.h"
#include <string>
#include <iostream>
#include <assert.h>

void Object::swap(Object& other){
    auto tmpCounter = other.refCounter;
    other.refCounter = this->refCounter;
    this->refCounter = tmpCounter;

    auto tmpMapStr = other.stringToValue;
    other.stringToValue = this->stringToValue;
    this->stringToValue = tmpMapStr;

    auto tmpMapDouble = other.doubleToValue;
    other.doubleToValue = this->doubleToValue;
    this->doubleToValue = tmpMapDouble;
}

void Object::clear(){
    assert(refCounter == 0);
    for(auto it : stringToValue){
        delete it.second;
    }
    for(auto it : doubleToValue){
        delete it.second;
    }
}

Object::Object() {
    refCounter = 0;
    stringToValue = std::map<const std::string, Value*>();
    doubleToValue = std::map<double, Value*>();
}

Object::Object(const Object& other) {
    refCounter = 0;
    for(auto it : other.stringToValue){
        stringToValue[it.first] = it.second->clone();
    }
    for(auto it : other.doubleToValue){
        doubleToValue[it.first] = it.second->clone();
    }
}

Object::~Object() {
    assert(refCounter == 0);
    clear();
}

Object::Object(Object &&other){
    refCounter = other.refCounter;
    stringToValue = other.stringToValue;
    doubleToValue = other.doubleToValue;
    other.refCounter = 0;
    other.stringToValue = std::map<const std::string, Value*>();
    other.doubleToValue = std::map<double, Value*>();
}

Object& Object::operator=(const Object& other){
    Object tmp(other);
    swap(tmp); //copy and swap idiom
    return *this;
}

Object& Object::operator=(Object&& other){
    if(this->refCounter == 0)
        clear();
    refCounter = other.refCounter;
    stringToValue = other.stringToValue;
    doubleToValue = other.doubleToValue;
    other.refCounter = 0;
    other.stringToValue = std::map<const std::string, Value*>();
    other.doubleToValue = std::map<double, Value*>();    
    return *this;
}

void Object::incRefCounter() {
    refCounter++;
}

void Object::decRefCounter() {
    assert(refCounter > 0);
    refCounter--;
}

unsigned Object::getRefCounter() const {
    return refCounter;
}

Value* Object::operator[](const std::string& key) const {
    auto s2v = stringToValue.find(key);
    if (s2v == stringToValue.end()) {
        return nullptr;
    }
    return s2v->second;
}

Value* Object::operator[](double key) const {
    auto d2v = doubleToValue.find(key);
    if (d2v == doubleToValue.end()) {
        return nullptr;
    }
    return d2v->second;
}

Value* Object::operator[](const Value* key) const {
    if (key->isNumber()) 
        return operator[](key->toNumber());
    else if (key->isString()) 
        return operator[](key->toString());
    assert(false);
}

Value Object::getAndRemove(const std::string& key) {
    auto tmp = stringToValue.find(key);
    if(tmp == stringToValue.end())
        return Value(Value::Type::NilType);
    auto retVal = *tmp->second;
    delete tmp->second;
    stringToValue.erase(key);    
    return retVal;
}

Value Object::getAndRemove(double key) {
    auto tmp = doubleToValue.find(key);
    if(tmp == doubleToValue.end())
        return Value(Value::Type::NilType);    
    auto retVal = *tmp->second;
    delete tmp->second;
    doubleToValue.erase(key);   
    return retVal;
}

void Object::set(const std::string& key, const Value& value) {
    if(stringToValue.find(key) != stringToValue.end())
        delete stringToValue[key];
    stringToValue[key] = value.clone();
}

void Object::set(double key, const Value& value) {
    if(doubleToValue.find(key) != doubleToValue.end())
        delete doubleToValue[key];
    doubleToValue[key] = value.clone();
}

void Object::set(const Value* key, const Value& value) {
    if (key->isNumber())
        set(key->toNumber(), value);
    else if (key->isString())
        set(key->toString(), value);
    else 
        assert(false);    
}

void Object::remove(const std::string& key) {
    getAndRemove(key);
}

void Object::remove(double key) {
    getAndRemove(key);
}

void Object::remove(const Value* key){
    assert(key->isNumber() || key->isString());
    (key->isString())?remove(std::string(key->toString())):remove(key->toNumber());
}

unsigned Object::getTotal() const {
    return stringToValue.size() + doubleToValue.size();
}

void Object::apply(const Applier& f) {
    for (std::pair<const std::string, Value*> e : stringToValue) {
        f(Value((e.first).c_str()), e.second);
    }
    for (std::pair<double, Value*> e : doubleToValue) {
        f(Value(e.first), e.second);
    }
}

void Object::visit(const Visitor& f) const {
for (std::pair<const std::string, Value*> e : stringToValue) {
        f(Value((e.first).c_str()), e.second);
    }
    for (std::pair<double, Value*> e : doubleToValue) {
        f(Value(e.first), e.second);
    } 
}

std::string Object::toString() const {
    std::string toReturn = "[";	
    std::string tmp;

    bool flag = true;
    bool isArray = true;

    if (stringToValue.size() == 0) {
        double counter = 0.0;
        for (std::pair<double, Value*> e : doubleToValue) {
            if (e.first != counter++)
                isArray = false;
        }
    }        

    for (std::pair<const std::string, Value*> e : stringToValue) { 
        if (!flag)
            toReturn += ", ";		
		toReturn += " {\"" + e.first + "\" : " + e.second->makeString() + "}";
		flag = false;
	}
    
    for (std::pair<double, Value*> e : doubleToValue) { 
        if (!flag)
            toReturn += ", ";

        if (isArray)
            toReturn +=  e.second->makeString();
        else		
		    toReturn += " {" + std::to_string(e.first) +  " : " + e.second->makeString() + "}";
		flag = false;
	}
    toReturn += " ]";

    return toReturn;
}