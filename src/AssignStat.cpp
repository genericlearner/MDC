#include "AssignStat.h"
#include "Visitor.h"

void AssignStat::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
AssignStat::AssignStat(compositeConcept cc) : CompositeConceptAST(cc) {}