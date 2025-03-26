#pragma once
#include "compositeConceptToken.h"

class Add  : public CompositeConceptTokenAST {
public:
	Add(Token t);
	//virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};