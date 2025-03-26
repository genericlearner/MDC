#pragma once

#include "compositeConceptToken.h"

class And : public CompositeConceptTokenAST {
public:
	And(Token t);
	//virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};