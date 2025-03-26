#include "Not.h"
#include "Visitor.h"

void Not::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Not::Not(Token t):CompositeConceptTokenAST(t){}