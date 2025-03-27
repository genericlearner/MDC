#include "visMemberDeclList.h"
#include "Visitor.h"

void VisMemberDeclList::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
VisMemberDeclList::VisMemberDeclList(compositeConcept cc) : CompositeConceptAST(cc) {}