#pragma once
#include "compositeConceptToken.h"

class NotEqTo : public CompositeConceptTokenAST {
public:
	NotEqTo(Token t);
	virtual std::string toString() override;
};