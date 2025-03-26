#include "factor.h"	

#include "Visitor.h"

void Factor::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Factor::Factor(compositeConcept cc) : CompositeConceptAST(cc) {}
