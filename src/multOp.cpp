#include "multOp.h"
#include "Visitor.h"

void MultOp::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
MultOp::MultOp(compositeConcept cc) : CompositeConceptAST(cc) {}