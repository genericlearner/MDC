#include "prog.h"
#include "Visitor.h"

void Prog::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Prog::Prog(compositeConcept cc) : CompositeConceptAST(cc) {}