#include "Void.h"
#include <sstream>
#include "Visitor.h"

void Void::accept(Visitor* visitor, bool depthSearch) {

	visitor->visit(this);
}
Void::Void(Token t): TokenAST(t){}

std::string Void::toString() {
	std::stringstream ss;
	ss << (void const*)this;
	return getLexeme() + "(" + ss.str() + ")";
}
