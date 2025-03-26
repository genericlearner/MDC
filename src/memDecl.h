#pragma once
#include "CompositeConcept.h"

class MemDecl : public CompositeConceptAST {
public:
	MemDecl(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
