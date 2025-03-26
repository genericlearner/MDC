#pragma once
#include "compositeConceptToken.h"

class Not : public CompositeConceptTokenAST {
public:
	Not(Token t);
	//virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};