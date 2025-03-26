#include "statementlist.h"

#include "Visitor.h"

void StatementList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
StatementList::StatementList(compositeConcept cc) : CompositeConceptAST(cc) {}