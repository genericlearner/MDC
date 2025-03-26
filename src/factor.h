#pragma once
#include "CompositeConcept.h"

class Factor : public CompositeConceptAST {
public:
	Factor(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
