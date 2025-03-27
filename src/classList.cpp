#include "classList.h"
#include "Visitor.h"

void ClassList::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ClassList::ClassList(compositeConcept cc) : CompositeConceptAST(cc) {}