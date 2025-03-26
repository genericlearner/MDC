#include "addTermList.h"
#include "Visitor.h"
#include <sstream>
void addTermList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
addTermList::addTermList(compositeConcept cc) : CompositeConceptAST(cc) {}