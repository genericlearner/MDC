#pragma once
#include "AST.h"
#include "parserUtility.h"
#include <string>

class CompositeConceptAST :public AST {
	compositeConcept cc;
public:
	CompositeConceptAST(compositeConcept cc);
	std::string toString();
	compositeConcept getConcept();

};