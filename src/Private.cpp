#include "Private.h"
#include <sstream>

Private::Private(Token t) :TokenAST(t){}

std::string Private::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "ID: " + getLexeme() + " (" + ss.str() + ")";
}