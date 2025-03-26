#include "ArraySizeList.h"
#include "Visitor.h"

void ArraySizeList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ArraySizeList::ArraySizeList(compositeConcept cc) : CompositeConceptAST(cc) {}