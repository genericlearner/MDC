#include "IndiceList.h"
#include "Visitor.h"

void IndiceList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
IndiceList::IndiceList(compositeConcept cc) : CompositeConceptAST(cc) {}