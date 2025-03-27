#include "isa.h"
#include "Visitor.h"

void ISA::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ISA::ISA(compositeConcept cc) : CompositeConceptAST(cc) {}