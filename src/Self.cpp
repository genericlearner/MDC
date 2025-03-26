#include "Self.h"
#include <sstream>
#include "Visitor.h"

void Self::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Self::Self(Token t):TokenAST(t){}

std::string Self::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "ID: " + getLexeme() + " (" + ss.str() + ")";
}