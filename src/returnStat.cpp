#include "returnStat.h"
#include "Visitor.h"

void ReturnStat::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ReturnStat::ReturnStat(compositeConcept cc) : CompositeConceptAST(cc) {}