#include "factor.h"	

#include "Visitor.h"

void Factor::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Factor::Factor(compositeConcept cc) : CompositeConceptAST(cc) {}
