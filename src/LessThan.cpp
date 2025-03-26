#include "LessThan.h"
#include "Visitor.h"

void LessThan::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
LessThan::LessThan(Token t):CompositeConceptTokenAST(t){}