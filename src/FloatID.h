#pragma once
#include "compositeConceptToken.h"

class FloatID : public CompositeConceptTokenAST {
public:
	FloatID(Token t);
	virtual std::string toString() override;
};