#pragma once
#include "CompositeConcept.h"

class ClassImplFunc : public CompositeConceptAST {
public:
	ClassImplFunc(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};