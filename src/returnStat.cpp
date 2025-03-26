#include "returnStat.h"
#include "Visitor.h"

void ReturnStat::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ReturnStat::ReturnStat(compositeConcept cc) : CompositeConceptAST(cc) {}