#include "relOp.h"
#include "Visitor.h"

void RelOp::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
RelOp::RelOp(compositeConcept cc) : CompositeConceptAST(cc) {}