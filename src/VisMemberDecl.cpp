#include "visMemberDecl.h"
#include "Visitor.h"

void VisMemberDecl::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
VisMemberDecl::VisMemberDecl(compositeConcept cc) : CompositeConceptAST(cc) {}