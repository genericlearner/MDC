#pragma once
#include "CompositeConcept.h"

class WhileStat : public CompositeConceptAST {
public:
	WhileStat(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
