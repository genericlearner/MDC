#include "writeStat.h"

#include "Visitor.h"

void WriteStat::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
WriteStat::WriteStat(compositeConcept cc) : CompositeConceptAST(cc) {}