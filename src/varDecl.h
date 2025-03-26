#pragma once
#include "CompositeConcept.h"

class VarDecl : public CompositeConceptAST {
public:
	VarDecl(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
