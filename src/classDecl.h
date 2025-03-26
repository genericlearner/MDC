#pragma once
#include "CompositeConcept.h"

class ClassDecl : public CompositeConceptAST {
public:
	ClassDecl(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
