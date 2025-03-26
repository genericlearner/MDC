#include "Variable.h"
#include "Visitor.h"

void Variable::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Variable::Variable(compositeConcept cc) : CompositeConceptAST(cc) {}