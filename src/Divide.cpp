#include "Divide.h"
#include "Visitor.h"

void Divide::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Divide::Divide(Token t):CompositeConceptTokenAST(t){}