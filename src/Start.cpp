#include "Start.h"
#include "Visitor.h"

void Start::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Start::Start(compositeConcept cc): CompositeConceptAST(cc){}