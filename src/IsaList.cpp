#include "isaList.h"
#include "Visitor.h"

void ISAList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ISAList::ISAList(compositeConcept cc) : CompositeConceptAST(cc) {}