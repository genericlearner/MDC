#include "implDef.h"
#include "Visitor.h"

void ImplDef::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ImplDef::ImplDef(compositeConcept cc) : CompositeConceptAST(cc) {}