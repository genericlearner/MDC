#pragma once
#pragma once
#include "CompositeConcept.h"

class ClassImplFuncList : public CompositeConceptAST {
public:
	ClassImplFuncList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};