#include "Indice.h"
#include "Visitor.h"

void Indice::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Indice::Indice(compositeConcept cc) : CompositeConceptAST(cc) {}