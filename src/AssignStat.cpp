#include "AssignStat.h"
#include "Visitor.h"

void AssignStat::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
AssignStat::AssignStat(compositeConcept cc) : CompositeConceptAST(cc) {}