#include "statement.h"
#include "Visitor.h"

void Statement::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Statement::Statement(compositeConcept cc) : CompositeConceptAST(cc) {}