#include "FloatID.h"
#include <sstream>
FloatID::FloatID(Token t):CompositeConceptTokenAST(t){}

std::string FloatID::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "float: " + getToken().getLexeme() + " (" + ss.str() + ")";
}