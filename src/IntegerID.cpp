#include "IntegerID.h"
#include <sstream>
IntegerID::IntegerID(Token  t): TokenAST(t){}

std::string IntegerID::toString()
{
	std::stringstream ss;
	ss << "integer ";
	ss << "(" << (void const*)this << ")";
	return ss.str();
}