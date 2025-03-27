#include "EQTO.h"
#include "Visitor.h"

void EqTo::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
EqTo::EqTo(Token t): CompositeConceptTokenAST(t){}