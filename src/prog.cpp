#include "prog.h"
#include "Visitor.h"

void Prog::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Prog::Prog(compositeConcept cc) : CompositeConceptAST(cc) {}