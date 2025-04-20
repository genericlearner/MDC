#include "parserUtility.h"
#include <string>

std::string EnumeratedDeclarations::compositeConceptToString(compositeConcept cc) {
	std::string str;
    switch (cc) {
    case compositeConcept::START:
        str = "START";
        break;
    case compositeConcept::CLASSIMPLFUNC:
        str = "CLASSIMPLFUNC";
        break;
    case compositeConcept::CLASSIMPLFUNCLIST:
        str = "CLASSIMPLFUNCLIST";
        break;
    case compositeConcept::PROG:
        str = "PROG";
        break;
    case compositeConcept::CLASSLIST:
        str = "CLASSLIST";
        break;
    case compositeConcept::IMPLDEFLIST:
        str = "IMPLDEFLIST";
        break;
    case compositeConcept::FUNCDEFLIST:
        str = "FUNCDEFLIST";
        break;
    case compositeConcept::CLASSDECL:
        str = "CLASSDECL";
        break;
    case compositeConcept::IMPLDEF:
        str = "IMPLDEF";
        break;
    case compositeConcept::FUNCDEF:
        str = "FUNCDEF";
        break;
    case compositeConcept::ISALIST:
        str = "ISALIST";
        break;
    case compositeConcept::MEMBERLIST:
        str = "MEMBERLIST";
        break;
    case compositeConcept::ISA:
        str = "ISA";
        break;
    case compositeConcept::VISIBILITY:
        str = "VISIBILITY";
        break;
    case compositeConcept::VISMEMBERDECLLIST:
        str = "VISMEMBERDECLLIST";
        break;
    case compositeConcept::VISMEMBERDECL:
        str = "VISMEMBERDECL";
        break;
    case compositeConcept::MEMDECL:
        str = "MEMDECL";
        break;
    case compositeConcept::IMPLBODYLIST:
        str = "IMPLBODYLIST";
        break;
    case compositeConcept::IMPLBODY:
        str = "IMPLBODY";
        break;
    case compositeConcept::ATTRDECL:
        str = "ATTRDECL";
        break;
    case compositeConcept::FUNCDECL:
        str = "FUNCDECL";
        break;
    case compositeConcept::FUNCHEAD:
        str = "FUNCHEAD";
        break;
    case compositeConcept::FUNCBODY:
        str = "FUNCBODY";
        break;
    case compositeConcept::FPARAMSLIST:
        str = "FPARAMSLIST";
        break;
    case compositeConcept::VARDECL:
        str = "VARDECL";
        break;
    case compositeConcept::STATEMENTLIST:
        str = "STATEMENTLIST";
        break;
    case compositeConcept::LOCALVARDECLORSTATLIST:
        str = "LOCALVARDECLORSTATLIST";
        break;
    case compositeConcept::LOCALVARDECL:
        str = "LOCALVARDECL";
        break;
    case compositeConcept::TYPE:
        str = "TYPE";
        break;
    case compositeConcept::STATEMENT:
        str = "STATEMENT";
        break;
    case compositeConcept::IFSTAT:
        str = "IFSTAT";
        break;
    case compositeConcept::READSTAT:
        str = "READSTAT";
        break;
    case compositeConcept::RETURNSTAT:
        str = "RETURNSTAT";
        break;
    case compositeConcept::WHILESTAT:
        str = "WHILESTAT";
        break;
    case compositeConcept::WRITESTAT:
        str = "WRITESTAT";
        break;
    case compositeConcept::FUNCALLORASSIGNSTAT:
        str = "FUNCALLORASSIGNSTAT";
        break;
    case compositeConcept::STATBLOCK:
        str = "STATBLOCK";
        break;
    case compositeConcept::EXPR:
        str = "EXPR";
        break;
    case compositeConcept::VARIABLE:
        str = "VARIABLE";
        break;
    case compositeConcept::RELOP:
        str = "RELOP";
        break;
    case compositeConcept::EXPR2:
        str = "EXPR2";
        break;
    case compositeConcept::ARITHEXPR:
        str = "ARITHEXPR";
        break;
    case compositeConcept::RELEXPR:
        str = "RELEXPR";
        break;
    case compositeConcept::TERM:
        str = "TERM";
        break;
    case compositeConcept::ADDTERMLIST:
        str = "ADDTERMLIST";
        break;
    case compositeConcept::RIGHTRECARITHEXPR:
        str = "RIGHTRECARITHEXPR";
        break;
    case compositeConcept::ADDOP:
        str = "ADDOP";
        break;
    case compositeConcept::SIGN:
        str = "SIGN";
        break;
    case compositeConcept::FACTORLIST:
        str = "FACTORLIST";
        break;
    case compositeConcept::RECTERM:
        str = "RECTERM";
        break;
    case compositeConcept::IDORSELF:
        str = "IDORSELF";
        break;
    case compositeConcept::NOTFACTOR:
        str = "NOTFACTOR";
        break;
    case compositeConcept::SIGNFACTOR:
        str = "SIGNFACTOR";
        break;
    case compositeConcept::FACTOR2:
        str = "FACTOR2";
        break;
    case compositeConcept::VARORFUNCTIONCALLLIST:
        str = "VARORFUNCTIONCALLLIST";
        break;
    case compositeConcept::APARAMSLIST:
        str = "APARAMSLIST";
        break;
    case compositeConcept::APARAMS:
        str = "APARAMS";
        break;
    case compositeConcept::FLOAT_T:
        str = "FLOAT_T";
        break;
    case compositeConcept::INT_T:
        str = "INT_T";
        break;
    case compositeConcept::FPARAMS:
        str = "FPARAMS";
        break;
    case compositeConcept::ASSIGNSTAT:
        str = "ASSIGNSTAT";
        break;
    case compositeConcept::ARRAYSIZELIST:
        str = "INDICELIST";
        break;
    case compositeConcept::ARRAYSIZE:
        str = "ARRAY DIMENSION?";
        break;
    case compositeConcept::INDICELIST:
        str = "INDICELIST";
        break;
    case compositeConcept::INDICE:
        str = "INDICE";
        break;
    case compositeConcept::FUNCCALL:
        str = "FUNCTIONCALL";
        break;
    default:
        str = "UNKNOWN";
        break;
    }
    return str;
}