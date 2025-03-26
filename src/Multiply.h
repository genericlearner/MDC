#pragma once
#include "compositeConceptToken.h"

class Multiply : public CompositeConceptTokenAST {
public:
	Multiply(Token t);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};