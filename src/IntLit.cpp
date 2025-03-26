#include "intLit.h"
#include <sstream>
#include "Visitor.h"

void IntLit::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
IntLit::IntLit(Token t) : TokenAST(t) {}

std::string IntLit::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "integer: " + getLexeme() + " (" + ss.str() + ")";
}