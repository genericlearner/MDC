#include "CompositeConcept.h"
#include <sstream>

CompositeConceptAST::CompositeConceptAST(compositeConcept cconcept): AST(), concept(cconcept){}

compositeConcept CompositeConceptAST::getConcept() {
	return concept;
}
void CompositeConceptAST::accept(Visitor* visitor, bool depthSearch) {
	if (depthSearch) {
		AST* child = leftMostChild;

		while (child != nullptr) {
			child->accept(visitor);
			child = child->rightSibling;
		}
	}
}


std::string CompositeConceptAST::toString() {
	std::stringstream ss;
	ss << (void const*)this;

	return EnumeratedDeclarations::compositeConceptToString(concept) + "(" + ss.str() + ")";

}


