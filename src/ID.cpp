#include "ID.h"
#include <sstream>
ID::ID(Token t):TokenAST(t){}

std::string ID::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "ID: " + getLexeme() + " (" + ss.str() + ")";
}