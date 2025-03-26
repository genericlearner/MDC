#include "relOp.h"
#include "Visitor.h"

void RelOp::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
RelOp::RelOp(compositeConcept cc) : CompositeConceptAST(cc) {}