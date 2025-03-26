#include "compositeConceptToken.h"

CompositeConceptTokenAST::CompositeConceptTokenAST(Token t):TokenAST(t){}
void CompositeConceptTokenAST::accept(Visitor* visitor, bool depthSearch) {
	if (depthSearch) {
		AST* child = leftMostChild;
		while(child != nullptr) {
			child->accept(visitor);
			child = child->rightSibling;
		}
	}
}

std::string CompositeConceptTokenAST::toString() {
	std::stringstream ss;
	ss << (void const*)this;
	return getLexeme() + "(" + ss.str() + ")";
}