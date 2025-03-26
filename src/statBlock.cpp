#include "statBlock.h"
#include "Visitor.h"

void StatBlock::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
StatBlock::StatBlock(compositeConcept cc) : CompositeConceptAST(cc) {}