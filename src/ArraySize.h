#pragma once
#include "CompositeConcept.h"

class ArraySize : public CompositeConceptAST {
public:
	ArraySize(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};