#pragma once
#include "CompositeConcept.h"

class RelExpr : public CompositeConceptAST {
public:
	RelExpr(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
