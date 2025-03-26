#pragma once
#include "tokenAST.h"

class Public: public TokenAST {
public:
	Public(Token t);
	virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};