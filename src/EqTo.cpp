#include "EQTO.h"
#include "Visitor.h"

void EqTo::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
EqTo::EqTo(Token t): CompositeConceptTokenAST(t){}