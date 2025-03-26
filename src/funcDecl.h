#pragma once
#include "CompositeConcept.h"

class FuncDecl : public CompositeConceptAST {
public:
	FuncDecl(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
