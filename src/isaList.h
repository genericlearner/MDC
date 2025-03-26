#pragma once
#include "CompositeConcept.h"

class ISAList : public CompositeConceptAST {
public:
	ISAList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
