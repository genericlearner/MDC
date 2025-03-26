#pragma once
#include "compositeConceptToken.h"

class LessThan : public CompositeConceptTokenAST {
public:
	LessThan(Token t);
	//virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};