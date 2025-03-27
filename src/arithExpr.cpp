#include "arithExpr.h"
#include "Visitor.h"

void ArithExpr::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ArithExpr::ArithExpr(compositeConcept cc) : CompositeConceptAST(cc) {}