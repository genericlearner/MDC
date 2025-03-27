#include "funcHead.h"
#include "Visitor.h"

void FuncHead::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
FuncHead::FuncHead(compositeConcept cc) : CompositeConceptAST(cc) {}