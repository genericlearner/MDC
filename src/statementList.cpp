#include "statementlist.h"

#include "Visitor.h"

void StatementList::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
StatementList::StatementList(compositeConcept cc) : CompositeConceptAST(cc) {}