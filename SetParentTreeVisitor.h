#ifndef SETPARENTTREEVISITOR_H
#define SETPARENTTREEVISITOR_H

#include "TreeVisitor.h"
#include "ValueStack.h"
#include <string.h>
#define PARENT_FIELD "$parent"

class SetParentTreeVisitor final : public TreeVisitor {
private:
    ValueStack valueStack;
    bool       isRemoval = false;
    void       setParent(Object& parent, int numPops) {
                    bool isRoot = strcmp(parent[AST_TAG_SUBTYPE_KEY]->toString(), AST_TAG_PROGRAM) == 0 ? true : false;
                    if (isRemoval) {
                        if (!isRoot)
                            parent.remove(PARENT_FIELD);
                    }
                    else {
                        int i = 0;
                        while (!valueStack.isEmpty() && i++ < numPops) 
                            valueStack.getTopAndPop().toObjectNoConst()->set(PARENT_FIELD, Value(&parent));
                        if(!isRoot)
                            valueStack.push(Value(&parent));
                    }
                }
public:
    virtual void visitProgram(Object& node) override;
    virtual void visitStmts(Object& node) override;
    virtual void visitStmt(Object& node) override;
    virtual void visitMultiCall(Object& node) override;
    virtual void visitFdefCall(Object& node) override;
    virtual void visitNormCall(Object& node) override;
    virtual void visitMethodCall(Object& node) override;
    virtual void visitElist(Object& node) override;
    virtual void visitElistNotEmpty(Object& node) override;
    virtual void visitObjectDef(Object& node) override;
    virtual void visitCommaIndexed(Object& node) override;
    virtual void visitBlock(Object& node) override;
    virtual void visitFuncDef(Object& node) override;
    virtual void visitFuncPrefix(Object& node) override;
    virtual void visitFuncName(Object& node) override;
    virtual void visitCommaIdList(Object& node) override;
    virtual void visitForPrefix(Object& node) override;
    virtual void visitFormal(Object& node) override;
    virtual void visitObjElistNotEmpty(Object& node) override;
    virtual void visitForStmt(Object& node) override;

    #define IMPL_VISIT(type, numPops) \
    virtual void visit##type (Object& node) override {setParent(node, numPops);}
    IMPL_VISIT( Continue, 0           )          IMPL_VISIT( Expr, 1                      )
    IMPL_VISIT( ArithExpr, 2          )          IMPL_VISIT( RelExpr, 2                   )
    IMPL_VISIT( BoolExpr, 2           )          IMPL_VISIT( Term, 1                      )
    IMPL_VISIT( TermParensExpr, 1     )          IMPL_VISIT( TermMinusExpr, 1             )
    IMPL_VISIT( TermNotExpr, 1        )          IMPL_VISIT( TermPlusPlusLvalue, 1        )
    IMPL_VISIT( TermMinusMinusLvalue, 1 )          IMPL_VISIT( TermLvaluePlusPlus, 1        )
    IMPL_VISIT( TermLvalueMinusMinus, 1 )          IMPL_VISIT( AssignExpr, 2                )
    IMPL_VISIT( Primary, 1              )          IMPL_VISIT( LvalueId, 0                  )
    IMPL_VISIT( LvalueGlobalId, 0       )          IMPL_VISIT( LvalueLocalId, 0             )
    IMPL_VISIT( LvalueMember, 1         )          IMPL_VISIT( MemberId, 1                  )
    IMPL_VISIT( MemberExpr, 2           )          IMPL_VISIT( Call, 2                      )
    IMPL_VISIT( NormCallSuffix, 1       )          IMPL_VISIT( MethodCallSuffix, 1          )
    IMPL_VISIT( ObjectDinnerObjElistnotempty, 1 )  IMPL_VISIT( ObjectDinnerIndexed, 1       )
    IMPL_VISIT( IndexedElem, 2          )          IMPL_VISIT( ID, 0                        )
    IMPL_VISIT( Const, 0                )          IMPL_VISIT( Break, 0                     )
    IMPL_VISIT( ConstNumconst, 0        )          IMPL_VISIT( ConstStringconst, 0          )
    IMPL_VISIT( ConstBoolconst, 0       )          IMPL_VISIT( ConstNil, 0                  )
    IMPL_VISIT( IfPrefix, 1             )          IMPL_VISIT( ElsePrefix, 0                )
    IMPL_VISIT( IfStmt, 2               )          IMPL_VISIT( IfStmtElseStmt, 4            )
    IMPL_VISIT( WhileStart, 0           )          IMPL_VISIT( WhileCond, 1                 )
    IMPL_VISIT( WhileStmt, 3            )          IMPL_VISIT( Argument, 1                  )
    IMPL_VISIT( ReturnStmt, 0           )          IMPL_VISIT( ReturnStmtExpr, 1            )
    IMPL_VISIT( QuasiQuotes, 1          )          
    IMPL_VISIT( QuotedRules, 1          )
    IMPL_VISIT( EscapeId, 0             )          IMPL_VISIT( EscapeExpr, 1                ) 
    IMPL_VISIT( Inline, 1               )          IMPL_VISIT( Unparsed, 1                  )
    IMPL_VISIT( CompiledString, 1       )          IMPL_VISIT( ValueStorage, 0              )
    #undef IMPL_VISIT

    void        setIsRemoval(bool v) {isRemoval = v; }   
    virtual TreeVisitor* Clone(void) const override {
        return new SetParentTreeVisitor(isRemoval);
    }
    SetParentTreeVisitor(bool _isRemoval) : isRemoval(_isRemoval) {
    }
    ~SetParentTreeVisitor() {
        valueStack.clear();
    }
};


#endif 