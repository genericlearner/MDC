#include "Multiply.h"
#include "Visitor.h"

void Multiply::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Multiply::Multiply(Token t):CompositeConceptTokenAST(t){}