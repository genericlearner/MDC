#include "statBlock.h"
#include "Visitor.h"

void StatBlock::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
StatBlock::StatBlock(compositeConcept cc) : CompositeConceptAST(cc) {}