#pragma once
#include "CompositeConcept.h"

class FuncHead : public CompositeConceptAST {
public:
	FuncHead(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
