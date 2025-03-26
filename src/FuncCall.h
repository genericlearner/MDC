#pragma once
#include "CompositeConcept.h"

class FuncCall : public CompositeConceptAST {
public:
	FuncCall(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};