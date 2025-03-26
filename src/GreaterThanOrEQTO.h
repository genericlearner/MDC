#pragma once
#include "compositeConceptToken.h"

class GreaterThanOrEqTo : public CompositeConceptTokenAST {
public:
	GreaterThanOrEqTo(Token t);
	//virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};