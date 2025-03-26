#include "implDeflist.h"
#include "Visitor.h"

void ImplDefList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}

ImplDefList::ImplDefList(compositeConcept cc) : CompositeConceptAST(cc) {}