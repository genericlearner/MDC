#pragma once
#include "compositeConceptToken.h"

class EqTo : public CompositeConceptTokenAST {
public:
	EqTo(Token t);
	//virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};