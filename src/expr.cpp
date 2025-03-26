#include "expr.h"
#include "Visitor.h"

void Expr::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Expr::Expr(compositeConcept cc) : CompositeConceptAST(cc) {}