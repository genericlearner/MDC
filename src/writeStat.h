#pragma once
#include "CompositeConcept.h"

class WriteStat : public CompositeConceptAST {
public:
	WriteStat(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
