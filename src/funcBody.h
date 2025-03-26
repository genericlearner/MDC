#pragma once
#include "CompositeConcept.h"

class FuncBody : public CompositeConceptAST {
public:
	FuncBody(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
