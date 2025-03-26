#include "ArraySize.h"
#include "Visitor.h"

void ArraySize::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ArraySize::ArraySize(compositeConcept cc) : CompositeConceptAST(cc) {}