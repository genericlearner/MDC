#include "funcDefList.h"
#include "Visitor.h"

void FuncDefList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
FuncDefList::FuncDefList(compositeConcept cc) : CompositeConceptAST(cc) {}