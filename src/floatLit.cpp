#include "floatLit.h"
#include <sstream>

FloatLit::FloatLit(Token t) : TokenAST(t) {}

std::string FloatLit::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "float: " + getToken().getLexeme() + " (" + ss.str() + ")";
}