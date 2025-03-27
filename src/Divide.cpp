#include "Divide.h"
#include "Visitor.h"

void Divide::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Divide::Divide(Token t):CompositeConceptTokenAST(t){}