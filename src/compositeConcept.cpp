#include "compositeConcept.h"
#include <sstream>

CompositeConceptAST::CompositeConceptAST(compositeConcept cconcept): AST(), concet(cconcept){}

compositeConcept CompositeConceptAST::getConcept() {
	return concet;
}

std::string CompositeConceptAST::toString() {
	std::stringstream ss;
	ss << (void const*)this;

	return EnumeratedDeclarations::compositeConceptToString(concet) + "(" + ss.str() + ")";

}