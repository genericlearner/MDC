#pragma once
#include "CompositeConcept.h"

class Expr : public CompositeConceptAST {
public:
	Expr(compositeConcept c);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
