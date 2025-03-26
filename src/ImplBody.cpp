#include "implBody.h"
#include "Visitor.h"

void ImplBody::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ImplBody::ImplBody(compositeConcept cc) : CompositeConceptAST(cc) {}