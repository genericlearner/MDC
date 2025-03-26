#pragma once
#include "CompositeConcept.h"

class Statement : public CompositeConceptAST {
public:
	Statement(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
