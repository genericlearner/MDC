#include "Private.h"
#include <sstream>
#include "Visitor.h"

void Private::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
Private::Private(Token t) :TokenAST(t){}

std::string Private::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "ID: " + getLexeme() + " (" + ss.str() + ")";
}