#pragma once
#include "compositeConceptToken.h"

class Or : public CompositeConceptTokenAST {
public:
	Or(Token t);
	//virtual std::string toString() override;
};