#pragma once
#include "CompositeConcept.h"

class ExtraExpr : public CompositeConceptAST {
public:
	ExtraExpr(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
