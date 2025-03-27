#include "varDecl.h"
#include "Visitor.h"

void VarDecl::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
VarDecl::VarDecl(compositeConcept cc) : CompositeConceptAST(cc) {}