#include "IntegerID.h"
#include <sstream>
#include "Visitor.h"

void IntegerID::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
IntegerID::IntegerID(Token  t): TokenAST(t){}

std::string IntegerID::toString()
{
	std::stringstream ss;
	ss << "integer ";
	ss << "(" << (void const*)this << ")";
	return ss.str();
}