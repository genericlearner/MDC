#include "whileStat.h"
#include "Visitor.h"

WhileStat::WhileStat(compositeConcept cc) : CompositeConceptAST(cc) {}
void WhileStat::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
