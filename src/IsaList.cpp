#include "isaList.h"
#include "Visitor.h"

void ISAList::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ISAList::ISAList(compositeConcept cc) : CompositeConceptAST(cc) {}