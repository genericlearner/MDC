#include "isa.h"
#include "Visitor.h"

void ISA::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
ISA::ISA(compositeConcept cc) : CompositeConceptAST(cc) {}