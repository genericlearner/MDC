#pragma once
#include "CompositeConcept.h"

class Indice : public CompositeConceptAST {
public:
	Indice(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};