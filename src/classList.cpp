#include "classList.h"
#include "Visitor.h"

void ClassList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ClassList::ClassList(compositeConcept cc) : CompositeConceptAST(cc) {}