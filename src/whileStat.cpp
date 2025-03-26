#include "whileStat.h"

#include "Visitor.h"

void Add::WhileStat(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
WhileStat::WhileStat(compositeConcept cc) : CompositeConceptAST(cc) {}