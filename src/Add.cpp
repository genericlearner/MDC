#include "Add.h"
#include "Visitor.h"
#include <sstream>
void Add::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}

Add::Add(Token t): CompositeConceptTokenAST(t){}

