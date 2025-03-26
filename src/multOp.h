#pragma once
#include "CompositeConcept.h"

class MultOp : public CompositeConceptAST {
public:
	MultOp(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
