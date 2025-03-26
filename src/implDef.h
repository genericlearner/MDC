#pragma once
#include "CompositeConcept.h"

class ImplDef : public CompositeConceptAST {
public:
	ImplDef(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
