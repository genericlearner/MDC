#include "NotEQTO.h"
#include "Visitor.h"

void NotEqTo::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
NotEqTo::NotEqTo(Token t):CompositeConceptTokenAST(t){}