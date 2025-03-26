#pragma once
#include "CompositeConcept.h"

class StatementList : public CompositeConceptAST {
public:
	StatementList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
