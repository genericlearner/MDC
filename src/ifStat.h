#pragma once
#include "CompositeConcept.h"

class IfStat : public CompositeConceptAST {
public:
	IfStat(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
