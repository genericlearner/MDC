#include "fParams.h"
#include "Visitor.h"
fParams::fParams(compositeConcept cc) : CompositeConceptAST(cc) {}

void fParams::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
