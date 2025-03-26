#include "localVarDeclList.h"
#include "Visitor.h"

void LocalVarDeclList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
LocalVarDeclList::LocalVarDeclList(compositeConcept cc) : CompositeConceptAST(cc) {}