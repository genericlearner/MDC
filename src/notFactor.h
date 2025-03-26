#pragma once
#include "CompositeConcept.h"

class NotFactor : public CompositeConceptAST {
public:
	NotFactor(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
