#include "floatLit.h"
#include <sstream>
#include "Visitor.h"

void FloatLit::accept(Visitor* visitor, bool depthSearch) {
	
	visitor->visit(this);
}
FloatLit::FloatLit(Token t) : TokenAST(t) {}

std::string FloatLit::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "float: " + getToken().getLexeme() + " (" + ss.str() + ")";
}