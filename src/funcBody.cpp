#include "funcBody.h"
#include "Visitor.h"

void FuncBody::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
FuncBody::FuncBody(compositeConcept cc) : CompositeConceptAST(cc) {}