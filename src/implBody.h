#pragma once
#include "CompositeConcept.h"

class ImplBody : public CompositeConceptAST {
public:
	ImplBody(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
