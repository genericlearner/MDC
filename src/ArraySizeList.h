#pragma once
#include "CompositeConcept.h"

class ArraySizeList : public CompositeConceptAST {
public:
	ArraySizeList(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};