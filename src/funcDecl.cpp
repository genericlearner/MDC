#include "funcDecl.h"
#include "Visitor.h"

void FuncDecl::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
FuncDecl::FuncDecl(compositeConcept cc) : CompositeConceptAST(cc) {}