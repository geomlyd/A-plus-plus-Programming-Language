#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Value.h"
#include "Object.h"

using Type = Value::Type;
bool Value::isUndef() const {
    return Value::type == Type::UndefType;
}

bool Value::isNumber() const {
    return Value::type == Type::NumberType;
}

bool Value::isBoolean() const {
    return Value::type == Type::BooleanType;
}

bool Value::isString() const {
    return Value::type == Type::StringType;
}

bool Value::isObject() const {
    return Value::type == Type::ObjectType;
}

bool Value::isProgramFunction() const {
    return Value::type == Type::ProgramFunctionType;
}
 
bool Value::isLibraryFunction() const {
    return Value::type == Type::LibraryFunctionType;
}
 
bool Value::isNativePtr() const {
    return Value::type == Type::NativePtrType;
}

bool Value::isNil() const {
    return Value::type == Type::NilType;
}

void Value::fromNil () {
	clear();
	type = Type::NilType;
}

void Value::fromDouble (double _numVal) {
	clear();
	type = Type::NumberType;
    data.numVal = _numVal;
}

void Value::fromBool (bool _boolVal) {
	clear();
	type = Type::BooleanType;
    data.boolVal = _boolVal;
}

void Value::fromString (const char *_strVal) {
	clear();
	type = Type::StringType;
    data.strVal = strdup(_strVal);
}

void Value::fromLibraryFunction (LibraryFunction ast, char *name) {
	clear();
	type = Type::LibraryFunctionType;
    data.libFuncVal.ast = ast;
    data.libFuncVal.libFuncName = strdup(name);
}

void Value::fromObject (Object* _objectVal) {
	clear();
	data.objectVal = _objectVal;
    _objectVal->incRefCounter();
}

void Value::fromProgramFunction (Object* _funcAst, Object* _funcClosure, const char *name) {
	clear();	
	
	type = Type::ProgramFunctionType;
	
    data.progFuncVal.ast = _funcAst;    
    _funcAst->incRefCounter();
	
	data.progFuncVal.closure = _funcClosure;    
    _funcClosure->incRefCounter();
    
    data.progFuncVal.funcName = strdup(name);
}

void Value::fromNativePtr (void* _ptr, char* _typeId) {	
	clear();
	
	type = Type::NativePtrType;
	
    data.nativePtrVal.ptr = _ptr;
	data.nativePtrVal.typeId = _typeId;
}

Value::Value(Type _type) {
    type = _type;
    switch(_type){
        case(Type::BooleanType):
            data.boolVal = false;
            break;
        case(Type::LibraryFunctionType):
            data.libFuncVal.ast = nullptr;
            data.libFuncVal.libFuncName = nullptr;
            data.libFuncVal.libFuncName = nullptr;
            break;
        case(Type::NativePtrType):
            data.nativePtrVal.ptr = nullptr;
            data.nativePtrVal.typeId = nullptr;
            break;
        case(Type::NumberType):
            data.numVal = 0;
            break;
        case(Type::ObjectType):
            data.objectVal = nullptr;
            break;
        case(Type::ProgramFunctionType):
            data.progFuncVal.ast = nullptr;
            data.progFuncVal.closure = nullptr;
            data.progFuncVal.funcName = nullptr;
            break;
        case(Type::StringType):
            data.strVal = nullptr; 
        default:
            ; //ena semicolon kati
    }
}

Value::Value(double _numVal) {
    type = Type::NumberType;
    data.numVal = _numVal;
}

Value::Value(bool _boolVal) {
    type = Type::BooleanType;
    data.boolVal = _boolVal;
}

Value::Value(const char* _strVal) {
    type = Type::StringType;
    data.strVal = strdup(_strVal);
}

Value::Value(LibraryFunction libFuncAst, const char *name) {
    type = Type::LibraryFunctionType;
    data.libFuncVal.ast = libFuncAst;
    data.libFuncVal.libFuncName = strdup(name);
}

Value::Value(Object* _objectVal) {
    type = Type::ObjectType;
    data.objectVal = _objectVal;
    _objectVal->incRefCounter();
}

Value::Value(Object* _funcAst, Object* _funcClosure, const char *name) {
    type = Type::ProgramFunctionType;
    data.progFuncVal.ast = _funcAst;
    data.progFuncVal.closure = _funcClosure;
    data.progFuncVal.funcName = strdup(name);
    _funcAst->incRefCounter();
    _funcClosure->incRefCounter();
}

Value::Value(void* _ptr, const char* _typeId) {
     type = Type::NativePtrType;
     data.nativePtrVal.ptr = _ptr;
     data.nativePtrVal.typeId = _typeId;
}

Value::Value(const Value& _v) {
    type = _v.getType();
    switch(_v.getType()) {
        case(Type::StringType):
            data.strVal = strdup(_v.data.strVal);
            break;
        case(Type::LibraryFunctionType):
            data.libFuncVal.ast = _v.data.libFuncVal.ast;           
            data.libFuncVal.libFuncName = strdup(_v.data.libFuncVal.libFuncName);
            break;
        case(Type::ObjectType):
            data.objectVal = _v.data.objectVal;
            _v.data.objectVal->incRefCounter();
            break;
        case(Type::ProgramFunctionType):
            data.progFuncVal.ast = _v.data.progFuncVal.ast;
            _v.data.progFuncVal.ast->incRefCounter();
            data.progFuncVal.closure = _v.data.progFuncVal.closure;
            _v.data.progFuncVal.closure->incRefCounter();
            data.progFuncVal.funcName = strdup(_v.data.progFuncVal.funcName);
            break;
        case(Type::NativePtrType):
            data.nativePtrVal.ptr = _v.data.nativePtrVal.ptr;
            data.nativePtrVal.typeId = _v.data.nativePtrVal.typeId;
            break;
        case(Type::NumberType):
            data.numVal = _v.data.numVal;
            break;
        case(Type::BooleanType):
            data.boolVal = _v.data.boolVal;
        default:
            ;
    }
}

Value::Value(Value&& _v){
    this->data = _v.data;
    this->type = _v.type;
    _v.type = UndefType; //cancel the temp value
}

void Value::clear() {
    if (isObject()) {
        (data.objectVal)->decRefCounter();       
        if (!(data.objectVal)->getRefCounter()) 
            delete data.objectVal;
    }
    else if (isProgramFunction()) {
        (data.progFuncVal.ast)->decRefCounter();
        if (!(data.progFuncVal.ast)->getRefCounter()) 
            delete data.progFuncVal.ast;
        (data.progFuncVal.closure)->decRefCounter();
        if (!(data.progFuncVal.closure)->getRefCounter()) 
            delete data.progFuncVal.closure;
        free(data.progFuncVal.funcName);
    }
    else if (isLibraryFunction()) {
        free(data.libFuncVal.libFuncName);
    }
    else if (isString()) {
        free(data.strVal);
    }
	
	type = Type::UndefType;
}

Value::~Value() {
    clear();
}

Type Value::getType() const {
    return type;
}

double Value::toNumber() const {
    assert(type == Type::NumberType);
    return data.numVal;
}

bool Value::toBoolean() const {
    assert(type == Type::BooleanType);
    return data.boolVal;
}

char* Value::toString() const {
    assert(type == Type::StringType);
    return data.strVal;
}

const Object* Value::toObject() const {
    assert(type == ObjectType);
    return toObjectNoConst();
}

const Object* Value::toProgramFunctionAST() const {
    assert(type == ProgramFunctionType);
    return toProgramFunctionASTNoConst();
}

const Object* Value::toProgramFunctionClosure() const {
    assert(type == ProgramFunctionType);
    return toProgramFunctionClosureNoConst();
}

const char* Value::toProgramFunctionName() const {
    assert(type == ProgramFunctionType);
    return data.progFuncVal.funcName;
}

Object* Value::toObjectNoConst() const {
    assert(type == Type::ObjectType);
    return data.objectVal;
}

Object* Value::toProgramFunctionASTNoConst() const {
    assert(type == Type::ProgramFunctionType);
    return data.progFuncVal.ast;
}

Object* Value::toProgramFunctionClosureNoConst() const {
    assert(type == Type::ProgramFunctionType);
    return data.progFuncVal.closure;
}

const LibraryFunction Value::toLibraryFunction() const {
    assert(type == Type::LibraryFunctionType);
    return data.libFuncVal.ast;
}

void* Value::toNativePtr() const {
    assert(type == Type::NativePtrType);
    return data.nativePtrVal.ptr;
}

const char* Value::toNativeTypeId() const {
    assert(type == Type::NativePtrType);
    return data.nativePtrVal.typeId;
}

Value* Value::clone() const {
    auto tmp = new Value(*this);
    return tmp;
}

void Value::swap(Value& _v) {
    Type tmp = type;
    type = _v.type;
    _v.type = tmp;
    auto tmp2 = data;
    data = _v.data;
    _v.data = tmp2;
}

const Value Value::operator=(const Value& _v) {
    Value tmp(_v);
    swap(tmp);
    return *this;
}

Value& Value::operator=(Value&& _v){
    if(this != &_v){
        clear();
        this->data = _v.data;
        this->type = _v.type;
        _v.type = UndefType;
    }
    return *this;
}

//NUMERIC OPERATORS
Value Value::operator+(const Value&other) const {
    if(isNumber() && other.isNumber())
        return Value(this->data.numVal + other.data.numVal);
    else if(isNumber() && other.isString()) {
        std::string tmp = std::to_string(this->data.numVal);
        tmp = tmp + std::string(other.data.strVal);
        return Value(tmp.c_str());
    }
    else if(isString() && other.isNumber()) {
        std::string tmp = std::to_string(other.data.numVal);
        tmp = std::string(this->data.strVal) + tmp;
        return Value(tmp.c_str());        
    }
    else if(isString() && other.isString())
        return Value((std::string(data.strVal) + std::string(other.data.strVal)).c_str());
    throw std::runtime_error("Invalid operands to \"+\"");
}

Value Value::operator-(const Value&other) const {
    if(isNumber() && other.isNumber())
        return Value(this->data.numVal - other.data.numVal);
    throw std::runtime_error("Invalid operands to \"-\"");
}

Value Value::operator*(const Value&other) const {
    if(isNumber() && other.isNumber())
        return Value(this->data.numVal * other.data.numVal);
    throw std::runtime_error("Invalid operands to \"*\"");    
}

Value Value::operator/(const Value&other) const {
    if(isNumber() && other.isNumber()){
        if(other.data.numVal == 0)
            throw std::runtime_error("Division by zero");
        return Value(this->data.numVal / other.data.numVal);
    }
    throw std::runtime_error("Invalid operands to \"/\"");
}

Value Value::operator%(const Value&other) const {
    if(isNumber() && other.isNumber()){
        if(this->data.numVal != (int)this->data.numVal && other.data.numVal != (int)other.data.numVal)
            throw std::runtime_error("Non-integer modulus operands");
        if(other.data.numVal == 0)
            throw std::runtime_error("Modulus with 0");
        return Value( (double)((int)this->data.numVal % (int)other.data.numVal));
    }
    throw std::runtime_error("Invalid operands to %");  
}

//RELATIONAL OPERATORS
Value Value::operator>(const Value& other) const{
    if(isNumber() && other.isNumber())
        return this->data.numVal > other.data.numVal;
    if(isString() && other.isString())
        return strcmp(this->data.strVal, other.data.strVal) > 0;
    if(isUndef() || other.isUndef())
        throw std::runtime_error("Operand of \">\" is undefined");
    throw std::runtime_error("Invalid operands to \">\"");
}

Value Value::operator>=(const Value& other) const{
    try{
        return this->operator==(other) || this->operator>(other);
    }
    catch(std::runtime_error &e){
        if(isUndef() || other.isUndef())
            throw e;
        throw std::runtime_error("Invalid operands to \">=\"");
    }
}

Value Value::operator<(const Value& other) const{
    if(isNumber() && other.isNumber())
        return this->data.numVal < other.data.numVal;
    if(isString() && other.isString())
        return strcmp(this->data.strVal, other.data.strVal) < 0;
    if(isUndef() || other.isUndef())
        throw std::runtime_error("Operand of \"<\" is undefined");
    throw std::runtime_error("Invalid operands to \"<\"");
}

Value Value::operator<=(const Value& other) const{
    try{
        return this->operator==(other) || this->operator<(other);
    }
    catch(std::runtime_error &e){
        if(isUndef() || other.isUndef())
            throw e;
        throw std::runtime_error("Invalid operands to \"<=\"");
    }
}

Value Value::operator==(const Value& other) const{
    if(this->type != other.type){       
        return false;        
    }
    switch(this->type){
        case(NumberType):
            return this->data.numVal == other.data.numVal;
        case(StringType):
            return strcmp(this->data.strVal, other.data.strVal) == 0;
        case(BooleanType):
            return this->data.boolVal == other.data.boolVal;
        case(ObjectType):
            return this->data.objectVal == other.data.objectVal;
        case(LibraryFunctionType):
            return this->data.libFuncVal.ast == other.data.libFuncVal.ast && !strcmp(this->data.libFuncVal.libFuncName, other.data.libFuncVal.libFuncName);
        case(ProgramFunctionType):
            return this->data.progFuncVal.ast == other.data.progFuncVal.ast && this->data.progFuncVal.closure == other.data.progFuncVal.closure;
        case(NativePtrType):
            return this->data.nativePtrVal.ptr == other.data.nativePtrVal.ptr;
        case(NilType):
            return true;
        case(UndefType):
            throw std::runtime_error("Operand of \"==\" is undefined");
    }
    return false;
}

Value Value::operator!=(const Value& other) const{
    try{
        return !(this->operator==(other));
    }
    catch(std::runtime_error &e){
        if(isUndef())
            throw e;
        throw std::runtime_error("Invalid operands to \"!=\"");
    }
}

Value::operator bool() const {
     switch(type) {
        case UndefType:
            throw std::runtime_error("Operand to logical operator is undefined\n");
        case NumberType:
            return (data.numVal != 0);
        case BooleanType:
            return data.boolVal;
        case StringType:
            return strlen(data.strVal) != 0;
        case ObjectType:            
        case ProgramFunctionType:
        case LibraryFunctionType:
            return true;
        case NativePtrType:
            return data.nativePtrVal.ptr != nullptr;
        case NilType:
            return false;
        default:
            assert(false); //bad area        
     }
}

std::string Value::makeString() const{
    switch(type) {
        case(Type::StringType):
            return std::string(data.strVal);
        case(Type::LibraryFunctionType):
            return "library function " + std::string(data.libFuncVal.libFuncName);
        case(Type::ObjectType):
            return data.objectVal->toString();
        case(Type::ProgramFunctionType):
            return "user function " + std::string(data.progFuncVal.funcName);
        case(Type::NativePtrType):
            return data.nativePtrVal.typeId;
        case(Type::NumberType):
            return std::to_string(data.numVal);
        case(Type::BooleanType):
            return data.boolVal ? "true" : "false";
        case(Type::UndefType):
            return "undefined";
        case(Type::NilType):
            return "nil";
        default:
            ;
    }
    return std::string();
}

std::string Value::typeOfToString() {
    switch (type) {
        case(Type::StringType):
            return "string";
        case(Type::LibraryFunctionType):
            return "libraryfunction";
        case(Type::ObjectType):
            return "object";
        case(Type::ProgramFunctionType):
            return "userfunction";
        case(Type::NativePtrType):
            return "nativepointer";
        case(Type::NumberType):
            return "number";
        case(Type::BooleanType):
            return "boolean";
        case(Type::NilType):
            return "nil";
        default:
            ;    
    }
    return std::string();
}