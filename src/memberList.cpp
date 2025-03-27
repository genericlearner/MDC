#include "memberList.h"
#include "Visitor.h"

void MemberList::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
MemberList::MemberList(compositeConcept cc) : CompositeConceptAST(cc) {}