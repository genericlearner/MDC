#pragma once
#include "CompositeConcept.h"

class RelOp : public CompositeConceptAST {
public:
	RelOp(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
