#include "visibility.h"
#include "Visitor.h"

void Visibility::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Visibility::Visibility(compositeConcept cc) : CompositeConceptAST(cc) {}