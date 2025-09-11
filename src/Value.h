#ifndef VALUE_H
#define VALUE_H

#include <string>

class Object;

typedef void (*LibraryFunction)(Object&);

class Value { 
    public:
    enum Type {
        UndefType = 0,
        NumberType,
        BooleanType,
        StringType,
        ObjectType,
        ProgramFunctionType,
        LibraryFunctionType,
        NativePtrType,
        NilType
    };
	
    Value(Type _type); //otherwise undef
    Value(double _numVal);
    Value(bool _boolVal);
    Value(const char* _strVal);
    Value(LibraryFunction libFuncAst, const char *name);
    Value(Object* _objectVal);
    Value(Object* _funcAst, Object* _funcClosure, const char *name);
    Value(void* _ptr, const char* _typeId);
    Value(const Value&);
    Value(Value&&);
    
    ~Value();

    operator                bool() const;

    bool                    isUndef() const;
    bool                    isNumber() const;
    bool                    isBoolean() const;
    bool                    isString() const;
    bool                    isObject() const;
    bool                    isProgramFunction() const;
    bool                    isLibraryFunction() const;
    bool                    isNativePtr() const;
    bool                    isNil() const;

    Type                    getType() const;

    double                  toNumber() const;
    bool                    toBoolean() const;
    char*                   toString() const;    
    const Object*           toObject() const;
    const Object*           toProgramFunctionAST() const;
    const Object*           toProgramFunctionClosure() const;
    const char*             toProgramFunctionName() const;
    Object*                 toObjectNoConst() const;
    Object*                 toProgramFunctionASTNoConst() const;
    Object*                 toProgramFunctionClosureNoConst() const;
    const LibraryFunction   toLibraryFunction() const;
    void*                   toNativePtr() const;
    const char*             toNativeTypeId() const;

	void					fromNil(void);   
    void                    fromNativePtr (void* _ptr, char* _typeId);
	void                    fromProgramFunction (Object* _funcAst, Object* _funcClosure, const char *name);	
	void                    fromObject (Object* _objectVal);
	void                    fromLibraryFunction (LibraryFunction ast, char *name);
	void                    fromString (const char *_strVal);
	void                    fromBool (bool _boolVal);
	void                    fromDouble (double _numVal); 

    Value*                  clone() const;
    void                    clear();
    void                    swap(Value&);    

    const Value             operator=(const Value&);
    Value&                  operator=(Value&&);
    Value                   operator+(const Value& other) const;
    Value                   operator-(const Value& other) const;
    Value                   operator*(const Value& other) const;
    Value                   operator/(const Value& other) const;
    Value                   operator%(const Value& other) const;

    Value                   operator>(const Value& other) const;
    Value                   operator>=(const Value& other) const;
    Value                   operator<(const Value& other) const;
    Value                   operator<=(const Value& other) const;
    Value                   operator==(const Value& other) const;
    Value                   operator!=(const Value& other) const;

    std::string             makeString() const;
    std::string             typeOfToString();
    
    private:
    Type type;
    union {
        double numVal;
        bool boolVal;
        char* strVal;
        struct {
            LibraryFunction ast;
            char *libFuncName;
        } libFuncVal;
        Object* objectVal;
        struct {
            Object* ast;
            Object* closure;
            char *funcName;
        } progFuncVal;
        struct {
            void* ptr;
            const char* typeId;
        } nativePtrVal;
    } data;
};

#endif