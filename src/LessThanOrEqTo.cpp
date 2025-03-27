#include "LessThanOrEQTO.h"
#include "Visitor.h"


void LessThanOrEqTo::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
LessThanOrEqTo::LessThanOrEqTo(Token t):CompositeConceptTokenAST(t){}