#include "Public.h"
#include <sstream>

Public::Public(Token t): TokenAST(t){}

std::string Public::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "ID: " + getLexeme() + " (" + ss.str() + ")";
}