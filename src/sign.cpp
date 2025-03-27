#include "sign.h"
#include "Visitor.h"

void Sign::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Sign::Sign(compositeConcept cc) : CompositeConceptAST(cc) {}