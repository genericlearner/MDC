#include "compositeConcept.h"
#include <sstream>

CompositeConceptAST::CompositeConceptAST(compositeConcept cconcept): AST(), concept(cconcept){}

compositeConcept CompositeConceptAST::getConcept() {
	return concept;
}

std::string CompositeConceptAST::toString() {
	std::stringstream ss;
	ss << (void const*)this;

	return EnumeratedDeclarations::compositeConceptToString(concept) + "(" + ss.str() + ")";

}