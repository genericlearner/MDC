#include "Or.h"
#include "Visitor.h"

void Or::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Or::Or(Token t):CompositeConceptTokenAST(t){}