#include "funcDefList.h"
#include "Visitor.h"

void FuncDefList::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
FuncDefList::FuncDefList(compositeConcept cc) : CompositeConceptAST(cc) {}