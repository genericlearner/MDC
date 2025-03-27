#include "Multiply.h"
#include "Visitor.h"

void Multiply::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Multiply::Multiply(Token t):CompositeConceptTokenAST(t){}