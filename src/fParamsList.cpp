#include "fParamsList.h"
#include "Visitor.h"

void fParamsList::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
fParamsList::fParamsList(compositeConcept cc) : CompositeConceptAST(cc) {}