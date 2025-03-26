#pragma once
#include "CompositeConcept.h"

class SignFactor : public CompositeConceptAST {
public:
	SignFactor(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
