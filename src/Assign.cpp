#include "Assign.h"
#include "Visitor.h"

void Assign::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Assign::Assign(Token token):CompositeConceptTokenAST(token){}