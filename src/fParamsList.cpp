#include "fParamsList.h"
#include "Visitor.h"

void fParamsList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
fParamsList::fParamsList(compositeConcept cc) : CompositeConceptAST(cc) {}