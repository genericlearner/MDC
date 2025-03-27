#include "term.h"
#include "Visitor.h"

void Term::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}

Term::Term(compositeConcept cc) : CompositeConceptAST(cc) {}