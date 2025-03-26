#pragma once
#include "CompositeConcept.h"

class AttrDecl : public CompositeConceptAST {
public:
	AttrDecl(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
