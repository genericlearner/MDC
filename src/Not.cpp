#include "Not.h"
#include "Visitor.h"

void Not::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Not::Not(Token t):CompositeConceptTokenAST(t){}