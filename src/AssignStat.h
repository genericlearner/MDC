#pragma once

#include "CompositeConcept.h"

class AssignStat : public CompositeConceptAST {
public:
	AssignStat(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
