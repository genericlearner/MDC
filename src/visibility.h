#pragma once
#include "CompositeConcept.h"


class Visibility : public CompositeConceptAST {
public:
	Visibility(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
