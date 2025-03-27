#include "fParams.h"
#include "Visitor.h"

void fParams::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
fParams::fParams(compositeConcept cc) : CompositeConceptAST(cc) {}