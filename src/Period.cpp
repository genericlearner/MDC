#include "Period.h"
#include "Visitor.h"

void Period::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Period::Period(Token t):CompositeConceptTokenAST(t){}