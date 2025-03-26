#pragma once
#include "CompositeConcept.h"

class Prog : public CompositeConceptAST {
public:
	Prog(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
