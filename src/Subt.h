#pragma once
#include "compositeConceptToken.h"

class Subt : public CompositeConceptTokenAST {
public:
	Subt(Token t);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};