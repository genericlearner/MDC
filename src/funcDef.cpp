#include "funcDef.h"
#include "Visitor.h"

void FuncDef::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
FuncDef::FuncDef(compositeConcept cc) : CompositeConceptAST(cc) {}