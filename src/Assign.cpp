#include "Assign.h"
#include "Visitor.h"

void Assign::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Assign::Assign(Token token):CompositeConceptTokenAST(token){}