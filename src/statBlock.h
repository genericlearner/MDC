#pragma once
#include "CompositeConcept.h"

class StatBlock : public CompositeConceptAST {
public:
	StatBlock(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
