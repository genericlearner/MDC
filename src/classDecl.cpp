#include "classDecl.h"
#include "Visitor.h"

void ClassDecl::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ClassDecl::ClassDecl(compositeConcept cc) : CompositeConceptAST(cc) {}