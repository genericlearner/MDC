#pragma once
#include "CompositeConcept.h"

class Start : public CompositeConceptAST {
public:
	Start(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};