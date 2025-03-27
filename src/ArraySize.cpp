#include "ArraySize.h"
#include "Visitor.h"

void ArraySize::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ArraySize::ArraySize(compositeConcept cc) : CompositeConceptAST(cc) {}