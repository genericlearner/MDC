#include "Or.h"
#include "Visitor.h"

void Or::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Or::Or(Token t):CompositeConceptTokenAST(t){}