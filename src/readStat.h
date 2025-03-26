#pragma once
#include "CompositeConcept.h"

class ReadStat : public CompositeConceptAST {
public:
	ReadStat(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
