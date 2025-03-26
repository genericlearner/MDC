#pragma once

#include "CompositeConcept.h"

class Sign : public CompositeConceptAST {
public:
	Sign(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
