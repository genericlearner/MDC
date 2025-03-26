#pragma once
#include "CompositeConcept.h"

class FuncDef : public CompositeConceptAST {
public:
	FuncDef(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
