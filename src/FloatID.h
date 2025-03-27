#pragma once
#include "compositeConceptToken.h"

class FloatID : public TokenAST {
public:
	FloatID(Token t);
	virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};