#pragma once
#include "CompositeConcept.h"

class ArithExpr : public CompositeConceptAST {
public:
	ArithExpr(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
