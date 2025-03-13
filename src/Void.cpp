#include "Void.h"
#include <sstream>

Void::Void(Token t): TokenAST(t){}

std::string Void::toString() {
	std::stringstream ss;
	ss << (void const*)this;
	return getLexeme() + "(" + ss.str() + ")";
}
