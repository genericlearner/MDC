#include "GreaterThan.h"
#include "Visitor.h"

void GreaterThan::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
GreaterThan::GreaterThan(Token t):CompositeConceptTokenAST(t){}