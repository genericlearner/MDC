#pragma once
#include "CompositeConcept.h"

class AParamsList : public CompositeConceptAST {
public:
	AParamsList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;


};