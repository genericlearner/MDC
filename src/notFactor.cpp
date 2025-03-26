#include "notFactor.h"
#include "Visitor.h"

void NotFactor::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
NotFactor::NotFactor(compositeConcept cc) : CompositeConceptAST(cc) {}