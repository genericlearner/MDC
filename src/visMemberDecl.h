#pragma once
#include "CompositeConcept.h"

class VisMemberDecl : public CompositeConceptAST {
public:
	VisMemberDecl(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
