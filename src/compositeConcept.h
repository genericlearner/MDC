#pragma once
#include "AST.h"
#include "parserUtility.h"
#include <string>

class CompositeConceptAST : public AST {
	compositeConcept concept;
public:
	CompositeConceptAST(compositeConcept cconcept);
	std::string toString();
	compositeConcept getConcept();

	virtual void accept(Visitor* visitor, bool depthSearch = true)override;

};