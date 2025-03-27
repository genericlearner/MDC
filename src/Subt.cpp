#include "Subt.h"
#include <sstream>
#include "Visitor.h"

void Subt::accept(Visitor* visitor, bool depthSearch) {
	CompositeConceptTokenAST::accept(visitor, depthSearch);
	visitor->visit(this);
}
Subt::Subt(Token t) : CompositeConceptTokenAST(t) {}