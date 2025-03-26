#pragma once
#include "CompositeConcept.h"

class LocalVarDeclList : public CompositeConceptAST {
public:
	LocalVarDeclList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
