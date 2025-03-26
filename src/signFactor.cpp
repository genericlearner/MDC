#include "signFactor.h"
#include "Visitor.h"

void SignFactor::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
SignFactor::SignFactor(compositeConcept cc) : CompositeConceptAST(cc) {}