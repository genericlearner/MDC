#include "extraExpr.h"
#include "Visitor.h"

void ExtraExpr::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ExtraExpr::ExtraExpr(compositeConcept cc) : CompositeConceptAST(cc) {}