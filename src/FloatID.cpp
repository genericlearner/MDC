#include "FloatID.h"
#include <sstream>
#include "Visitor.h"

void FloatID::accept(Visitor* visitor, bool depthSearch) {

	visitor->visit(this);
}
FloatID::FloatID(Token t):TokenAST(t){}

std::string FloatID::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "float: " + getToken().getLexeme() + " (" + ss.str() + ")";
}