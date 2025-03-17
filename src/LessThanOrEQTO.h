#pragma once
#include "compositeConceptToken.h"

class LessThanOrEqTo: public CompositeConceptTokenAST {
public:
	LessThanOrEqTo(Token t);
	//virtual std::string toString() override;
};