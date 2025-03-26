#include "FuncCall.h"
#include "Visitor.h"

void FuncCall::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
FuncCall::FuncCall(compositeConcept cc) : CompositeConceptAST(cc) {}