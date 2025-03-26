#include "relExpr.h"
#include "Visitor.h"

void RelExpr::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
RelExpr::RelExpr(compositeConcept cc) : CompositeConceptAST(cc) {}