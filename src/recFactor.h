#pragma once
#include "CompositeConcept.h"

class RecFactor : public CompositeConceptAST {
public:
	RecFactor(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
