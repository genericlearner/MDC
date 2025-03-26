#include "multOp.h"
#include "Visitor.h"

void MultOp::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
MultOp::MultOp(compositeConcept cc) : CompositeConceptAST(cc) {}