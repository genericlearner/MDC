#pragma once

#include "CompositeConcept.h"

class addOp : public CompositeConceptAST {
public:
	addOp(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
