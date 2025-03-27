#include "GreaterThanOrEQTO.h"
#include "Visitor.h"

void GreaterThanOrEqTo::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
GreaterThanOrEqTo::GreaterThanOrEqTo(Token t):CompositeConceptTokenAST(t){}