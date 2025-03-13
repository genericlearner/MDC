#pragma once
#include "compositeConceptToken.h"

class GreaterThanOrEqTo : public CompositeConceptTokenAST {
public:
	GreaterThanOrEqTo(Token t);
	virtual std::string toString() override;
};