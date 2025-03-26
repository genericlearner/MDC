#pragma once
#include "compositeConceptToken.h"

class Divide : public  CompositeConceptTokenAST{
public:
	Divide(Token t);
	//virtual std::string toString() override;
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};