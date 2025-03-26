#pragma once
#include "tokenAST.h"

class IntegerID : public TokenAST {
public:
	IntegerID(Token t);

	virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};