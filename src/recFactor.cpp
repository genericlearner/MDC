#include "recFactor.h"
#include "Visitor.h"

void RecFactor::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
RecFactor::RecFactor(compositeConcept cc) : CompositeConceptAST(cc) {}