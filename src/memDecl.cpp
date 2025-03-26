#include "memDecl.h"
#include "Visitor.h"

void MemDecl::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
MemDecl::MemDecl(compositeConcept cc) : CompositeConceptAST(cc) {}