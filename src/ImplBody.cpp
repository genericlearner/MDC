#include "implBody.h"
#include "Visitor.h"

void ImplBody::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ImplBody::ImplBody(compositeConcept cc) : CompositeConceptAST(cc) {}