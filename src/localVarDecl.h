#pragma once
#include "CompositeConcept.h"

class LocalVarDecl : public CompositeConceptAST {
public:
	LocalVarDecl(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
