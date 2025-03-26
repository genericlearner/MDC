#pragma once
#include "CompositeConcept.h"

class FuncDefList : public CompositeConceptAST {
public:
	FuncDefList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
