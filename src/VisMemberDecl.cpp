#include "visMemberDecl.h"
#include "Visitor.h"

void VisMemberDecl::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
VisMemberDecl::VisMemberDecl(compositeConcept cc) : CompositeConceptAST(cc) {}