#include "And.h"
#include "Visitor.h"
#include <sstream>
void And::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
And::And(Token t): CompositeConceptTokenAST(t){}