#include "notFactor.h"
#include "Visitor.h"

void NotFactor::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
NotFactor::NotFactor(compositeConcept cc) : CompositeConceptAST(cc) {}