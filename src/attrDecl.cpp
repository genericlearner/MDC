#include "attrDecl.h"
#include "Visitor.h"

void AttrDecl::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
AttrDecl::AttrDecl(compositeConcept cc) : CompositeConceptAST(cc) {}