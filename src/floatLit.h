#pragma once
#include "tokenAST.h"

class FloatLit : public TokenAST {
public:
	FloatLit(Token t);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
	virtual std::string toString() override;
};
