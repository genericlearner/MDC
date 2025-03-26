#include "addOp.h"
#include "Visitor.h"
#include <sstream>
void addOp::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
addOp::addOp(compositeConcept cc): CompositeConceptAST(cc){}