#include "fParams.h"
#include "Visitor.h"

void fParams::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
fParams::fParams(compositeConcept cc) : CompositeConceptAST(cc) {}