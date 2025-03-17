#pragma once
#include "AST.h"
#include "parserUtility.h"
#include <string>

class CompositeConceptAST :public AST {
	compositeConcept concet;
public:
	CompositeConceptAST(compositeConcept cconcept);
	std::string toString();
	compositeConcept getConcept();

};