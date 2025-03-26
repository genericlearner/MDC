#pragma once
#include "CompositeConcept.h"

class Term : public CompositeConceptAST {
public:
	Term(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
