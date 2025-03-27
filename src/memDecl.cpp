#include "memDecl.h"
#include "Visitor.h"

void MemDecl::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
MemDecl::MemDecl(compositeConcept cc) : CompositeConceptAST(cc) {}