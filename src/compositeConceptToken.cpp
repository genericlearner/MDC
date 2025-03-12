#include "compositeConceptToken.h"

CompositeConceptTokenAST::CompositeConceptTokenAST(Token t):TokenAST(t){}

std::string CompositeConceptTokenAST::toString() {
	std::stringstream ss;
	ss << (void const*)this;
	return getLexeme() + "(" + ss.str() + ")";
}