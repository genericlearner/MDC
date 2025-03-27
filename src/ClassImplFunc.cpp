#include "ClassImplFunc.h"
#include "Visitor.h"

void ClassImplFunc::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
ClassImplFunc::ClassImplFunc(compositeConcept cc) : CompositeConceptAST(cc) {}