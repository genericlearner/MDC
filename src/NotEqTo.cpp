#include "NotEQTO.h"
#include "Visitor.h"

void NotEqTo::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
NotEqTo::NotEqTo(Token t):CompositeConceptTokenAST(t){}