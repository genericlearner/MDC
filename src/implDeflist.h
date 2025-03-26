#pragma once
#include "CompositeConcept.h"

class ImplDefList : public CompositeConceptAST {
public:
	ImplDefList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
