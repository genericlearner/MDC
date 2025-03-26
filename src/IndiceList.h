#pragma once
#include "CompositeConcept.h"

class IndiceList : public CompositeConceptAST {
public:
	IndiceList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};