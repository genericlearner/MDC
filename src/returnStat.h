#pragma once
#include "CompositeConcept.h"

class ReturnStat : public CompositeConceptAST {
public:
	ReturnStat(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
