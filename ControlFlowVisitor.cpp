#include "ControlFlowVisitor.h"
#include "error_handler.h"
#include <string.h>

#define PARENT_FIELD "$parent"

void ControlFlowVisitor::visitProgram(Object& node) {return; }
void ControlFlowVisitor::visitStmts(Object& node) { }
void ControlFlowVisitor::visitStmt(Object& node) { }

ControlFlowVisitor::ControlFlowVisitor() {}

void ControlFlowVisitor::visitBreak(Object& node) {
    Object *parent = node[PARENT_FIELD]->toObjectNoConst();
    
    while (1) {
        if (parent == nullptr || !strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FUNCDEF)) {
            auto tmp = ("A++ error: Break not inside for/while statement\n");
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
            exit(1);
        }        
        else if (!strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_WHILESTMT) || !strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FORSTMT) || !strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_QUOTEDRULES))
            break;

        if ((*parent)[PARENT_FIELD] != nullptr)
            parent = (*parent)[PARENT_FIELD]->toObjectNoConst();
        else
            parent = nullptr;
    }
}

void ControlFlowVisitor::visitContinue(Object& node) {
    Object *parent = node[PARENT_FIELD]->toObjectNoConst();
    
    while (1) {
        if (parent == nullptr || !strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FUNCDEF)) {
            auto tmp = ("A++ error: Continue not inside for/while statement\n");
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
            exit(1);
        }       
        else if (!strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_WHILESTMT) || !strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FORSTMT) || !strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_QUOTEDRULES))
            break;

        if ((*parent)[PARENT_FIELD] != nullptr)
            parent = (*parent)[PARENT_FIELD]->toObjectNoConst();
        else
            parent = nullptr;
    }
}

void ControlFlowVisitor::visitExpr(Object& node) { }
void ControlFlowVisitor::visitArithExpr(Object& node) { }
void ControlFlowVisitor::visitRelExpr(Object& node) { }
void ControlFlowVisitor::visitBoolExpr(Object& node) { }

void ControlFlowVisitor::visitTerm(Object& node) { }
void ControlFlowVisitor::visitTermParensExpr(Object& node) { }
void ControlFlowVisitor::visitTermMinusExpr(Object& node) { }
void ControlFlowVisitor::visitTermNotExpr(Object& node) { }
void ControlFlowVisitor::visitTermPlusPlusLvalue(Object& node) { }
void ControlFlowVisitor::visitTermMinusMinusLvalue(Object& node) { }
void ControlFlowVisitor::visitTermLvaluePlusPlus(Object& node) { }
void ControlFlowVisitor::visitTermLvalueMinusMinus(Object& node) { }  
    
void ControlFlowVisitor::visitAssignExpr(Object& node) { }
void ControlFlowVisitor::visitPrimary(Object& node) { }
void ControlFlowVisitor::visitLvalueId(Object& node) { 
    Object *parent = node[PARENT_FIELD]->toObjectNoConst();
    if (std::string(node[AST_TAG_ID]->toString()) == "$lambda"){
        while (1) {
            if (parent == nullptr) {
                auto tmp = ("A++ error: $lambda not inside function");
                error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
                exit(1);
            }
            else if (!strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FUNCDEF) || !strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_QUOTEDRULES)) {
                break;
            }       

            if ((*parent)[PARENT_FIELD] != nullptr)
                parent = (*parent)[PARENT_FIELD]->toObjectNoConst();
            else
                parent = nullptr;
        }
    }
    
}
void ControlFlowVisitor::visitLvalueGlobalId(Object& node) { }
void ControlFlowVisitor::visitLvalueLocalId(Object& node) { }
void ControlFlowVisitor::visitLvalueMember(Object& node) { }
void ControlFlowVisitor::visitMemberId(Object& node) { }
void ControlFlowVisitor::visitMemberExpr(Object& node) { }
void ControlFlowVisitor::visitCall(Object& node) { }
void ControlFlowVisitor::visitMultiCall(Object& node) { }
void ControlFlowVisitor::visitFdefCall(Object& node) { }
void ControlFlowVisitor::visitNormCallSuffix(Object& node) { }
void ControlFlowVisitor::visitMethodCallSuffix(Object& node) { }
void ControlFlowVisitor::visitNormCall(Object& node) { }
void ControlFlowVisitor::visitMethodCall(Object& node) { }
void ControlFlowVisitor::visitElist(Object& node) { }
void ControlFlowVisitor::visitElistNotEmpty(Object& node) { }
void ControlFlowVisitor::visitArgument(Object& node) {}
void ControlFlowVisitor::visitObjectDef(Object& node) { }
void ControlFlowVisitor::visitObjElistNotEmpty( Object& node) { }
void ControlFlowVisitor::visitObjectDinnerObjElistnotempty( Object& node) {}
void ControlFlowVisitor::visitObjectDinnerIndexed(Object& node) { }

void ControlFlowVisitor::visitCommaIndexed(Object& node) { }
void ControlFlowVisitor::visitIndexedElem(Object& node) { }    
void ControlFlowVisitor::visitBlock(Object& node) { }
void ControlFlowVisitor::visitFuncDef(Object& node) { }
void ControlFlowVisitor::visitFuncPrefix(Object& node) { }
void ControlFlowVisitor::visitFuncName(Object& node) { }
void ControlFlowVisitor::visitConst(Object& node) { }
void ControlFlowVisitor::visitConstNumconst(Object& node) { }
void ControlFlowVisitor::visitConstStringconst(Object& node) { }
void ControlFlowVisitor::visitConstBoolconst(Object& node) { }
void ControlFlowVisitor::visitConstNil(Object& node) { }   
void ControlFlowVisitor::visitID(Object& node) { }
void ControlFlowVisitor::visitCommaIdList(Object& node) { }
void ControlFlowVisitor::visitFormal(Object& node) { }
void ControlFlowVisitor::visitIfPrefix(Object& node) { }
void ControlFlowVisitor::visitElsePrefix(Object& node) { }
void ControlFlowVisitor::visitIfStmt(Object& node) { }
void ControlFlowVisitor::visitIfStmtElseStmt(Object& node) { }
void ControlFlowVisitor::visitWhileStart(Object& node) {}
void ControlFlowVisitor::visitWhileCond(Object& node) {}
void ControlFlowVisitor::visitWhileStmt(Object& node) { }
void ControlFlowVisitor::visitForPrefix(Object& node) { }
void ControlFlowVisitor::visitForStmt(Object&node) { }

void ControlFlowVisitor::visitReturnStmt(Object& node) { 
    Object *parent = node[PARENT_FIELD]->toObjectNoConst();
    
    while (1) {
        if (parent == nullptr) {
            auto tmp = ("A++ error: return  not inside function\n");
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
            exit(1);
        }
        else if (!strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FUNCDEF) || !strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_QUOTEDRULES)) {
            break;
        }       

        if ((*parent)[PARENT_FIELD] != nullptr)
            parent = (*parent)[PARENT_FIELD]->toObjectNoConst();
        else
            parent = nullptr;
    }
}

void ControlFlowVisitor::visitReturnStmtExpr(Object& node) { 
    Object *parent = node[PARENT_FIELD]->toObjectNoConst();
    
    while (1) {
        if (parent == nullptr) {
            auto tmp = ("A++ error: return  not inside function\n");
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
            exit(1);
        }
        else if (!strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_FUNCDEF) || !strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_QUOTEDRULES)) {
            break;
        }       

        if ((*parent)[PARENT_FIELD] != nullptr)
            parent = (*parent)[PARENT_FIELD]->toObjectNoConst();
        else
            parent = nullptr;
    }
} 

void ControlFlowVisitor::visitQuasiQuotes(Object& node) {}

void ControlFlowVisitor::visitQuotedRules(Object& node) {}

void ControlFlowVisitor::visitEscapeId(Object& node) {
    Object *parent = node[PARENT_FIELD]->toObjectNoConst();
    
    while (1) {
        if (parent == nullptr) {
            auto tmp = ("A++ error: escape not inside quasi quotes\n");
            error(ErrorType::Error, node[AST_TAG_LINE_KEY]->toNumber(), tmp);
            exit(1);
        }
        else if (!strcmp((*parent)[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_QUOTEDRULES)) {
            break;
        }       

        if ((*parent)[PARENT_FIELD] != nullptr)
            parent = (*parent)[PARENT_FIELD]->toObjectNoConst();
        else
            parent = nullptr;
    }
}

void ControlFlowVisitor::visitEscapeExpr(Object& node) {
    visitEscapeId(node);
}

void ControlFlowVisitor::visitInline(Object& node) { }

void ControlFlowVisitor::visitUnparsed(Object& node) { }

void ControlFlowVisitor::visitCompiledString(Object& node) { }

void ControlFlowVisitor::visitValueStorage(Object& node) { }

 TreeVisitor* ControlFlowVisitor::Clone(void) const {
    return new ControlFlowVisitor();
 }

