#include "GreaterThanOrEQTO.h"
#include "Visitor.h"

void GreaterThanOrEqTo::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
GreaterThanOrEqTo::GreaterThanOrEqTo(Token t):CompositeConceptTokenAST(t){}