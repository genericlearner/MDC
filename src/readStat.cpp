#include "readStat.h"
#include "Visitor.h"

void ReadStat::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ReadStat::ReadStat(compositeConcept cc) : CompositeConceptAST(cc) {}