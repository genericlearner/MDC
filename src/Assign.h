#pragma once
#include "compositeConceptToken.h"

class Assign : public CompositeConceptTokenAST {
public:
	Assign(Token token);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};