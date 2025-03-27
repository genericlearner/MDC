#include "ifStat.h"
#include "Visitor.h"

void IfStat::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
IfStat::IfStat(compositeConcept cc) : CompositeConceptAST(cc) {}