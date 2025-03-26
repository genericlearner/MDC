#include "ClassImplFuncList.h"
#include "Visitor.h"

void ClassImplFuncList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ClassImplFuncList::ClassImplFuncList(compositeConcept cc) : CompositeConceptAST(cc) {}