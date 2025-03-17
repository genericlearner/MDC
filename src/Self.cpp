#include "Self.h"
#include <sstream>

Self::Self(Token t):TokenAST(t){}

std::string Self::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "ID: " + getLexeme() + " (" + ss.str() + ")";
}