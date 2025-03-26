#include "Public.h"
#include <sstream>
#include "Visitor.h"

void Public::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Public::Public(Token t): TokenAST(t){}

std::string Public::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "ID: " + getLexeme() + " (" + ss.str() + ")";
}