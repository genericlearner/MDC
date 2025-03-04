#include "parser.h"


Parser::Parser(std::ifstream& source, std::ostream& outDerivation, std::ofstream& syntaxErrors, Lexer& lexer)
    :source(source), outDerivation(outDerivation), syntaxErrors(syntaxErrors), lexer(lexer) {

    firstSet["START"] = { {TokenType::FUNCTION, TokenType::CONSTRUCTOR, TokenType::IMPLEMENTATION, TokenType::CLASS} };
    firstSet["PROG"] = { {TokenType::FUNCTION, TokenType::CONSTRUCTOR, TokenType::IMPLEMENTATION, TokenType::CLASS} };
    firstSet["CLASSIMPLFUNC"] = { {TokenType::CLASS}, {TokenType::IMPLEMENTATION}, {TokenType::FUNCTION, TokenType::CONSTRUCTOR} };
    firstSet["CLASSDECL"] = { {TokenType::CLASS} };
    firstSet["VISMEMBERDECL"] = { {TokenType::PRIVATE, TokenType::PUBLIC} };
    firstSet["ISA1"] = { {TokenType::ISA} };
    firstSet["ISA2"] = { {TokenType::COMMA} }; 
    firstSet["IMPLDEF"] = { {TokenType::IMPLEMENTATION} };
    firstSet["IMPLBODY"] = { {TokenType::FUNCTION, TokenType::CONSTRUCTOR} };
    firstSet["FUNCDEF"] = { {TokenType::FUNCTION, TokenType::CONSTRUCTOR} };
    firstSet["VISIBILITY"] = { {TokenType::PUBLIC},{TokenType::PRIVATE} };
    firstSet["MEMDECL"] = { {TokenType::FUNCTION, TokenType::CONSTRUCTOR}, {TokenType::ATTRIBUTE} };
    firstSet["FUNCDECL"] = { {TokenType::FUNCTION, TokenType::CONSTRUCTOR} };
    firstSet["FUNCHEAD"] = { {TokenType::CONSTRUCTOR}, {TokenType::FUNCTION} };
    firstSet["FUNCBODY"] = { {TokenType::OPENCURLY} };
    firstSet["LOCALVARDECLORSTAT"] = { {TokenType::LOCAL} , {TokenType::IF, TokenType::READ, TokenType::RETURN, TokenType::WHILE, TokenType::WRITE, TokenType::ID,
        TokenType::SELF}  };
    firstSet["LOCALVARDECLORSTAT2"] = { {TokenType::IF, TokenType::READ, TokenType::RETURN, TokenType::WHILE, TokenType::WRITE, TokenType::ID,
        TokenType::SELF, TokenType::LOCAL} };
    firstSet["ATTRDECL"] = { {TokenType::ATTRIBUTE} };
    firstSet["LOCALVARDECL"] = { {TokenType::LOCAL} };
    firstSet["VARDECL"] = { {TokenType::ID} };
    firstSet["STATEMENT"] = { {TokenType::ID, TokenType::SELF}, {TokenType::WRITE}, {TokenType::WHILE}, {TokenType::RETURN}, {TokenType::READ},
        {TokenType::IF} };
    firstSet["FUNCALLORASSIGN"] = { {TokenType::ID, TokenType::SELF} };
    firstSet["FUNCALLORASSIGN2"] = { {TokenType::OPENSQUARE, TokenType::DOT, TokenType::ASSIGN}, {TokenType::OPENPAR} };
    firstSet["FUNCALLORASSIGN3"] = { {TokenType::ASSIGN}, {TokenType::DOT} };
    firstSet["FUNCALLORASSIGN4"] = { {TokenType::DOT} };
    firstSet["STATBLOCK"] = { {TokenType::IF, TokenType::READ, TokenType::RETURN, TokenType::WHILE, TokenType::WRITE, TokenType::ID,
        TokenType::SELF}, {TokenType::OPENCURLY} };
    firstSet["STATEMENTS"] = { {TokenType::IF, TokenType::READ, TokenType::RETURN, TokenType::WHILE, TokenType::WRITE, TokenType::ID,
        TokenType::SELF} };
    firstSet["EXPR"] = { {TokenType::OPENPAR, TokenType::INTEGER_VAL, TokenType::FLOAT_VAL, TokenType::NOT, TokenType::ID, TokenType::SELF,
        TokenType::SUBT, TokenType::ADD} };
    firstSet["EXPR2"] = { {TokenType::EQ, TokenType::GT, TokenType::GTEQ, TokenType::LT, TokenType::LTEQ, TokenType::NOTEQ} };
    firstSet["RELEXPR"] = { {TokenType::OPENPAR, TokenType::INTEGER_VAL, TokenType::FLOAT_VAL, TokenType::NOT, TokenType::ID, TokenType::SELF,
        TokenType::SUBT, TokenType::ADD} };
    firstSet["ARITHEXPR"] = { {TokenType::OPENPAR, TokenType::INTEGER_VAL, TokenType::FLOAT_VAL, TokenType::NOT, TokenType::ID, TokenType::SELF,
       TokenType::SUBT, TokenType::ADD} };
    firstSet["RIGHTRECARITHEXPR"] = { {TokenType::SUBT, TokenType::OR, TokenType::ADD} };
    firstSet["SIGN"] = { {TokenType::ADD}, {TokenType::SUBT} };
    firstSet["TERM"] = { {TokenType::OPENPAR, TokenType::INTEGER_VAL, TokenType::FLOAT_VAL, TokenType::NOT, TokenType::ID, TokenType::SELF,
        TokenType::SUBT, TokenType::ADD} };
    firstSet["RIGHTRECTERM"] = { {TokenType::MULT, TokenType::DIV, TokenType::AND} };
    firstSet["FACTOR"] = { {TokenType::SUBT, TokenType::ADD}, {TokenType::ID, TokenType::SELF}, {TokenType::NOT}, {TokenType::INTEGER_VAL}, {TokenType::FLOAT_VAL},
        {TokenType::OPENPAR} };
    //epsilon?
    firstSet["FACTOR2"] = { {TokenType::OPENSQUARE}, {TokenType::OPENPAR} };
    firstSet["INDICES"] = { {TokenType::OPENSQUARE} };
    firstSet["REPTVARIABLEORFUNCTIONCALL"] = { {TokenType::DOT} };
    firstSet["VARIABLE"] = { {TokenType::ID, TokenType::SELF} };
    firstSet["VARIABLE2"] = { {TokenType::OPENSQUARE, TokenType::DOT}, {TokenType::OPENPAR} };
    firstSet["REPTVARIABLE"] = { {TokenType::DOT} };
    firstSet["VARIDNEST"] = { {TokenType::DOT} };
    firstSet["VARIDNEST2"] = { {TokenType::OPENSQUARE}, {TokenType::OPENPAR} };
    firstSet["INDICE"] = { {TokenType::OPENSQUARE} };
    firstSet["IDNEST"] = { {TokenType::DOT} };
    firstSet["IDNEST2"] = { {TokenType::OPENSQUARE},{TokenType::OPENPAR} };
    firstSet["ARRAYSIZE"] = { {TokenType::OPENSQUARE} };
    firstSet["ARRAYSIZE2"] = { {TokenType::CLOSESQUARE}, {TokenType::INTEGER_VAL} };
    firstSet["ARRAYSIZES"] = { {TokenType::OPENSQUARE} };
    firstSet["TYPE"] = { {TokenType::INT_T}, {TokenType::ID}, {TokenType::FLOAT_T} };
    firstSet["RETURNTYPE"] = { {TokenType::INT_T, TokenType::ID, TokenType::FLOAT_T}, {TokenType::VOID} };
    firstSet["APARAMS"] = { {TokenType::OPENPAR, TokenType::INTEGER_VAL, TokenType::FLOAT_VAL, TokenType::NOT, TokenType::ID, TokenType::SELF,
        TokenType::SUBT, TokenType::ADD} };
    firstSet["REPTAPARAMS1"] = { {TokenType::COMMA} };
    firstSet["APARAMSTAIL"] = { {TokenType::COMMA} };
    firstSet["FPARAMS"] = { {TokenType::ID} };
    firstSet["REPTFPARAMS1"] = { {TokenType::COMMA} };
    firstSet["FPARAMSTAIL"] = { {TokenType::COMMA} };
    firstSet["ASSIGNOP"] = { {TokenType::ASSIGN} };
    firstSet["RELOP"] = { {TokenType::NOTEQ}, {TokenType::LTEQ}, {TokenType::LT}, {TokenType::GTEQ},{TokenType::GT}, {TokenType::EQ} };
    firstSet["ADDOP"] = { {TokenType::ADD}, {TokenType::OR}, {TokenType::SUBT} };
    firstSet["MULTOP"] = { {TokenType::AND}, {TokenType::DIV}, {TokenType::MULT} };
    firstSet["IDORSELF"] = { {TokenType::SELF}, {TokenType::ID} };


    followSet["START"] = { {TokenType::ENDOFILE} };
    followSet["PROG"] = { {TokenType::ENDOFILE} };
    followSet["VISMEMBERDECL"] = { {TokenType::CLOSECURLY} };
    followSet["ISA1"] = { {TokenType::OPENCURLY} };
    followSet["ISA2"] = { {TokenType::OPENCURLY} };
    followSet["IMPLBODY"] = { {TokenType::CLOSECURLY} };
    followSet["LOCALVARDECLORSTAT2"] = { {TokenType::CLOSECURLY} };
    followSet["FUNCALLORASSIGN4"] = { {TokenType::SEMICOLON} };
    followSet["STATBLOCK"] = { {TokenType::ELSE, TokenType::SEMICOLON} };
    followSet["STATEMENTS"] = { {TokenType::CLOSECURLY} };
    followSet["EXPR2"] = { {TokenType::CLOSEPAR, TokenType::SEMICOLON, TokenType::COMMA} };
    followSet["RIGHTRECARITHEXPR"] = { {TokenType::CLOSEPAR, TokenType::SEMICOLON, TokenType::COMMA, TokenType::EQ, TokenType::EQ,
        TokenType::GT, TokenType::GTEQ, TokenType::LT, TokenType::LTEQ, TokenType::NOTEQ, TokenType::CLOSESQUARE} };
    followSet["RIGHTRECTERM"] = { {TokenType::CLOSEPAR, TokenType::SEMICOLON, TokenType::COMMA, TokenType::EQ, TokenType::EQ,
        TokenType::GT, TokenType::GTEQ, TokenType::LT, TokenType::LTEQ, TokenType::NOTEQ, TokenType::CLOSESQUARE, TokenType::SUBT, TokenType::OR,
        TokenType::ADD} };
    followSet["FACTOR2"] = { {TokenType::CLOSEPAR, TokenType::SEMICOLON, TokenType::COMMA, TokenType::EQ, TokenType::GT,
        TokenType::GTEQ, TokenType::LT, TokenType::LTEQ, TokenType::NOTEQ, TokenType::CLOSESQUARE, TokenType::SUBT, TokenType::OR,
        TokenType::ADD, TokenType::MULT, TokenType::DIV, TokenType::AND, TokenType::DOT} };
    followSet["INDICES"] = { {TokenType::ASSIGN, TokenType::CLOSEPAR, TokenType::SEMICOLON, TokenType::COMMA, TokenType::EQ, TokenType::GT,
        TokenType::GTEQ, TokenType::LT, TokenType::LTEQ, TokenType::NOTEQ, TokenType::CLOSESQUARE, TokenType::SUBT, TokenType::OR,
        TokenType::ADD, TokenType::MULT, TokenType::DIV, TokenType::AND, TokenType::DOT} };
    followSet["REPTVARIABLEORFUNCTIONCALL"] = { {TokenType::CLOSEPAR, TokenType::SEMICOLON, TokenType::COMMA, TokenType::EQ, TokenType::GT,
        TokenType::GTEQ, TokenType::LT, TokenType::LTEQ, TokenType::NOTEQ, TokenType::CLOSESQUARE, TokenType::SUBT, TokenType::OR,
        TokenType::ADD, TokenType::MULT, TokenType::DIV, TokenType::AND} };
    followSet["VARIABLE2"] = { {TokenType::CLOSEPAR} };
    followSet["REPTVARIABLE"] = { {TokenType::CLOSEPAR} };
    followSet["VARIDNEST2"] = { {TokenType::CLOSEPAR, TokenType::DOT} };
    followSet["ARRAYSIZES"] = { {TokenType::SEMICOLON, TokenType::CLOSEPAR, TokenType::COMMA} };
    followSet["APARAMS"] = { {TokenType::CLOSEPAR} };
    followSet["REPTAPARAMS1"] = { {TokenType::CLOSEPAR} };
    followSet["FPARAMS"] = { {TokenType::CLOSEPAR} };
    followSet["REPTFPARAMS1"] = { {TokenType::CLOSEPAR} };



    
    

    lookAhead = lexer.nextToken();
}


bool Parser::match(TokenType token){
    if(lookAhead.getType() == token){
        lookAhead = lexer.nextToken();
        return true;
    }
    else{
        lookAhead = lexer.nextToken();
        return false;
    }
};

bool Parser::checkFirstSet(std::string funcName, int pos){
    bool isValid = false;
    if (firstSet.find(funcName) != firstSet.end()) {
        for (size_t i = 0; i < firstSet[funcName][pos].size(); i++) {
            if (lookAhead.getType() == firstSet[funcName][pos][i]) {
                return true;
            }
        }
    }
    return isValid;
}

bool Parser::checkAllFirstSet(std::string funcName) {
    bool isValid = false;
    if (firstSet.find(funcName) != firstSet.end()) {
        for (size_t i = 0; i < firstSet[funcName].size(); i++) {
            for (size_t j = 0; j < firstSet[funcName][i].size(); j++) {
                if (lookAhead.getType() == firstSet[funcName][i][j]) {
                    return true;
                }
            }
        }
    }
    return isValid;
}
bool Parser::checkFollowSet(std::string funcName){
    bool isValid = false;
    for (size_t i = 0; i < followSet[funcName].size(); i++) {
        if (lookAhead.getType() == followSet[funcName][i]) isValid = true;
    }
    return isValid;
}
bool Parser::epsilonCheck(std::string funcName) {
    return followSet.count(funcName) > 0;
}

bool Parser::skipErrors(std::string funcName) {
    if (checkAllFirstSet(funcName) || epsilonCheck(funcName)) {
        return true;
    }
    else {
        outDerivation << "syntax error at" << lookAhead.getLine() <<" \n";
        while (!checkAllFirstSet(funcName) && !checkFollowSet(funcName)) {
            lookAhead = lexer.nextToken();
        }
        if (epsilonCheck(funcName) && checkFollowSet(funcName)) {
            outDerivation << "Parsing Aborted \n";
            return false;
        }
        return true;
    }

}
bool Parser::startParse(){
    std::cout<<"Started Parsing"<<std::endl;
    outDerivation << "Started Parsing \n";
    if(start() && match(TokenType::ENDOFILE)){
        std::cout<<""<<std::endl;
        outDerivation << "Parsing Ended \n";
        return true;}
    else { 
        std::cout << "Syntax error: "<<lookAhead.getLexeme() <<" Type: "<<lookAhead.getType() << " on line "<<lookAhead.getLine() << std::endl;
        return false; }

}

bool Parser::start(){
    
    if(checkFirstSet("START", 0)) {
        if(prog()){
            std::cout<<"start->prog"<<std::endl;
            outDerivation<<"Start -> prog \n";
            return true;
        }
        else{
            return false;
        }
    }
    
    else if(lookAhead.getType() == TokenType::ENDOFILE){
        std::cout<<"start->EOF"<<std::endl;
        outDerivation << "start->EOF \n";

        return true;
    }
    else if(lookAhead.getType() == TokenType::ENDOFILE){
        return true;
    }
    else return false;
};

bool Parser::prog(){
    bool success = false;
    if (!skipErrors("PROG"))return false;
    if(checkFirstSet("PROG", 0)) {
        if(classimplfunc() && prog()){
            std::cout << "PROG-> CLASSIMPLFUNC PROG" << std::endl;
            outDerivation << "PROG-> CLASSIMPLFUNC PROG \n";
            success = true;
        }
        
    }
    else if(checkFollowSet("PROG")){
        std::cout << "PROG -> EPSILON" << std::endl;
        outDerivation << "PROG -> EPSILON \n";
        success = true;
    }
    else {}
    return success;
};

bool Parser::classimplfunc(){
    bool success = false;
    if(!skipErrors("CLASSIMPLFUNC"))return false;

    if(checkFirstSet("CLASSIMPLFUNC", 0)) {
        if(classdecl()){
            std::cout << "CLASSIMPLFUNC -> CLASSDEC" << std::endl;
            outDerivation << "CLASSIMPLFUNC -> CLASSDECL\n";
            success = true;
        }
    }
    else if(checkFirstSet("CLASSIMPLFUNC", 1)){
        if(impldef()){
            std::cout << "CLASSIMPLFUNC -> IMPLDEF" << std::endl;
            outDerivation << "CLASSIMPLFUNC -> IMPLDEF \n";
            success = true;
        }

    }
    else if(checkFirstSet("CLASSIMPLFUNC", 2)){
        if(funcdef()){
            std::cout << "CLASSIMPLFUNC -> FUNCDEF" << std::endl;
            outDerivation << "CLASSIMPLFUNC -> FUNCDEF\n";
            success = true;
        }
    }
    else {}

    return success;
};
//check the conditions of the first set for this declaration
bool Parser::classdecl(){
    bool success = false;
    if (!skipErrors("CLASSDECL")) return false;
    if (checkFirstSet("CLASSDECL", 0)) {
            if (match(TokenType::CLASS) && match(TokenType::ID) && isa1() && match(TokenType::OPENCURLY)
                && vismemberdecl() && match(TokenType::CLOSECURLY) && match(TokenType::SEMICOLON)) {
                std::cout << "CLASSDECL -> CLASS ID ISA1 OPENCURLY VSEMEMBERDECL CLOSECURLY SEMICOLON" << std::endl;
                outDerivation << "CLASSDECL -> CLASS ID ISA1 OPENCURLY VSEMEMBERDECL CLOSECURLY SEMICOLON \n";
                success = true;
            }
        }
    return success;
};

bool Parser::vismemberdecl() {
    bool success = false;
    if (!skipErrors("VISMEMBERDECL")) return false;
    if (checkFirstSet("VISMEMBERDECL", 0)) {
        if (visibility() && memdecl() && vismemberdecl()) {
            std::cout << "VISEMEMBERDECL -> VISIBILITY MEMDECL VISMEMBERDECL" << std::endl;
            outDerivation << "VISEMEMBERDECL -> VISIBILITY MEMDECL VISMEMBERDECL \n";
            success = true;
        }
    }
    else if (checkFollowSet("VISMEMBERDECL")) {
        std::cout << "VISEMEMBERDECL -> EPSILON" << std::endl;
        outDerivation << "VISEMEMBERDECL -> EPSILON\n";
        success = true;
    }
    else {}
    return success;
}

bool Parser::isa1() {
    bool success = false;
    if (!skipErrors("ISA1")) return false;
    if (checkFirstSet("ISA1", 0)) {
        if (match(TokenType::ISA) && match(TokenType::ID) && isa2()) {
            std::cout << "ISA 1 -> isa id isa2" << std::endl;
            outDerivation << "ISA 1 -> isa id isa2 \n";
            success = true;

        }
        else success = false;
        
    }
    else if (checkFollowSet("ISA1")) {
        std::cout << "ISA 1-> EPSILON" << std::endl;
        outDerivation << "ISA 1-> EPSILON \n";
        success = true;
    }
    else success = false;
    return success;
}

bool Parser::isa2() {
    bool success = false;
    if (!skipErrors("ISA2")) return false;
    if (checkFirstSet("ISA2", 0)) {
        if (match(TokenType::COMMA) && match(TokenType::ID) && isa2()) {
            std::cout << "ISA 2-> COMMA ID ISA2" << std::endl;
            outDerivation << "ISA 2-> COMMA ID ISA2 \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFollowSet("ISA2")) {
        std::cout << "ISA 2-> EPSILON" << std::endl;
        outDerivation << "ISA 2-> EPSILON \n";
        success = true;
    }
    else success = false;
    return success;
}

bool Parser::impldef() {
    bool success = false;
    if (!skipErrors("IMPLDEF")) return false;
    if (checkFirstSet("IMPLDEF", 0)) {
        if (match(TokenType::IMPLEMENTATION) && match(TokenType::ID) && match(TokenType::OPENCURLY) && implbody() && match(TokenType::CLOSECURLY)) {
            std::cout << "IMPLDEF -> IMPLEMENTATION ID OPENCURLY IMPLBODY CLOSECURLY" << std::endl;
            outDerivation << " IMPLDEF -> IMPLEMENTATION ID OPENCURLY IMPLBODY CLOSECURLY \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}


bool Parser::implbody() {
    bool success = false;
    if (!skipErrors("IMPLBODY")) return false;
    if (checkFirstSet("IMPLBODY", 0)) {
        if (funcdef() && implbody()) {
            std::cout << "IMPLBODY -> FUNCDEF IMPLBODY" << std::endl;
            outDerivation << "IMPLBODY -> FUNCDEF IMPLBODY \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFollowSet("IMPLBODY")) {
        std::cout << "IMPLBODY -> EPSILON" << std::endl;
        outDerivation << "IMPLBODY -> EPSILON \n";
        success = true;
    }
    else success = false;
    return success;
}

bool Parser::funcdef() {
    bool success = false;
    if (!skipErrors("FUNCDEF")) return false;
    if (checkFirstSet("FUNCDEF", 0)) {
        if (funchead() && funcbody()) {
            std::cout << "FUNCDEF -> FUNCHEAD FUNCBODY" << std::endl;
            outDerivation << "FUNCDEF -> FUNCHEAD FUNCBODY \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::visibility() {
    bool success = false;
    if (!skipErrors("VISIBILITY")) return false;
    if (checkFirstSet("VISIBILITY", 0)) {
        if (match(TokenType::PUBLIC)) {
            std::cout << "VISIBILITY -> PUBLIC" << std::endl;
            outDerivation << "VISIBILITY -> PUBLIC \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("VISIBILITY", 1)) {
        if (match(TokenType::PRIVATE)) {
            std::cout << "VISIBILITY -> PRIVATE" << std::endl;
            outDerivation << "VISIBILITY -> PRIVATE \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::memdecl() {
    bool success = false;
    if (!skipErrors("MEMDECL")) return false;
    if (checkFirstSet("MEMDECL", 0)) {
        if (funcdecl()) {
            std::cout << "MEMDECL -> FUNCDECL" << std::endl;
            outDerivation << "MEMDECL -> FUNCDECL\n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("MEMDECL", 1)) {
        if (attrdecl()) {
            std::cout << "MEMDECL -> ATTRDECL" << std::endl;
            outDerivation << "MEMDECL -> ATTRDECL\n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcdecl() {
    bool success = false;
    if (!skipErrors("FUNCDECL")) return false;
    if (checkFirstSet("FUNCDECL", 0)) {
        if (funchead() && match(TokenType::SEMICOLON)) {
            std::cout << "FUNCDECL -> FUNCHEAD SEMICOLON" << std::endl;
            outDerivation << "FUNCDECL -> FUNCHEAD SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funchead() {
    bool success = false;
    if (!skipErrors("FUNCHEAD")) return false;
    if (checkFirstSet("FUNCHEAD", 0)) {
        if (match(TokenType::CONSTRUCTOR) && match(TokenType::OPENPAR) && fParams() && match(TokenType::CLOSEPAR)) {
            std::cout << "CONSTRUCTOR OPENPAR FPARAMS CLOSEPAR" << std::endl;
            outDerivation << " CONSTRUCTOR OPENPAR FPARAMS CLOSEPAR \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("FUNCHEAD", 1)) {
        if (match(TokenType::FUNCTION) && match(TokenType::ID) && match(TokenType::OPENPAR) && fParams() && match(TokenType::CLOSEPAR) &&
            match(TokenType::ARROW) && returnType()) {
            std::cout << "FUNCTION ID OPENPAR FPARAMS CLOSEPAR ARROW RETURNTYPE" << std::endl;
            outDerivation << "FUNCTION ID OPENPAR FPARAMS CLOSEPAR ARROW RETURNTYPE \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcbody() {
    bool success = false;
    if (!skipErrors("FUNCBODY")) return false;
    if (checkFirstSet("FUNCBODY", 0)) {
        if (match(TokenType::OPENCURLY) && localvardeclorstat2() && match(TokenType::CLOSECURLY)) {
            std::cout << "OPENPAR LOCALVARDECLORSTAT2 CLOSEPAR" << std::endl;
            outDerivation << "OPENPAR LOCALVARDECLORSTAT2 CLOSEPAR \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::localvardeclorstat() {
    bool success = false;
    if (!skipErrors("LOCALVARDECLORSTAT")) return false;
    if (checkFirstSet("LOCALVARDECLORSTAT", 0)) {
        if (localvardecl()) {
            std::cout << "LOCALVARDECLORSTAT -> LOCALVARDECL" << std::endl;
            outDerivation << "LOCALVARDECLORSTAT -> LOCALVARDECL \n";
            success = true;
        }
    }
    else if (checkFirstSet("LOCALVARDECLORSTAT", 1)) {
        if (statement()) {
            std::cout << "LOCALVARDECLORSTAT -> STATEMENT" << std::endl;
            outDerivation << "LOCALVARDECLORSTAT -> STATEMENT \n";
            success = true;
        }
         
    }
    else {}
    return success;

}

bool Parser::localvardeclorstat2() {
    bool success = false;
    if (!skipErrors("LOCALVARDECLORSTAT2")) return false;
    if (checkFirstSet("LOCALVARDECLORSTAT2", 0)) {
        if (localvardeclorstat() && localvardeclorstat2()) {
            std::cout << "LOCALVARDECLORSTAT2 -> LOCALVARDECLORSTAT LOCALVARDECLORSTAT2" << std::endl;
            outDerivation << "LOCALVARDECLORSTAT2 -> LOCALVARDECLORSTAT LOCALVARDECLORSTAT2 \n ";
            success = true;
        }
        else success = false;
    }
    else if (checkFollowSet("LOCALVARDECLORSTAT2")) {
        std::cout << "LOCALVARDECLORSTAT2 -> EPSILON " << std::endl;
        outDerivation << "LOCALVARDECLORSTAT2 -> EPSILON \n";
        success = true;
    }
    else success = false;
    return success;
}

bool Parser::attrdecl() {
    bool success = false;
    if (!skipErrors("ATTRDECL")) return false;
    if (checkFirstSet("ATTRDECL", 0)) {
        if (match(TokenType::ATTRIBUTE) && vardecl()) {
            std::cout << "ATTRDECL -> ATTRIBUTE VARDECL " << std::endl;
            outDerivation << "ATTRDECL -> ATTRIBUTE VARDECL \n";
            success = true;
        }
    }
    return success;
}

bool Parser::localvardecl() {
    bool success = false;
    if (!skipErrors("LOCALVARDECL")) return false;
    if (checkFirstSet("LOCALVARDECL", 0)) {
        if (match(TokenType::LOCAL) && vardecl()) {
            std::cout << "LOCALVARDECL -> LOCAL VARDECL" << std::endl;
            outDerivation << "LOCALVARDECL -> LOCAL VARDECL \n";
            success = true;
        }
    }
    else {}
    return success;
}

bool Parser::vardecl() {
    bool success = false;
    if (!skipErrors("VARDECL")) return false;
    if (checkFirstSet("VARDECL", 0)) {
        if (match(TokenType::ID) && match(TokenType::COLON) && type() && arraySizes() && match(TokenType::SEMICOLON)) {
            std::cout << "VARDECL -> ID COLON TYPE ARRAYSIZES SEMICOLON" << std::endl;
            outDerivation << "VARDECL -> ID COLON TYPE ARRAYSIZES SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::statement() {
    bool success = false;
    if (!skipErrors("STATEMENT")) return false;
    if (checkFirstSet("STATEMENT", 0)) {
        if (funcallorassign() && match(TokenType::SEMICOLON)) {
            std::cout << "STATEMENT -> FUNCALLAORASSIGN SEMICOLON " << std::endl;
            outDerivation << "STATEMENT -> FUNCALLAORASSIGN SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATEMENT", 1)) {
        if (match(TokenType::WRITE) && match(TokenType::OPENPAR) && expr() && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)) {
            std::cout << "STATEMENT -> WRITE OPENPAR EXPR CLOSEPAR SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> WRITE OPENPAR EXPR CLOSEPAR SEMICOLON \n";
            success = true;
        }
        else success = false;

    }
    else if (checkFirstSet("STATEMENT", 2)) {
        if (match(TokenType::WHILE) && match(TokenType::OPENPAR) && relexpr() && match(TokenType::CLOSEPAR)
            && statblock() && match(TokenType::SEMICOLON)) {
            std::cout << "STATEMENT -> WHILE OPENPAR RELEXPR CLOSEPAR STATBLOCK SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> WHILE OPENPAR RELEXPR CLOSEPAR STATBLOCK SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATEMENT", 3)) {
        if (match(TokenType::RETURN) && match(TokenType::OPENPAR) && expr() && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)) {
            std::cout << "STATEMENT -> RETURN OPENPAR EXPR CLOSEPAR SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> RETURN OPENPAR EXPR CLOSEPAR SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATEMENT", 4)) {
        if (match(TokenType::READ) && match(TokenType::OPENPAR) && variable() && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)) {
            std::cout << "STATEMENT -> READ OPENPAR VARIABLE CLOSEPAR SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> READ OPENPAR VARIABLE CLOSEPAR SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATEMENT", 5)) {
        if (match(TokenType::IF) && match(TokenType::OPENPAR) && relexpr() && match(TokenType::CLOSEPAR)
            && match(TokenType::THEN) && statblock() && match(TokenType::ELSE) && statblock() && match(TokenType::SEMICOLON)) {
            std::cout << "STATEMENT -> IF OPENPAR RELEXPR CLOSEPAR THEN STATBLOCK ELSE STATBLOCK SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> IF OPENPAR RELEXPR CLOSEPAR THEN STATBLOCK ELSE STATBLOCK SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcallorassign() {
    bool success = false;
    if (!skipErrors("FUNCALLORASSIGN")) return false;
    if (checkFirstSet("FUNCALLORASSIGN", 0)) {
        if (idOrSelf() && funcallorassign2()) {
            std::cout << "FUNCALLORASSIGN -> IDORSELF FUNCALLORASSIGN2" << std::endl;
            outDerivation << "FUNCALLORASSIGN -> IDORSELF FUNCALLORASSIGN2 \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcallorassign2() {
    bool success = false;
    if (!skipErrors("FUNCALLORASSIGN2")) return false;
    if (checkFirstSet("FUNCALLORASSIGN2", 0)) {
        if (indices() && funcasllorassign3()) {
            std::cout << "FUNCALLORASSIGN2 -> INDICES FUNCALLORASSIGN3" << std::endl;
            outDerivation << "FUNCALLORASSIGN2 -> INDICES FUNCALLORASSIGN3 \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("FUNCALLORASSIGN2", 1)) {
        if (match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR) && funcallorassign4()) {
            std::cout << "FUNCALLORASSIGN2 -> OPENPAR AAPARMS CLOSEPAR FUNCALLORASSIGN4" << std::endl;
            outDerivation << "FUNCALLORASSIGN2 -> OPENPAR AAPARMS CLOSEPAR FUNCALLORASSIGN4 \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcasllorassign3() {
    bool success = false;
    if (!skipErrors("FUNCALLORASSIGN3")) return false;
    if (checkFirstSet("FUNCALLORASSIGN3", 0)) {
        if (assignOp() && expr()) {
            std::cout << "FUNCALLORASSIGN3 -> ASSIGNOP EXPR" << std::endl;
            outDerivation << "FUNCALLORASSIGN3 -> ASSIGNOP EXPR \n";
            success = true;
        }
    }
    else if (checkFirstSet("FUNCALLORASSIGN3", 1)) {
        if (match(TokenType::DOT) && match(TokenType::ID) && funcallorassign2()) {
            std::cout << "FUNCALLORASSIGN3 -> DOT ID FUNCALLORASSIGN2" << std::endl;
            outDerivation << "FUNCALLORASSIGN3 -> DOT ID FUNCALLORASSIGN2 \n";
            success = true;
        }
    }
    else {}
    return success;
}

bool Parser::funcallorassign4() {
    bool success = false;
    if (!skipErrors("FUNCALLORASSIGN4")) return false;
    if (checkFirstSet("FUNCALLORASSIGN4", 0)) {
        if (match(TokenType::DOT) && match(TokenType::ID) && funcallorassign2()) {
            std::cout << "FUNCALLORASSIGN4 -> DOT ID FUNCALLORASSIGN2" << std::endl;
            outDerivation << "FUNCALLORASSIGN4 -> DOT ID FUNCALLORASSIGN2 \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFollowSet("FUNCALLORASSIGN4")) {
        std::cout << "FUNCALLORASSIGN4 -> EPSILON" << std::endl;
        outDerivation << "FUNCALLORASSIGN4 -> EPSILON \n";
        success = true;
    }
    else success = false;
    return success;
}

bool Parser::statblock() {
    bool success = false;

    if (!skipErrors("STATBLOCK")) return false;

    if (checkFirstSet("STATBLOCK", 0)) {
        if (statement()) {
            std::cout << "STATBLOCK -> STATEMENT" << std::endl;
            outDerivation << "STATBLOCK -> STATEMENT \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATBLOCK", 1)) {
        if (match(TokenType::OPENCURLY) && statements() && match(TokenType::CLOSECURLY)) {
            std::cout << "STATBLOCK -> OPENCURLY STATEMENTS CLOSECURLY" << std::endl;
            outDerivation << "STATBLOCK -> OPENCURLY STATEMENTS CLOSECURLY \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFollowSet("STATBLOCK")) {
        std::cout << "STATBLOCK -> EPSILON" << std::endl;
        outDerivation << "STATBLOCK -> EPSILON \n";
        success = true;
    }
    else success = false;
    return success;
}


bool Parser::statements() {
    bool success = false;
    if (!skipErrors("STATEMENTS")) return false;
    if (checkFirstSet("STATEMENTS", 0)) {
        if (statement() && statements()) {
            std::cout << "STATEMENTS -> STATEMENT STATEMENTS" << std::endl;
            outDerivation << "STATEMENTS -> STATEMENT STATEMENTS \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFollowSet("STATEMENTS")) {
        std::cout << "STATEMENTS -> EPSILON " << std::endl;
        outDerivation << "STATEMENTS -> EPSILON \n";
        success = true;
    }
    else success = false;
    return success;
}

bool Parser::expr() {
    bool success = false;
    if (!skipErrors("EXPR")) return false;

    if (checkFirstSet("EXPR", 0)) {
        if (arithexpr() && expr2()) {
            std::cout << "EXPR -> ARITHEXPR EXPR2" << std::endl;
            outDerivation << "EXPR -> ARITHEXPR EXPR2 \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    
    return success;
}

bool Parser::expr2() {
    bool success = false;
    if (!skipErrors("EXPR2"))return false;
    if (checkFirstSet("EXPR2", 0)) {
        if (relOp() && arithexpr()) {
            std::cout << "EXPR2 -> RELOP ARITHEXPR" << std::endl;
            outDerivation << "EXPR2 -> RELOP ARITHEXPR \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFollowSet("EXPR2")) {
        std::cout << "EXPR2 -> EPSILON" << std::endl;
        outDerivation << "EXPR2 -> EPSILON \n";
        success = true;
    }
    else success = false;

    return success;
}

bool Parser::relexpr() {
    bool success = false;
    if (!skipErrors("RELEXPR")) return false;

    if (checkFirstSet("RELEXPR", 0)) {
        if (arithexpr() && relOp() && arithexpr()) {
            std::cout << "RELEXPR -> ARITHEXPR RELOP ARITHEXPR" << std::endl;
            outDerivation << "RELEXPR -> ARITHEXPR RELOP ARITHEXPR \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::arithexpr() {
    bool success = false;
    if (!skipErrors("ARITHEXPR")) return false;

    if (checkFirstSet("ARITHEXPR", 0)) {
        if (term() && rightrecarithexpr()) {
            std::cout << "ARITHEXPR -> TERM RIGHTRECARITHEXPR" << std::endl;
            outDerivation << "ARITHEXPR -> TERM RIGHTRECARITHEXPR \n";
            success = true;
        }
    }
    return success;
}

bool Parser::rightrecarithexpr() {
    bool success = false;
    if (!skipErrors("RIGHTRECARITHEXPR"))return false;

    if (checkFirstSet("RIGHTRECARITHEXPR", 0)) {
        if (addOp() && term() && rightrecarithexpr()) {
            std::cout << "RIGHTRECARITHEXPR -> ADDOP TERM RIGHTRECARITHEXPR" << std::endl;
            outDerivation << "RIGHTRECARITHEXPR -> ADDOP TERM RIGHTRECARITHEXPR \n";
            success = true;
        }

    }
    else if (checkFollowSet("RIGHTRECARITHEXPR")) {
        std::cout << "RIGHTRECARITHEXPR -> EPSILON" << std::endl;
        outDerivation << "RIGHTRECARITHEXPR -> EPSILON \n";
        success = true;
    }

    return success;
}


bool Parser::sign() {
    bool success = false;
    if (!skipErrors("SIGN")) return false;

    if (checkFirstSet("SIGN", 0)) {
        if (match(TokenType::ADD)) {
            std::cout << "SIGN -> ADD" << std::endl;
            outDerivation << "SIGN -> ADD \n";
            success = true;
        }
    }
    else if (checkFirstSet("SIGN", 1)) {
        if (match(TokenType::SUBT)) {
            std::cout << "SIGN -> SUBT" << std::endl;
            outDerivation << "SIGN -> SUBT \n";
            success = true;
        }
    }
    return success;
}

bool Parser::term() {
    bool success = false;
    if (!skipErrors("TERM")) return false;

    if (checkFirstSet("TERM", 0)) {
        if (factor() && rightrecterm()) {
            std::cout << "TERM -> FACTOR RIGHTRECTERM" << std::endl;
            outDerivation << "TERM -> FACTOR RIGHTRECTERM \n";
            success = true;
        }

    }
    return success;
}

bool Parser::rightrecterm() {
    bool success = false;
    if (!skipErrors("RIGHTRECTERM")) return false;

    if (checkFirstSet("RIGHTRECTERM", 0)) {
        if (multOp() && factor() && rightrecterm()) {
            std::cout << "RIGHTRECTERM -> MULTOP FACTOR RIGHTRECTERM" << std::endl;
            outDerivation << "RIGHTRECTERM -> MULTOP FACTOR RIGHTRECTERM \n";
            success = true;
        }

    }
    else if (checkFollowSet("RIGHTRECTERM")) {
        std::cout << "RIGHTRECTERM -> EPSILON" << std::endl;
        outDerivation << "RIGHTRECTERM -> EPSILON \n";
        success = true;
    }
    
    return success;
}

bool Parser::factor() {
    bool success = false;
    if (!skipErrors("FACTOR"))return false;

    if (checkFirstSet("FACTOR", 0)) {
        if (sign() && factor()) {
            std::cout << "FACTOR -> SIGN FACTOR" << std::endl;
            outDerivation << "FACTOR -> SIGN FACTOR \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 1)) {
        if (idOrSelf() && factor2() && reptvariableorfunctioncall()) {
            std::cout << "FACTOR -> IDORSELF FACTOR2 REPTVARIABLEORFUNCTIONCALL" << std::endl;
            outDerivation << "FACTOR -> IDORSELF FACTOR2 REPTVARIABLEORFUNCTIONCALL \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 2)) {
        if (match(TokenType::NOT) && factor()) {
            std::cout << "FACTOR -> NOT FACTOR" << std::endl;
            outDerivation << "FACTOR -> NOT FACTOR \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 3)) {
        if (match(TokenType::INTEGER_VAL)) {
            std::cout << "FACTOR -> INTEGER LITERAL" << std::endl;
            outDerivation << "FACTOR -> INTEGER LITERAL \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 4)) {
        if (match(TokenType::FLOAT_VAL)) {
            std::cout << "FACTOR -> FLOAT LITERAL" << std::endl;
            outDerivation << "FACTOR -> FLOAT LITERAL \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 5)) {
        if (match(TokenType::OPENPAR) && arithexpr() && match(TokenType::CLOSEPAR)) {
            std::cout << "FACTOR -> OPENPAR ARITHEXPR CLOSEPAR" << std::endl;
            outDerivation << "FACTOR -> OPENPAR ARITHEXPR CLOSEPAR \n";
            success = true;
        }
    }
    else success = false;
    return success;
}

bool Parser::factor2() {
    bool success = false;

    if (!skipErrors("FACTOR2"))return false;

    if (checkFirstSet("FACTOR2", 0)) {
        if (indices()) {
            std::cout << "FACOTR2 -> INDICES" << std::endl;
            outDerivation << "FACOTR2 -> INDICES \n";
            success = true;
        }
        
    }
    else if (checkFirstSet("FACTOR2", 1)) {
        if (match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR)) {
            std::cout << "FACTOR2 -> OPENPAR APARAMS CLOSEPAR" << std::endl;
            outDerivation << "FACTOR2 -> OPENPAR APARAMS CLOSEPAR \n";
            success = true;
        }
    }
    else if (checkFollowSet("FACTOR2")) {
        std::cout << "FACTOR2 -> EPSILON" << std::endl;
        outDerivation << "FACTOR2 -> EPSILON \n";
        success = true;
    }

    return success;
}

bool Parser::indices() {
    bool success = false;

    if (!skipErrors("INDICES"))return false;

    if (checkFirstSet("INDICES", 0)) {
        if (indice() && indices()) {
            std::cout << "INDICES -> INDICE INDICES" << std::endl;
            outDerivation << "INDICES -> INDICE INDICES \n";
            success = true;
        }

    }
    else if (checkFollowSet("INDICES")) {
        std::cout << "INDICES -> EPSILON" << std::endl;
        outDerivation << "INDICES -> EPSILON \n";
        success = true;
    }

    return success;
}

bool Parser::reptvariableorfunctioncall() {
    bool success = false;
    if (!skipErrors("REPTVARIABLEORFUNCTIONCALL"))return false;

    if (checkFirstSet("REPTVARIABLEORFUNCTIONCALL", 0)) {
        if (idNest() && reptvariableorfunctioncall()) {
            std::cout << "REPTVARIABLEORFUNCTIONCALL -> IDNEST REPTVARIABLEORFUNCTIONCALL" << std::endl;
            outDerivation << "REPTVARIABLEORFUNCTIONCALL -> IDNEST REPTVARIABLEORFUNCTIONCALL \n";
            success = true;
        }

    }
    else if (checkFollowSet("REPTVARIABLEORFUNCTIONCALL")) {
        std::cout << "REPTVARIABLEORFUNCTIONCALL -> EPSILON" << std::endl;
        outDerivation << "REPTVARIABLEORFUNCTIONCALL -> EPSILON \n";
        success = true;
    }
    return success;
}

bool Parser::variable() {
    bool success = false;
    if (!skipErrors("VARIABLE"))return false;

    if (checkFirstSet("VARIABLE", 0)) {
        if (idOrSelf() && variable2()) {
            std::cout << "VARIABLE -> IDORSELF VARIABLE2" << std::endl;
            outDerivation << "VARIABLE -> IDORSELF VARIABLE2 \n";
            success = true;
        }
    }
    return success;
}

bool Parser::variable2() {
    bool success = false;
    if (!skipErrors("VARIABLE2"))return false;
    if (checkFirstSet("VARIABLE2", 0)) {
        if (indices() && reptvariable()) {
            std::cout << "VARIABLE2 -> INDICES REPTVARIABLE" << std::endl;
            outDerivation << "VARIABLE2 -> INDICES REPTVARIABLE \n";
            success = true;
        }
    }
    else if (checkFirstSet("VARIABLE2", 1)) {
        if (match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR) && varIdNest()) {
            std::cout << "VARIABLE2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST" << std::endl;
            outDerivation << "VARIABLE2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST \n";
            success = true;
        }
    }
    

    return success;
}

bool Parser::reptvariable() {
    bool success = false;
    if (!skipErrors("REPTVARIABLE"))return false;
    if (checkFirstSet("REPTVARIABLE", 0)) {
        if (varIdNest() && reptvariable()) {
            std::cout << "REPTVARIABLE -> VARIDNEST REPTVARIABLE" << std::endl;
            outDerivation << "REPTVARIABLE -> VARIDNEST REPTVARIABLE \n";
            success = true;
        }
    }
    else if (checkFollowSet("REPTVARIABLE")) {
        std::cout << "REPTVARIABLE -> EPSILON" << std::endl;
        outDerivation << "REPTVARIABLE -> EPSILON \n";
        success = true;
    }
    return success;
}

bool Parser::varIdNest() {
    bool success = false;
    if (!skipErrors("VARIDNEST"))return false;
    if (checkFirstSet("VARIDNEST", 0)) {
        if (match(TokenType::DOT) && match(TokenType::ID) && varIdNest2()) {
            std::cout << "VARIDNEST -> DOT ID VARIDEST2" << std::endl;
            outDerivation << "VARIDNEST -> DOT ID VARIDEST2 \n";
            success = true;
        }
    }
    return success;
}

bool Parser::varIdNest2() {
    bool success = false;
    if (!skipErrors("VARIDNEST2"))return false;

    if (checkFirstSet("VARIDNEST2", 0)) {
        if (indices()) {
            std::cout << "VARIDNEST2 -> INDICES " << std::endl;
            outDerivation << "VARIDNEST2 -> INDICES \n";
            success = true;
        }
    }
    else if (checkFirstSet("VARIDNEST2", 1)) {
        if (match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR) && varIdNest()) {
            std::cout << "VARIDNEST2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST" << std::endl;
            outDerivation << "VARIDNEST2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST \n";
            success = true;
        }
    }

    return success;
}

bool Parser::indice() {
    bool success = false;
    if (!skipErrors("INDICE")) return false;

    if (checkFirstSet("INDICE", 0)) {
        if (match(TokenType::OPENSQUARE) && arithexpr() && match(TokenType::CLOSESQUARE)) {
            std::cout << "INDICE -> OPENSQUARE ARITHEXPR CLOSESQUARE" << std::endl;
            outDerivation << "INDICE -> OPENSQUARE ARITHEXPR CLOSESQUARE \n";
            success = true;
        }
    }

    return success;
}

bool Parser::idNest() {
    bool success = false;

    if (!skipErrors("IDNEST"))return false;

    if (checkFirstSet("IDNEST", 0)) {
        if (match(TokenType::DOT) && match(TokenType::ID) && idNest2()) {
            std::cout << "IDNEST -> DOT ID IDNEST2" << std::endl;
            outDerivation << "IDNEST -> DOT ID IDNEST2 \n";
            success = true;
        }
    }

    return success;
}

bool Parser::idNest2() {
    bool success = false;

    if (!skipErrors("IDNEST2")) return false;

    if (checkFirstSet("IDNEST2", 0)) {
        if (indices()) {
            std::cout << "IDNEST2 -> INDICES" << std::endl;
            outDerivation << "IDNEST2 -> INDICES \n";
            success = true;
        }
    }
    else if (checkFirstSet("IDNEST2", 1)) {
        if (match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR)) {
            std::cout << "IDNEST2 -> OPENPAR APARAMS CLOSEPAR" << std::endl;
            outDerivation << "IDNEST2 -> OPENPAR APARAMS CLOSEPAR \n";
            success = true;
        }
    }
    else success = false;
    return success;
}

bool Parser::arraySize() {
    bool success = false;
    if (!skipErrors("ARRAYSIZE")) return false;

    if (checkFirstSet("ARRAYSIZE", 0)) {
        if (match(TokenType::OPENSQUARE) && arraySize2()) {
            std::cout << "ARRAYSIZE -> OPENSQUARE ARRAYSIZE2" << std::endl;
            outDerivation << "ARRAYSIZE -> OPENSQUARE ARRAYSIZE2 \n";
            success = true;
        }
    }
    return success;
}

bool Parser::arraySize2() {
    bool success = false;
    if (!skipErrors("ARRAYSIZE2"))return false;

    if (checkFirstSet("ARRAYSIZE2", 0)) {
        if (match(TokenType::CLOSESQUARE)) {
            std::cout << "ARRAYSIZE2 -> CLOSESQUARE" << std::endl;
            outDerivation << "ARRAYSIZE2 -> CLOSESQUARE \n";
            success = true;
        }
    }
    else if (checkFirstSet("ARRAYSIZE2", 1)) {
        if (match(TokenType::INTEGER_VAL) && match(TokenType::CLOSESQUARE)) {
            std::cout << "ARRAYSIZE2 -> INTEGERVAL CLOSESQUARE" << std::endl;
            outDerivation << "ARRAYSIZE2 -> INTEGERVAL CLOSESQUARE \n";
            success = true;
        }
    }
    
    else {}
    return success;
}

bool Parser::arraySizes() {
    bool success = false;

    if (!skipErrors("ARRAYSIZES"))return false;

    if (checkFirstSet("ARRAYSIZES", 0)) {
        if (arraySize() && arraySizes()) {
            std::cout << "ARRAYSIZES -> ARRAYSIZE ARRAYSIZES " << std::endl;
            outDerivation << "ARRAYSIZES -> ARRAYSIZE ARRAYSIZES \n";
            success = true;
        }
    }
    else if (checkFollowSet("ARRAYSIZES")) {
        std::cout << "ARRAYSIZES -> EPSILON" << std::endl;
        outDerivation << "ARRAYSIZES -> EPSILON \n";
        success = true;
    }
    else {}
    return success;
}

bool Parser::type() {
    bool success = false;

    if (!skipErrors("TYPE"))return false;

    if (checkFirstSet("TYPE", 0)) {
        if (match(TokenType::INT_T)) {
            std::cout << "TYPE -> INT" << std::endl;
            outDerivation << "TYPE -> INT \n";
            success = true;
        }
    }
    else if (checkFirstSet("TYPE", 1)) {
        if (match(TokenType::ID)) {
            std::cout << "TYPE -> ID" << std::endl;
            outDerivation << "TYPE -> ID \n";
            success = true;
        }
    }
    else if (checkFirstSet("TYPE", 2)) {
        if (match(TokenType::FLOAT_T)) {
            std::cout << "TYPE -> FLOAT" << std::endl;
            outDerivation << "TYPE -> FLOAT \n";
            success = true;
        }
    }
    else {}
    return success;
}

bool Parser::returnType() {
    bool success = false;
    if (!skipErrors("RETURNTYPE"))return false;
    if (checkFirstSet("RETURNTYPE", 0)) {
        if (type()) {
            std::cout << "RETURNTYPE -> TYPE" << std::endl;
            outDerivation << "RETURNTYPE -> TYPE \n";
            success = true;
        }
    }
    else if (checkFirstSet("RETURNTYPE", 1)) {
        if (match(TokenType::VOID)) {
            std::cout << "RETURNTYPE -> VOID" << std::endl;
            outDerivation << "RETURNTYPE -> VOID \n";
            success = true;
        }
    }
    else {}

    return success;
}

bool Parser::aParams() {
    bool success = false;
    if (!skipErrors("APARAMS"))return false;

    if (checkFirstSet("APARAMS", 0)) {
        if (expr() && reptaParams1()) {
            std::cout << "APARAMS -> EXPR REPTAPARAMS1" << std::endl;
            outDerivation << "APARAMS -> EXPR REPTAPARAMS1 \n";
            success = true;
        }
    }
    else if (checkFollowSet("APARAMS")) {
        std::cout << "APARAMS -> EPSILON" << std::endl;
        outDerivation << "APARAMS -> EPSILON \n";
        success = true;
    }
    else {}

    return success;
}

bool Parser::reptaParams1() {
    bool success = false;
    if (!skipErrors("REPTAPARAMS1"))return false;

    if (checkFirstSet("REPTAPARAMS1", 0)) {
        if (aParamsTail() && reptaParams1()) {
            std::cout << "REPTAPARAMS1 -> APARAMSTAIL REPTAPARAMS" << std::endl;
            outDerivation << "REPTAPARAMS1 -> APARAMSTAIL REPTAPARAMS \n";
            success = true;
        }

    }
    else if (checkFollowSet("REPTAPARAMS1")) {
        std::cout << "REPTAPARAMS1 -> EPSILON " << std::endl;
        outDerivation << "REPTAPARAMS1 -> EPSILON \n";
        success = true;
    }
    else {}

    return success;
}

bool Parser::aParamsTail() {
    bool success = false;
    if (!skipErrors("APARAMSTAIL"))return false;

    if (checkFirstSet("APARAMSTAIL", 0)) {
        if (match(TokenType::COMMA) && expr()) {
            std::cout << "APARAMSTAIL -> COMMA EXPR " << std::endl;
            outDerivation << "APARAMSTAIL -> COMMA EXPR \n";
            success = true;
        }
    }
    return success;
}

bool Parser::fParams() {
    bool success = false;

    if (!skipErrors("FPARAMS"))return false;

    if (checkFirstSet("FPARAMS", 0)) {
        if (match(TokenType::ID) && match(TokenType::COLON) && type() && arraySizes() && reptfParams1()) {
            std::cout << "FPARAMS -> ID COLON TYPE ARRAYSIZES REPTFPARAMS1" << std::endl;
            outDerivation << "FPARAMS -> ID COLON TYPE ARRAYSIZES REPTFPARAMS1 \n";
            success = true;
        }
    }
    else if (checkFollowSet("FPARAMS")) {
        std::cout << "FPARAMS -> EPSILON " << std::endl;
        outDerivation << "FPARAMS -> EPSILON \n";
        success = true;
    }
    else {}

    return success;
}

bool Parser::reptfParams1() {
    bool success = false;

    if (!skipErrors("REPTFPARAMS1"))return false;

    if (checkFirstSet("REPTFPARAMS1", 0)) {
        if (fParamstail() && reptfParams1()) {
            std::cout << "REPTFPARAMS1 -> FPARAMSTAIL REPTFPARAMS1" << std::endl;
            outDerivation << "REPTFPARAMS1 -> FPARAMSTAIL REPTFPARAMS1\n";
            success = true;
        }
    }
    else if (checkFollowSet("REPTFPARAMS1")) {
        std::cout << "REPTFPARAMS1 -> EPSILON " << std::endl;
        outDerivation << "REPTFPARAMS1 -> EPSILON \n";
        success = true;
    }
    else {}
    return success;
}

bool Parser::fParamstail() {
    bool success = false;

    if (!skipErrors("FPARAMSTAIL"))return false;

    if (checkFirstSet("FPARAMSTAIL", 0)) {
        if (match(TokenType::COMMA) && match(TokenType::ID) && match(TokenType::COLON) && type() && arraySizes()) {
            std::cout << "FPARAMSTAIL -> COMMA ID COLON TYPE ARRAYSIZES" << std::endl;
            outDerivation << "FPARAMSTAIL -> COMMA ID COLON TYPE ARRAYSIZES \n";
            success = true;
        }
    }

    return success;
}

bool Parser::assignOp(){
    bool success = false;

    if (!skipErrors("ASSIGNOP"))return false;

    if (checkFirstSet("ASSIGNOP", 0)) {
        if (match(TokenType::ASSIGN)) {
            std::cout << "ASSIGNOP -> ASSIGN" << std::endl;
            outDerivation << "ASSIGNOP -> ASSIGN \n";
            success = true;
        }
    }
    return success;
}

bool Parser::relOp() {
    bool success = false;

    if (!skipErrors("RELOP"))return false;

    if (checkFirstSet("RELOP", 0)) {
        if (match(TokenType::NOTEQ)) {
            std::cout << "RELOP -> NOTEQ " << std::endl;
            outDerivation << "RELOP -> NOTEQ \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 1)) {
        if (match(TokenType::LTEQ)) {
            std::cout << "RELOP -> LTEQ " << std::endl;
            outDerivation << "RELOP -> LTEQ \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 2)) {
        if (match(TokenType::LT)) {
            std::cout << "RELOP -> NOTEQ " << std::endl;
            outDerivation << "RELOP -> NOTEQ \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 3)) {
        if (match(TokenType::GTEQ)) {
            std::cout << "RELOP -> GTEQ" << std::endl;
            outDerivation << "RELOP -> GTEQ \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 4)) {
        if (match(TokenType::GT)) {
            std::cout << "RELOP -> GT" << std::endl;
            outDerivation << "RELOP -> GT \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 5)) {
        if (match(TokenType::EQ)) {
            std::cout << "RELOP -> EQ " << std::endl;
            outDerivation << "RELOP -> EQ \n";
            success = true;
        }
    }
    else {}

    return success;
}

bool Parser::addOp() {
    bool success = false;
    if (!skipErrors("ADDOP"))return false;
    
    if (checkFirstSet("ADDOP", 0)) {
        if (match(TokenType::ADD)) {
            std::cout << "ADDOP -> ADD" << std::endl;
            outDerivation << "ADDOP -> ADD \n";
            success = true;
        }
    }
    else if (checkFirstSet("ADDOP", 1)) {
        if (match(TokenType::OR)) {
            std::cout << "ADDOP -> OR " << std::endl;
            outDerivation << "ADDOP -> OR \n";
            success = true;
        }
    }
    else if (checkFirstSet("ADDOP", 2)) {
        if (match(TokenType::SUBT)) {
            std::cout << "ADDOP -> SUBT " << std::endl;
            outDerivation << "ADDOP -> SUBT \n";
            success = true;
        }
    }
    else {}

    return success;
}

bool Parser::multOp() {
    bool success = false;

    if (!skipErrors("MULTOP"))return false;

    if (checkFirstSet("MULTOP", 0)) {
        if (match(TokenType::AND)) {
            std::cout << "MULTOP -> AND " << std::endl;
            outDerivation << "MULTOP -> AND \n";
            success = true;
        }
    }
    else if (checkFirstSet("MULTOP", 1)) {
        if (match(TokenType::DIV)) {
            std::cout << "MULTOP -> DIV  " << std::endl;
            outDerivation << "MULTOP -> DIV \n";
            success = true;
        }
    }
    else if (checkFirstSet("MULTOP", 2)) {
        if (match(TokenType::MULT)) {
            std::cout << "MULTOP -> MULT  " << std::endl;
            outDerivation << "MULTOP -> MULT \n";
            success = true;
        }
    }
    else {}

    return success;
}

bool Parser::idOrSelf() {
    bool success = false;

    if (!skipErrors("IDORSELF"))return false;

    if (checkFirstSet("IDORSELF", 0)) {
        if (match(TokenType::SELF)) {
            std::cout << "IDORSELF -> SELF" << std::endl;
            outDerivation << "IDORSELF -> SELF \n";
            success = true;
        }
    }
    else if (checkFirstSet("IDORSELF", 1)) {
        if (match(TokenType::ID)) {
            std::cout << "IDORSELF -> ID" << std::endl;
            outDerivation << "IDORSELF -> ID \n";
            success = true;
        }
    }
    else{}

    return success;
}





