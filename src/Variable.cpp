#include "Variable.h"
#include "Visitor.h"

void Variable::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Variable::Variable(compositeConcept cc) : CompositeConceptAST(cc) {}