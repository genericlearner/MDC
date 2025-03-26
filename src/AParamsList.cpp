#include "APaaramsList.h"
#include "Visitor.h"
#include <sstream>
void AParamsList::accept(Visitor* visitor, bool depthSearch) {
	visitor->visit(this);
}
AParamsList::AParamsList(compositeConcept cc):CompositeConceptAST(cc){}