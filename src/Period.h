#pragma once
#include "CompositeConceptToken.h"

class Period : public CompositeConceptTokenAST {
public:
	Period(Token t);
	//virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};