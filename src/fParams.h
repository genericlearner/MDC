#pragma once
#include "CompositeConcept.h"

class fParams : public CompositeConceptAST
{
public:
	fParams(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};