#pragma once
#include "CompositeConcept.h"

class MemberList : public CompositeConceptAST {
public:
	MemberList(compositeConcept cc);
	virtual void accept(Visitor* visitor, bool depthSearch = true)override;
};
