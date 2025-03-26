#pragma once
#include "CompositeConcept.h"

class ISA : public CompositeConceptAST {
public:
	ISA(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
