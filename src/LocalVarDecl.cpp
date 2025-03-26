#include "localVarDecl.h"
#include "Visitor.h"

void LocalVarDecl::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
LocalVarDecl::LocalVarDecl(compositeConcept cc) : CompositeConceptAST(cc) {}