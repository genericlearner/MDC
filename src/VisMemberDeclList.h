#pragma once
#include "CompositeConcept.h"

class VisMemberDeclList : public CompositeConceptAST {
public:
	VisMemberDeclList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
