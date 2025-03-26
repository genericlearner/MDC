#include "LessThanOrEQTO.h"
#include "Visitor.h"

void LessThanOrEqTo::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
LessThanOrEqTo::LessThanOrEqTo(Token t):CompositeConceptTokenAST(t){}