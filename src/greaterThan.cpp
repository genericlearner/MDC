#include "GreaterThan.h"
#include "Visitor.h"

void GreaterThan::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
GreaterThan::GreaterThan(Token t):CompositeConceptTokenAST(t){}