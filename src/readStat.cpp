#include "readStat.h"
#include "Visitor.h"

void ReadStat::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ReadStat::ReadStat(compositeConcept cc) : CompositeConceptAST(cc) {}