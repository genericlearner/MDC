#include "ID.h"
#include <sstream>
#include "Visitor.h"
ID::ID(Token t):TokenAST(t){}
void ID::accept(Visitor* visitor, bool handleDepthSearch)
{
	
	visitor->visit(this);
}
std::string ID::toString()
{
	std::stringstream ss;
	ss << (void const*)this;
	return "ID: " + getLexeme() + " (" + ss.str() + ")";
}