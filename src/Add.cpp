#include "Add.h"
#include "Visitor.h"
#include <sstream>
void Add::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}

Add::Add(Token t): CompositeConceptTokenAST(t){}

