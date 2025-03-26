#include "attrDecl.h"
#include "Visitor.h"

void AttrDecl::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
AttrDecl::AttrDecl(compositeConcept cc) : CompositeConceptAST(cc) {}