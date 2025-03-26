#include "arithExpr.h"
#include "Visitor.h"

void ArithExpr::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ArithExpr::ArithExpr(compositeConcept cc) : CompositeConceptAST(cc) {}