#include "implDeflist.h"
#include "Visitor.h"

void ImplDefList::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}

ImplDefList::ImplDefList(compositeConcept cc) : CompositeConceptAST(cc) {}