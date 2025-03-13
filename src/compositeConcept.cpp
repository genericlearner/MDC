#include "compositeConcept.h"
#include <sstream>

CompositeConceptAST::CompositeConceptAST(compositeConcept cc): AST(), cc(cc){}

compositeConcept CompositeConceptAST::getConcept() {
	return cc;
}

std::string CompositeConceptAST::toString() {
	std::stringstream ss;
	ss << (void const*)this;

	return EnumeratedDeclarations::compositeConceptToString(cc) + "(" + ss.str() + ")";

}