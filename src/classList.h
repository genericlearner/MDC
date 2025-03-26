#pragma once
#include "CompositeConcept.h"

class ClassList : public CompositeConceptAST {
public:
	ClassList(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
