#ifndef EVALESCAPESTREEVISITOR_H
#define EVALESCAPESTREEVISITOR_H

#include "TreeVisitor.h"


class EvalEscapesTreeVisitor final : public TreeVisitor {
public:
    using EvalEscape = std::function<const Value(Object&)>;
    EvalEscape evalEscape;

    #define IMPL_VISIT(type) \
    virtual void visit##type (Object& node) override {}
    IMPL_VISIT( Program              )          IMPL_VISIT( Stmts                     )
    IMPL_VISIT( Stmt                 )          IMPL_VISIT( Break                     )
    IMPL_VISIT( Continue             )          IMPL_VISIT( Expr                      )
    IMPL_VISIT( ArithExpr            )          IMPL_VISIT( RelExpr                   )
    IMPL_VISIT( BoolExpr             )          IMPL_VISIT( Term                      )
    IMPL_VISIT( TermParensExpr       )          IMPL_VISIT( TermMinusExpr             )
    IMPL_VISIT( TermNotExpr          )          IMPL_VISIT( TermPlusPlusLvalue        )
    IMPL_VISIT( TermMinusMinusLvalue )          IMPL_VISIT( TermLvaluePlusPlus        )
    IMPL_VISIT( TermLvalueMinusMinus )          IMPL_VISIT( AssignExpr                )
    IMPL_VISIT( Primary              )          IMPL_VISIT( LvalueId                  )
    IMPL_VISIT( LvalueGlobalId       )          IMPL_VISIT( LvalueLocalId             )
    IMPL_VISIT( LvalueMember         )          IMPL_VISIT( MemberId                  )
    IMPL_VISIT( MemberExpr           )          IMPL_VISIT( Call                      )
    IMPL_VISIT( MultiCall            )          IMPL_VISIT( FdefCall                  )
    IMPL_VISIT( NormCallSuffix       )          IMPL_VISIT( MethodCallSuffix          )
    IMPL_VISIT( NormCall             )          IMPL_VISIT( MethodCall                )
    IMPL_VISIT( Elist                )          IMPL_VISIT( ElistNotEmpty             )
    IMPL_VISIT( ObjectDef            )          IMPL_VISIT( ObjectDinnerObjElistnotempty )
    IMPL_VISIT( ObjectDinnerIndexed  )          IMPL_VISIT( CommaIndexed              )
    IMPL_VISIT( IndexedElem          )          IMPL_VISIT( Block                     )
    IMPL_VISIT( FuncDef              )          IMPL_VISIT( FuncPrefix                )
    IMPL_VISIT( FuncName             )          IMPL_VISIT( Const                     )
    IMPL_VISIT( ConstNumconst        )          IMPL_VISIT( ConstStringconst          )
    IMPL_VISIT( ConstBoolconst       )          IMPL_VISIT( ConstNil                  )
    IMPL_VISIT( ID                   )          IMPL_VISIT( CommaIdList               )
    IMPL_VISIT( IfPrefix             )          IMPL_VISIT( ElsePrefix                )
    IMPL_VISIT( IfStmt               )          IMPL_VISIT( IfStmtElseStmt            )
    IMPL_VISIT( WhileStart           )          IMPL_VISIT( WhileCond                 )
    IMPL_VISIT( WhileStmt            )          IMPL_VISIT( ForPrefix                 )
    IMPL_VISIT( ReturnStmt           )          IMPL_VISIT( ReturnStmtExpr            )
    IMPL_VISIT( ForStmt              )          IMPL_VISIT( Argument                  )
    IMPL_VISIT( Formal               )          IMPL_VISIT( ObjElistNotEmpty          )
    IMPL_VISIT( QuasiQuotes          )          IMPL_VISIT( QuotedRules               )
    IMPL_VISIT( Inline               )          IMPL_VISIT( Unparsed                  )
    IMPL_VISIT( CompiledString       )          IMPL_VISIT( ValueStorage              )
    #undef IMPL_VISIT

    virtual void visitEscapeId(Object& node) override {
        evalEscape(node);
    }
    virtual void visitEscapeExpr(Object& node) override {
        evalEscape(node);
    }
    virtual TreeVisitor* Clone(void) const override {
        return new EvalEscapesTreeVisitor();
    }
   
    ~EvalEscapesTreeVisitor() {}
};


#endif 