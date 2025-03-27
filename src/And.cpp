#include "And.h"
#include "Visitor.h"
#include <sstream>
void And::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
And::And(Token t): CompositeConceptTokenAST(t){}