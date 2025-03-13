#include "intLit.h"
#include <sstream>
IntLit::IntLit(Token t) : TokenAST(t) {}

std::string IntLit::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "integer: " + getLexeme() + " (" + ss.str() + ")";
}