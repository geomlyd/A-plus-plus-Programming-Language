#include "Interpreter.h"
#include "error_handler.h"
#include <iostream>
#include <regex>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include "ASTCreator.h"
#define NUM_SPECIAL_ARGS 4


void libfuncPrint(Object& args) {
    for (unsigned i = 0; i < args.getTotal() - NUM_SPECIAL_ARGS; i++) {
        std::string s = args[i]->makeString();
        std::cout << s << std::flush;
    }
    //retval shenanigans
}

void libfuncTypeOf(Object& args) {
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: typeof: too many or too few arguments\n\n");
        exit(-1);
    }
    else {
        args.set("$retval", Value(args[(double)0]->typeOfToString().c_str()));        
    }
}

void libfuncObjectKeys(Object& args) {
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: objectKeys: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::ObjectType) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: objectKeys: argument is not of Object type\n\n");
        exit(-1);
    }
    else {
        Object *obj = args[(double) 0]->toObjectNoConst();        
        Object *toReturn = new Object();

        double i = 0;
        obj->visit(
		    [toReturn, &i](const Value& key, const Value* val) {
                toReturn->set(i++, key);
            }
	    );
        args.set("$retval", Value(toReturn));
    }
}

void libfuncObjectSize(Object &args) {
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: objectSize: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::ObjectType) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: objectSize: argument is not of Object type\n\n");
        exit(-1);
    }
    else {
        const Object *obj = args[(double) 0]->toObject();
        args.set("$retval", Value((double)obj->getTotal()));
    }
}

void libfuncInput(Object &args) {
    if (args.getTotal() > NUM_SPECIAL_ARGS) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: input: too many arguments\n\n");
        exit(-1);
    }
    else {
        std::regex integer("(0[xX][0-9A-Fa-f]+)|([0-9]+)");
        std::regex real("(([0-9]+\\.[0-9]*)|([0-9]*\\.[0-9]+))((e|E)([-\\+]?)[0-9]+)?");   
        std::smatch m;
        std::string input;       

        std::getline(std::cin, input);

        if(std::regex_match(input,m,integer) || std::regex_match(input,m,real)){
            args.set("$retval", Value(std::stod(input)));            
        }                
        else if(input == "true" || input == "false"){
            if (input == "true")
                args.set("$retval", Value(true));
            else 
                args.set("$retval", Value(false));
        }
        else if(input == "nil"){
            args.set("$retval", Value(Value::Type::NilType));
        }                
        else{ 
            if( input.length() > 2 && (input[0] == '\"' && input[input.length()-1] == '\"')){
                input.erase(0,1);
                input.erase(input.length()-1,1);
            }                
            args.set("$retval", Value(input.c_str()));                   
        }	
    }
}

void libfuncStrToNum(Object& args) {
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: strToNum: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::StringType) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: strToNum: argument is not of String type\n\n");
        exit(-1);
    }
    else {
        std::string tmp = args[(double)0]->toString();
        std::regex integer("(0[xX][0-9A-Fa-f]+)|([0-9]+)");
        std::regex real("(([0-9]+\\.[0-9]*)|([0-9]*\\.[0-9]+))((e|E)([-\\+]?)[0-9]+)?");        
        std::smatch m;

        if(std::regex_match(tmp,m,integer) || std::regex_match(tmp,m,real)){
            args.set("$retval", Value((double)std::stod(tmp))); 
        }
        else{
            args.set("$retval", Value(Value::Type::NilType));           
        } 
    }
}

void libfuncSqrt(Object& args) {
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: sqrt: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::NumberType) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: sqrt: argument is not of Number type\n\n");
        exit(-1);
    }
    else {
        if (args[(double)0]->toNumber() < 0) {
            args.set("$retval", Value((Value::Type::NilType)));
        }
        else {
            double value = sqrt(args[(double)0]->toNumber());
            args.set("$retval", Value(value));
        }
        
    }
}

void libfuncCos(Object& args) {
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: cos: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::NumberType) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: cos: argument is not of Number type\n\n");
        exit(-1);
    }
    else {
        double value = cos(args[(double)0]->toNumber() * M_PI  / 180.0);
        args.set("$retval", Value(value));
    }
}

void libfuncSin(Object& args) {
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: sin: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::NumberType) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: sin: argument is not of Number type\n\n");
        exit(-1);
    }
    else {
        double value = sin(args[(double)0]->toNumber() * M_PI  / 180.0);
        args.set("$retval", Value(value));
    }
}

void libfuncTotalArguments(Object& args) {
    double currLineNo = args["$lineNo"]->toNumber();
    if(args.getTotal() != NUM_SPECIAL_ARGS){
        error(ErrorType::Error, currLineNo, "A++ runtime error: totalArguments: too many arguments\n\n");
        exit(-1);        
    }   
    if(args["$caller"]->isString() && std::string(args["$caller"]->toString()) == "@_invalid") {
        error(ErrorType::Error, currLineNo, "A++ runtime error: totalArguments: call not in function\n\n");
        exit(-1); 
    }
    args.set("$retval", *args["$numCallerArgs"]);
}

void libfuncGetArgument(Object& args){
    auto argIndex = args[(double)0];
    double currLineNo = args["$lineNo"]->toNumber();
    if(args["$caller"]->isString() && std::string(args["$caller"]->toString()) == "@_invalid"){
        error(ErrorType::Error, currLineNo, "A++ runtime error: getArgument: call not in function\n\n");
        exit(-1);          
    }   
    Object *currentFunction = args["$caller"]->toProgramFunctionASTNoConst();
    Object *callerEnv = args["$callerEnv"]->toObjectNoConst();
    if(args.getTotal() != NUM_SPECIAL_ARGS + 1){
        error(ErrorType::Error, currLineNo, "A++ runtime error: getArgument: too many or too few arguments\n\n");
        exit(-1);        
    }
    if(!argIndex->isNumber() || argIndex->toNumber() < 0 || argIndex->toNumber() != (int)argIndex->toNumber()){
        error(ErrorType::Error, currLineNo, "A++ runtime error: getArgument: expected exactly one integer argument\n");
        exit(-1);          
    }
    Value *arg = (*callerEnv)[std::to_string((int)argIndex->toNumber())];
    if(arg != nullptr) {//argument was passed without a match to an actual name
        args.set("$retval", *arg);
        return;
    }
    else { //look up the name of the corresponding argument
        auto idlist = (*currentFunction)[AST_TAG_IDLIST];
        bool notFound = true;
        if(idlist != nullptr){
            auto formalsNode = (*idlist->toObjectNoConst())[AST_TAG_CHILDREN];
            auto formals = (std::vector<Object*>*)formalsNode->toNativePtr();
            if(formals != nullptr && argIndex->toNumber() < formals->size()){
                Value *potentialName = (*(*formals)[(int)argIndex->toNumber()])[AST_TAG_ID];
                Value *potentialSymbol = (*callerEnv)[potentialName];
                if(potentialSymbol != nullptr){
                    notFound = false;
                    args.set("$retval", *potentialSymbol);
                    return;
                }
            }
        }
        if(notFound){
            error(ErrorType::Error, currLineNo, "A++ runtime error: getArgument: argument index out of bounds\n");
            exit(-1);             
        }
    }
}

void libfuncObjectCopy(Object& args){
    double currLineNo = args["$lineNo"]->toNumber();
    if(args.getTotal() != NUM_SPECIAL_ARGS + 1){
        error(ErrorType::Error, currLineNo, "A++ runtime error: objectCopy: too many or too few arguments\n\n");
        exit(-1);        
    }    
    if(!args[(double)0]->isObject()){
        error(ErrorType::Error, currLineNo, "A++ runtime error: objectCopy: argument not an object\n\n");
        exit(-1);        
    }
	Object* obj = new Object;
	args[(double)0]->toObject()->visit(
		[obj](const Value& key, const Value* val) 
			{ obj->set(&key, *val); }
	);
	args.set("$retval", Value(obj));    
}

void libfuncFileOpen(Object& args) {
    double currLineNo = args["$lineNo"]->toNumber();
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileOpen: too many or too few arguments\n\n");
        exit(-1);
    }
    const char* filepath = args[(double)0]->toString();
    try {
        std::fstream* f = new std::fstream(filepath, std::fstream::in | std::fstream::out);
        Value* filewrapper = new Value((void*)f, "FILE");
        args.set("$retval", *filewrapper);
    } catch (std::fstream::failure& e) {
        try {
            std::fstream* f = new std::fstream(filepath, std::fstream::in);
            Value* filewrapper = new Value((void*)f, "FILE");
            args.set("$retval", *filewrapper);
        } catch (std::fstream::failure& e) {
            error(ErrorType::Error, currLineNo, "A++ runtime error: fileOpen: Couldn't open the file\n\n");
            exit(-1);
        }
    }
}

void libfuncFileClose(Object& args) {
    double currLineNo = args["$lineNo"]->toNumber();
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileClose: too many or too few arguments\n\n");
        exit(-1);
    }
    Value* filewrapper = args[(double)0];
    if (strcmp(filewrapper->toNativeTypeId(), "FILE")) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileClose: input Value not a file\n");
        exit(-1);
    }
    try {
        std::fstream* f = (std::fstream*) filewrapper->toNativePtr();
        f->close();
        delete(f);
    } catch (std::fstream::failure& e) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileClose: failed to close file\n");
        exit(-1);
    }
    
    args.set("$retval", Value(Value::NilType));
}

void libfuncFileWrite(Object& args) {
    double currLineNo = args["$lineNo"]->toNumber();
    if (args.getTotal() != NUM_SPECIAL_ARGS + 2) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileWrite: too many or too few arguments\n\n");
        exit(-1);
    }
    Value* filewrapper = args[(double)0];
    if (strcmp(filewrapper->toNativeTypeId(), "FILE")) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileWrite: input Value not a file\n");
        exit(-1);
    }
    std::fstream* f = (std::fstream*) filewrapper->toNativePtr();
    try {
        if (f->is_open()) {
            std::string line = std::string(args[(double)1]->toString());
            *f << line;
        } else {
            error(ErrorType::Error, currLineNo, "A++ runtime error: fileWrite: input file not open\n");
            exit(-1);
        }
    } catch(std::fstream::failure& e) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileWrite: failed to write file\n");
    }
    
    args.set("$retval", Value(Value::NilType));
}

void libfuncFileGetLine(Object& args) {
    double currLineNo = args["$lineNo"]->toNumber();
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileGetLine: too many or too few arguments\n\n");
        exit(-1);
    }
    Value* filewrapper = args[(double)0];
    if (strcmp(filewrapper->toNativeTypeId(), "FILE")) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileGetLine: input Value not a file\n");
        exit(-1);
    }
    std::string line;
    std::fstream* f = (std::fstream*) filewrapper->toNativePtr();
    try {
        if (f->is_open()) {
            getline(*f, line);
        } else {
            error(ErrorType::Error, currLineNo, "A++ runtime error: fileGetLine: input file not open\n");
            exit(-1);
        }
        args.set("$retval", Value(line.c_str()));
    } catch(std::fstream::failure& e) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileWrite: failed to write file\n");
        exit(-1);
    }
    
    
}

void libfuncFileGetWord(Object& args) {
    double currLineNo = args["$lineNo"]->toNumber();
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileGetWord: too many or too few arguments\n\n");
        exit(-1);
    }
    Value* filewrapper = args[(double)0];
    if (strcmp(filewrapper->toNativeTypeId(), "FILE")) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileGetWord: input Value not a file\n");
        exit(-1);
    }
    std::fstream* f = (std::fstream*) filewrapper->toNativePtr();
    std::string word;
    try {
        if (f->is_open()) {
           *f >> word;
        } else {
            error(ErrorType::Error, currLineNo, "A++ runtime error: fileGetWord: input file not open\n");
            exit(-1);
        }
    } catch(std::fstream::failure& e) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileWrite: failed to write file\n");
        exit(-1);
    }

    std::regex integer("(0[xX][0-9A-Fa-f]+)|([0-9]+)");
    std::regex real("(([0-9]+\\.[0-9]*)|([0-9]*\\.[0-9]+))((e|E)([-\\+]?)[0-9]+)?");   
    std::smatch m;
    if(std::regex_match(word,m,integer) || std::regex_match(word,m,real)){
        args.set("$retval", Value(std::stod(word)));            
    }                
    else if(word == "true" || word == "false"){
        if (word == "true")
            args.set("$retval", Value(true));
        else 
            args.set("$retval", Value(false));
    }
    else if(word == "nil"){
        args.set("$retval", Value(Value::Type::NilType));
    }                
    else{ 
        if( word.length() > 2 && (word[0] == '\"' && word[word.length()-1] == '\"')){
            word.erase(0,1);
            word.erase(word.length()-1,1);
        }                
        args.set("$retval", Value(word.c_str()));                   
    }
}

void libfuncFileRead(Object& args) {
    double currLineNo = args["$lineNo"]->toNumber();
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileRead: too many or too few arguments\n\n");
        exit(-1);
    }
    Value* filewrapper = args[(double)0];
    if (strcmp(filewrapper->toNativeTypeId(), "FILE")) {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileRead: input Value not a file\n");
        exit(-1);
    }
    std::stringstream text;
    std::string line;
    std::fstream* f = (std::fstream*) filewrapper->toNativePtr();
    if (f->is_open()) {
        while (getline(*f, line)) {
            text << line << std::endl;
        }
    } else {
        error(ErrorType::Error, currLineNo, "A++ runtime error: fileGetLine: input file not open\n");
        exit(-1);
    }
    std::string toreturn = std::string(text.str());
    args.set("$retval", Value(toreturn.c_str()));
}

void libfuncEval(Object& args){
    double currLineNo = args["$lineNo"]->toNumber();
    if(args.getTotal() != NUM_SPECIAL_ARGS + 1){
        error(ErrorType::Error, currLineNo, "A++ runtime error: eval: too many or too few arguments\n");
        exit(-1);        
    }    
    if(!args[(double)0]->isString()){
        error(ErrorType::Error, currLineNo, "A++ runtime error: eval: argument not a string\n");
        exit(-1);        
    }    
    std::string codeString = args[(double)0]->toString();
    std::istringstream codeStream = std::istringstream(codeString);
    if(std::all_of(codeString.begin(), codeString.end(), isspace)){
        args.set("$retval", Value(Value::Type::NilType));
        return;
    }
    auto evalAst = ASTCreator::parseToAST(true, &codeStream);
    evalAst->set("$parent", ASTCreator::getOptionalParent());
    ASTCreator::validateAST(evalAst);
    const Value val = ASTCreator::interpretAST(evalAst);
    args.set("$retval", Value(val));
    evalAst->remove("$parent");
    ASTCreator::destroyAST(evalAst);
}

void libfuncFloor(Object& args) {   
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: floor: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::NumberType) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: floor: argument is not of Number type\n\n");
        exit(-1);
    }
    else {
        double value = floor(args[(double)0]->toNumber());
        args.set("$retval", Value(value));
    }    
}

void libfuncCeiling(Object& args) {   
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: floor: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::NumberType) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: floor: argument is not of Number type\n\n");
        exit(-1);
    }
    else {
        double value = ceil(args[(double)0]->toNumber());
        args.set("$retval", Value(value));
    }    
}

void libfuncExit(Object& args) {
    if (args.getTotal() > NUM_SPECIAL_ARGS) {
        error(ErrorType::Error, args["$lineNo"]->toNumber(), "A++ runtime error: input: too many arguments\n\n");
        exit(-1);
    }
    else {
        exit(-1);
    }
}

/*
void libfuncGtkNewApplication(Object& args) {
    if (args.getTotal() != NUM_SPECIAL_ARGS + 1) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: gtkNewApplication: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::StringType) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: gtkNewApplication: argument 1 is not of String type\n\n");
        exit(-1);
    }
    GtkApplication* app;
    app = gtk_application_new(args[(double)0], G_APPLICATION_FLAGS_NONE);
    args.set("$retval", Value((void*)app, "GTK_APP"));
}
*/
/*
void libfuncGtkNewWindow(Object& args) {
    if (args.getTotal() != NUM_SPECIAL_ARGS + 4) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: gtkNewWindow: too many or too few arguments\n\n");
        exit(-1);
    }
    else if (args[(double)0]->getType() != Value::Type::NativePtrType) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: gtkNewWindow: argument 1 is not of NativePtr type\n\n");
        exit(-1);
    }
    else if (args[(double)1]->getType() != Value::Type::StringType) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: gtkNewWindow: argument 2 is not of String type\n\n");
        exit(-1);
    }
    else if (args[(double)2]->getType() != Value::Type::NumberType) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: gtkNewWindow: argument 3 is not of Number type\n\n");
        exit(-1);
    }
    else if (args[(double)3]->getType() != Value::Type::NumberType) {
        error(ErrorType::Error, args[AST_TAG_LINE_KEY]->toNumber(), "A++ runtime error: gtkNewWindow: argument 4 is not of Number type\n\n");
        exit(-1);
    }
    GtkWindow* window;
    GtkApplication* app = (GtkApplication*) args[(double)0]->toNativePtr();
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), args[(double)1]->toString());
    gtk_window_set_default_side(GTK_WINDOW(window), args[(double)2], args[(double)3]);
    args.set("$retval", Value((void*)window, "GTK_WINDOW"));
}
*/