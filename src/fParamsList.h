#pragma once
#include "CompositeConcept.h"

class fParamsList : public CompositeConceptAST
{
public:
	fParamsList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};