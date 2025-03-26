#pragma once
#include "CompositeConcept.h"

class Variable : public CompositeConceptAST {
public:
	Variable(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;


};