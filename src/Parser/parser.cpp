#include "parser.h"
#include "../ASTFactory.h"

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
    followSet["IDNEST2"] = { {TokenType::CLOSEPAR, TokenType::SEMICOLON, TokenType::COMMA, TokenType::EQ, TokenType::GT,
        TokenType::GTEQ, TokenType::LT, TokenType::LTEQ, TokenType::NOTEQ, TokenType::CLOSESQUARE, TokenType::SUBT, TokenType::OR,
        TokenType::ADD, TokenType::MULT, TokenType::DIV, TokenType::AND, TokenType::DOT} };



    
    

    lookAhead = lexer.nextToken();
}



AST* Parser::getast() {
    return ast;
}
/**
 * @brief Matches the current lookahead token with the expected token type.
 *
 * This function checks if the type of the current lookahead token matches the
 * specified token type. If it matches, the function consumes the current token
 * by advancing to the next token from the lexer and returns true. If it does
 * not match, the function still advances to the next token but returns false.
 *
 * @param token The expected token type to match against the current lookahead token.
 * @return true if the current lookahead token matches the specified token type, false otherwise.
 */
bool Parser::match(TokenType token){
    if(lookAhead.getType() == token){
        lastToken = lookAhead;
        lookAhead = lexer.nextToken();

        switch (lastToken.getType()) {
        case TokenType::INT_T:
        case TokenType::FLOAT_T:
        case TokenType::FLOAT_VAL:
        case TokenType::INTEGER_VAL:
        case TokenType::ID:
        case TokenType::PUBLIC:
        case TokenType::PRIVATE:

        case TokenType::EQ:
        case TokenType::LT:
        case TokenType::LTEQ:
        case TokenType::GT:
        case TokenType::GTEQ:
        case TokenType::NOTEQ:

        case TokenType::ADD:
        case TokenType::SUBT:
        case TokenType::OR:
        case TokenType::AND:
        case TokenType::MULT:
        case TokenType::DIV:

        case TokenType::ASSIGN:
        case TokenType::VOID:
        case TokenType::NOT:
        case TokenType::DOT:
        case TokenType::SELF:


            attrStack.push(ASTFactory::makeNode(lastToken));
        }
        return true;
    }
    else{
        lookAhead = lexer.nextToken();
        return false;
    } 
};

/**
 * @brief Checks if the lookahead token type is in the first set of the given function name at the specified position.
 * 
 * This function verifies whether the type of the current lookahead token matches any of the token types
 * in the first set of the specified function name at the given position. The first set is a map where
 * the key is the function name and the value is a vector of vectors of token types.
 * 
 * @param funcName The name of the function whose first set is to be checked.
 * @param pos The position in the first set vector to be checked.
 * @return true If the lookahead token type matches any token type in the first set at the specified position.
 * @return false If the lookahead token type does not match any token type in the first set at the specified position.
 */
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

/**
 * @brief Checks if the lookahead token type is in the first set of the given function name.
 * 
 * This function iterates through the first set of the specified function name and checks if the
 * type of the lookahead token matches any type in the first set. If a match is found, the function
 * returns true. Otherwise, it returns false.
 * 
 * @param funcName The name of the function whose first set is to be checked.
 * @return true if the lookahead token type is in the first set of the given function name, false otherwise.
 */
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
/**
 * @brief Checks if the current lookahead token is in the follow set of the given function.
 * 
 * This function iterates through the follow set of the specified function name and 
 * checks if the type of the current lookahead token matches any of the types in the follow set.
 * 
 * @param funcName The name of the function whose follow set is to be checked.
 * @return true if the lookahead token's type is in the follow set of the given function, false otherwise.
 */
bool Parser::checkFollowSet(std::string funcName){
    bool isValid = false;
    for (size_t i = 0; i < followSet[funcName].size(); i++) {
        if (lookAhead.getType() == followSet[funcName][i]) isValid = true;
    }
    return isValid;
}
/**
 * @brief Checks if the given function name is in the follow set.
 * 
 * This function determines whether the specified function name exists
 * within the follow set, indicating that it can be derived from epsilon.
 * 
 * @param funcName The name of the function to check.
 * @return true if the function name is in the follow set, false otherwise.
 */
bool Parser::epsilonCheck(std::string funcName) {
    return followSet.count(funcName) > 0;
}

/**
 * @brief Skips errors in the parsing process by checking the first and follow sets of a given function name.
 *
 * This function attempts to handle syntax errors by checking if the current token is in the first set or if 
 * an epsilon transition is possible for the given function name. If neither condition is met, it outputs a 
 * syntax error message and continues to fetch the next token until a valid token is found in either the first 
 * or follow set. If an epsilon transition is possible and the token is in the follow set, parsing is aborted.
 *
 * @param funcName The name of the function whose first and follow sets are to be checked.
 * @return true if the error was successfully skipped and parsing can continue, false if parsing is aborted.
 */
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
    AST* startS = nullptr;
    if(start(&startS) && match(TokenType::ENDOFILE)){
        std::cout<<""<<std::endl;
        outDerivation << "Parsing Ended \n";
        ast = startS;
        return true;}
    else { 
        std::cout << "Syntax error: "<<lookAhead.getLexeme() <<" Type: "<<lookAhead.getType() << " on line "<<lookAhead.getLine() << std::endl;
        return false; }
    

}

bool Parser::start(AST** startS){
    
    if(checkFirstSet("START", 0)) {
        AST* progS = nullptr;
        if(prog(&progS)){
            AST* classimplfuncList = ASTFactory::makeFamily(compositeConcept::CLASSIMPLFUNCLIST, { progS });
            AST* progSub = ASTFactory::makeFamily(compositeConcept::PROG, { classimplfuncList });
            *startS = ASTFactory::makeFamily(compositeConcept::START, { progSub });
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

bool Parser::prog(AST** progS){
    bool success = false;
    //////if (!skipErrors("PROG"))return false;
    if(checkFirstSet("PROG", 0)) {
        AST* classImplFuncS = nullptr;
        AST* classImplFuncSiblings = nullptr;
        if(classimplfunc(&classImplFuncS) && prog(&classImplFuncSiblings)){

            if (classImplFuncSiblings) {
                classImplFuncS->makeSiblings(classImplFuncSiblings);
            }
            *progS = classImplFuncS;
            
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

bool Parser::classimplfunc(AST** classImplFuncS){
    bool success = false;
    //if(!skipErrors("CLASSIMPLFUNC"))return false;

    if(checkFirstSet("CLASSIMPLFUNC", 0)) {
        AST* classDeclS = nullptr;
        if(classdecl(&classDeclS)){
            *classImplFuncS = classDeclS;
            std::cout << "CLASSIMPLFUNC -> CLASSDEC" << std::endl;
            outDerivation << "CLASSIMPLFUNC -> CLASSDECL\n";
            success = true;
        }
    }
    else if(checkFirstSet("CLASSIMPLFUNC", 1)){
        AST* implDefS = nullptr;
        if(impldef(&implDefS)){
            *classImplFuncS = implDefS;
            std::cout << "CLASSIMPLFUNC -> IMPLDEF" << std::endl;
            outDerivation << "CLASSIMPLFUNC -> IMPLDEF \n";
            success = true;
        }

    }
    else if(checkFirstSet("CLASSIMPLFUNC", 2)){
        AST* funcDefS = nullptr;
        if(funcdef(&funcDefS)){
            *classImplFuncS = funcDefS;
            std::cout << "CLASSIMPLFUNC -> FUNCDEF" << std::endl;
            outDerivation << "CLASSIMPLFUNC -> FUNCDEF\n";
            success = true;
        }
    }
    else {}

    return success;
};
//check the conditions of the first set for this declaration
bool Parser::classdecl(AST** classDeclS){
    bool success = false;
    //////if (!skipErrors("CLASSDECL")) return false;
    if (checkFirstSet("CLASSDECL", 0)) {
        AST* isaS = nullptr;
        AST* visMemberDeclS = nullptr;
            if (match(TokenType::CLASS) && match(TokenType::ID) && isa1(&isaS) && match(TokenType::OPENCURLY)
                && vismemberdecl(&visMemberDeclS) && match(TokenType::CLOSECURLY) && match(TokenType::SEMICOLON)) {
                AST* classID = attrStack.top(); attrStack.pop();
                AST* isaList = nullptr;
                if (isaS) {
                    isaList = ASTFactory::makeFamily(compositeConcept::ISALIST, { isaS });
                }
                AST* visMemberDeclList = ASTFactory::makeFamily(compositeConcept::VISMEMBERDECLLIST, { visMemberDeclS });
                *classDeclS = ASTFactory::makeFamily(compositeConcept::CLASSDECL, { classID, isaList, visMemberDeclList });

                std::cout << "CLASSDECL -> CLASS ID ISA1 OPENCURLY VSEMEMBERDECL CLOSECURLY SEMICOLON" << std::endl;
                outDerivation << "CLASSDECL -> CLASS ID ISA1 OPENCURLY VSEMEMBERDECL CLOSECURLY SEMICOLON \n";
                success = true;
            }
        }
    return success;
};

bool Parser::vismemberdecl(AST** visMemberDeclS) {
    bool success = false;
    //////if (!skipErrors("VISMEMBERDECL")) return false;
    if (checkFirstSet("VISMEMBERDECL", 0)) {
        AST* visbilityS = nullptr;
        AST* memDeclS = nullptr;
        AST* visMemberSiblings = nullptr;
        if (visibility(&visbilityS) && memdecl(&memDeclS) && vismemberdecl(&visMemberSiblings)) {

            *visMemberDeclS = ASTFactory::makeFamily(compositeConcept::VISMEMBERDECL, { visbilityS, memDeclS });
            if (visMemberSiblings) {
                (*visMemberDeclS)->makeSiblings(visMemberSiblings);
            }

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

bool Parser::isa1(AST** isa1S) {
    bool success = false;
    //////if (!skipErrors("ISA1")) return false;
    if (checkFirstSet("ISA1", 0)) {
        AST* isa2S = nullptr;
        if (match(TokenType::ISA) && match(TokenType::ID) && isa2(&isa2S)) {
            *isa1S = attrStack.top(); attrStack.pop();
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

bool Parser::isa2(AST** isa2S) {
    bool success = false;
    //////if (!skipErrors("ISA2")) return false;
    if (checkFirstSet("ISA2", 0)) {
        AST* isaSibling = nullptr;
        if (match(TokenType::COMMA) && match(TokenType::ID) && isa2(&isaSibling)) {
            *isa2S = attrStack.top(); attrStack.pop();
            
            if (isaSibling) {
                (*isa2S)->makeSiblings(isaSibling);
            }

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

bool Parser::impldef(AST** implDefS) {
    bool success = false;
    ////if (!skipErrors("IMPLDEF")) return false;
    if (checkFirstSet("IMPLDEF", 0)) {
        AST* implBodyS = nullptr;
        if (match(TokenType::IMPLEMENTATION) && match(TokenType::ID) && match(TokenType::OPENCURLY) && implbody(&implBodyS) && match(TokenType::CLOSECURLY)) {
            AST* implID = attrStack.top(); attrStack.pop();
            AST* implBodyTemp = ASTFactory::makeFamily(compositeConcept::IMPLBODY, { implBodyS });
            *implDefS = ASTFactory::makeFamily(compositeConcept::IMPLDEF, { implID, implBodyTemp });
            std::cout << "IMPLDEF -> IMPLEMENTATION ID OPENCURLY IMPLBODY CLOSECURLY" << std::endl;
            outDerivation << " IMPLDEF -> IMPLEMENTATION ID OPENCURLY IMPLBODY CLOSECURLY \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}


bool Parser::implbody(AST** implBodyS) {
    bool success = false;
    ////if (!skipErrors("IMPLBODY")) return false;
    if (checkFirstSet("IMPLBODY", 0)) {
        AST* funcDefS = nullptr;
        AST* implBodySiblings = nullptr;
        if (funcdef(&funcDefS) && implbody(&implBodySiblings)) {
            *implBodyS =  funcDefS ;

            if (implBodySiblings) {
                (*implBodyS)->makeSiblings(implBodySiblings);
            }
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

bool Parser::funcdef(AST** funcDefS) {
    bool success = false;
    ////if (!skipErrors("FUNCDEF")) return false;
    if (checkFirstSet("FUNCDEF", 0)) {
        AST* funcHead = nullptr;
        AST* funcBody = nullptr;
        if (funchead(&funcHead) && funcbody(&funcBody)) {
            *funcDefS = ASTFactory::makeFamily(compositeConcept::FUNCDEF, { funcHead, funcBody });
            std::cout << "FUNCDEF -> FUNCHEAD FUNCBODY" << std::endl;
            outDerivation << "FUNCDEF -> FUNCHEAD FUNCBODY \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::visibility(AST** visibilityS) {
    bool success = false;
    ////if (!skipErrors("VISIBILITY")) return false;
    if (checkFirstSet("VISIBILITY", 0)) {
        if (match(TokenType::PUBLIC)) {
            *visibilityS = attrStack.top(); attrStack.pop();
            std::cout << "VISIBILITY -> PUBLIC" << std::endl;
            outDerivation << "VISIBILITY -> PUBLIC \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("VISIBILITY", 1)) {
        if (match(TokenType::PRIVATE)) {
            *visibilityS = attrStack.top(); attrStack.pop();
            std::cout << "VISIBILITY -> PRIVATE" << std::endl;
            outDerivation << "VISIBILITY -> PRIVATE \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::memdecl(AST** memDeclS) {
    bool success = false;
    ////if (!skipErrors("MEMDECL")) return false;
    if (checkFirstSet("MEMDECL", 0)) {
        AST* funcDecl = nullptr;
        if (funcdecl(&funcDecl)) {
            *memDeclS = funcDecl;
            std::cout << "MEMDECL -> FUNCDECL" << std::endl;
            outDerivation << "MEMDECL -> FUNCDECL\n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("MEMDECL", 1)) {
        AST* attrDecl = nullptr;
        if (attrdecl(&attrDecl)) {
            *memDeclS = attrDecl;
            std::cout << "MEMDECL -> ATTRDECL" << std::endl;
            outDerivation << "MEMDECL -> ATTRDECL\n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcdecl(AST** funcDecl) {
    bool success = false;
    ////if (!skipErrors("FUNCDECL")) return false;
    if (checkFirstSet("FUNCDECL", 0)) {
        AST* funcHead = nullptr;
        if (funchead(&funcHead) && match(TokenType::SEMICOLON)) {

            *funcDecl = ASTFactory::makeFamily(compositeConcept::FUNCDECL, { funcHead });

            std::cout << "FUNCDECL -> FUNCHEAD SEMICOLON" << std::endl;
            outDerivation << "FUNCDECL -> FUNCHEAD SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funchead(AST** funcHead) {
    bool success = false;
    ////if (!skipErrors("FUNCHEAD")) return false;
    if (checkFirstSet("FUNCHEAD", 0)) {
        AST* fParamsAST = nullptr;

        if (match(TokenType::CONSTRUCTOR) && match(TokenType::OPENPAR) && fParams(&fParamsAST) && match(TokenType::CLOSEPAR)) {
            AST* construct = attrStack.top(); attrStack.pop();

            *funcHead = ASTFactory::makeFamily(compositeConcept::FUNCHEAD, { construct, fParamsAST });
            std::cout << "CONSTRUCTOR OPENPAR FPARAMS CLOSEPAR" << std::endl;
            outDerivation << " CONSTRUCTOR OPENPAR FPARAMS CLOSEPAR \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("FUNCHEAD", 1)) {
        AST* fParamsAST = nullptr;
        AST* returnTypeAST = nullptr;
        if (match(TokenType::FUNCTION) && match(TokenType::ID) && match(TokenType::OPENPAR) && fParams(&fParamsAST) && match(TokenType::CLOSEPAR) &&
            match(TokenType::ARROW) && returnType(&returnTypeAST)) {
            AST* funcID = attrStack.top(); 
            attrStack.pop(); 

            *funcHead = ASTFactory::makeFamily(compositeConcept::FUNCHEAD, { funcID, fParamsAST, returnTypeAST });
            std::cout << "FUNCTION ID OPENPAR FPARAMS CLOSEPAR ARROW RETURNTYPE" << std::endl;
            outDerivation << "FUNCTION ID OPENPAR FPARAMS CLOSEPAR ARROW RETURNTYPE \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcbody(AST** funcBodyS) {
    bool success = false;
    //if (!skipErrors("FUNCBODY")) return false;
    if (checkFirstSet("FUNCBODY", 0)) {
        AST* LocalVarDeclOrStat = nullptr;
        if (match(TokenType::OPENCURLY) && localvardeclorstat2(&LocalVarDeclOrStat) && match(TokenType::CLOSECURLY)) {
            AST* LocalVarDeclOrStatList = nullptr;
            if (LocalVarDeclOrStat) {
                LocalVarDeclOrStatList = ASTFactory::makeFamily(compositeConcept::LOCALVARDECLORSTATLIST, { LocalVarDeclOrStat });
            }
            *funcBodyS = ASTFactory::makeFamily(compositeConcept::FUNCBODY, { LocalVarDeclOrStatList });
            std::cout << "OPENPAR LOCALVARDECLORSTAT2 CLOSEPAR" << std::endl;
            outDerivation << "OPENPAR LOCALVARDECLORSTAT2 CLOSEPAR \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}
bool Parser::localvardeclorstat2(AST** LocalVarDeclOrStat) {
    bool success = false;
    //if (!skipErrors("LOCALVARDECLORSTAT2")) return false;
    if (checkFirstSet("LOCALVARDECLORSTAT2", 0)) {
        AST* LocalVarDeclOrStatSiblings = nullptr;
        AST* LocalVarDeclOrStatcurr = nullptr;
        if (localvardeclorstat(&LocalVarDeclOrStatcurr) && localvardeclorstat2(&LocalVarDeclOrStatSiblings)) {
            
            
            if (LocalVarDeclOrStatcurr == nullptr) {
                std::cout << "its empty" << std::endl;
            }
            LocalVarDeclOrStatcurr->makeSiblings(LocalVarDeclOrStatSiblings);
            *LocalVarDeclOrStat = LocalVarDeclOrStatcurr;


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

bool Parser::localvardeclorstat(AST** LocalVarDeclOrStat) {
    bool success = false;
    //if (!skipErrors("LOCALVARDECLORSTAT")) return false;
    if (checkFirstSet("LOCALVARDECLORSTAT", 0)) {
        AST* localVarDecl = nullptr; 
        if (localvardecl(&localVarDecl)) {
            if (localVarDecl == nullptr) {
                std::cout << "local Vardecl empty" << std::endl;
            }
            *LocalVarDeclOrStat = localVarDecl;
            std::cout << "LOCALVARDECLORSTAT -> LOCALVARDECL" << std::endl;
            outDerivation << "LOCALVARDECLORSTAT -> LOCALVARDECL \n";
            success = true;
        }
    }
    else if (checkFirstSet("LOCALVARDECLORSTAT", 1)) {
        AST* statementAST = nullptr;
        if (statement(&statementAST)) {
            if (statementAST == nullptr) {
                std::cout << "statement pointer empty" << std::endl;
            }
            *LocalVarDeclOrStat = statementAST;
            std::cout << "LOCALVARDECLORSTAT -> STATEMENT" << std::endl;
            outDerivation << "LOCALVARDECLORSTAT -> STATEMENT \n";
            success = true;
        }
         
    }
    else {}
    return success;

}
 


bool Parser::attrdecl(AST** attrDeclS) {
    bool success = false;
    //if (!skipErrors("ATTRDECL")) return false;
    if (checkFirstSet("ATTRDECL", 0)) {
        AST* varDecl = nullptr;
        if (match(TokenType::ATTRIBUTE) && vardecl(&varDecl)) {
            *attrDeclS = ASTFactory::makeFamily(compositeConcept::ATTRDECL, { varDecl });
            std::cout << "ATTRDECL -> ATTRIBUTE VARDECL " << std::endl;
            outDerivation << "ATTRDECL -> ATTRIBUTE VARDECL \n";
            success = true;
        }
    }
    return success;
}

bool Parser::localvardecl(AST** localVarDecl) {
    bool success = false;
    //if (!skipErrors("LOCALVARDECL")) return false;
    if (checkFirstSet("LOCALVARDECL", 0)) {
        AST* varDecl = nullptr;
        if (match(TokenType::LOCAL) && vardecl(&varDecl)) {
            *localVarDecl = ASTFactory::makeFamily(compositeConcept::LOCALVARDECL, { varDecl });
            std::cout << "LOCALVARDECL -> LOCAL VARDECL" << std::endl;
            outDerivation << "LOCALVARDECL -> LOCAL VARDECL \n";
            success = true;
        }
    }
    else {}
    return success;
}

bool Parser::vardecl(AST** varDecl) {
    bool success = false;
    //if (!skipErrors("VARDECL")) return false;
    if (checkFirstSet("VARDECL", 0)) {
        AST* typeAST = nullptr;
        AST* arraySizeAST = nullptr;
        if (match(TokenType::ID) && match(TokenType::COLON) && type(&typeAST) && arraySizes(&arraySizeAST) && match(TokenType::SEMICOLON)) {
            AST* varID = attrStack.top(); attrStack.pop();
            AST* arraySizeList = nullptr;

            if (arraySizeAST) {
                arraySizeList = ASTFactory::makeFamily(compositeConcept::ARRAYSIZELIST, { arraySizeAST });
            }

            *varDecl = ASTFactory::makeFamily(compositeConcept::VARDECL, { varID, typeAST, arraySizeList });

            std::cout << "VARDECL -> ID COLON TYPE ARRAYSIZES SEMICOLON" << std::endl;
            outDerivation << "VARDECL -> ID COLON TYPE ARRAYSIZES SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::statement(AST** statementAST) {
    bool success = false;
    //if (!skipErrors("STATEMENT")) return false;
    if (checkFirstSet("STATEMENT", 0)) {
        AST* funcOrAssignStatS = nullptr;
        if (funcallorassign(&funcOrAssignStatS) && match(TokenType::SEMICOLON)) {
            AST* tempStatement = nullptr;
            tempStatement = funcOrAssignStatS;
            *statementAST = ASTFactory::makeFamily(compositeConcept::STATEMENT, { tempStatement });
            std::cout << "STATEMENT -> FUNCALLAORASSIGN SEMICOLON " << std::endl;
            outDerivation << "STATEMENT -> FUNCALLAORASSIGN SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATEMENT", 1)) {
        AST* writeExpr = nullptr;
        if (match(TokenType::WRITE) && match(TokenType::OPENPAR) && expr(&writeExpr) && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)) {
            AST* tempStatement = nullptr;
            tempStatement = ASTFactory::makeFamily(compositeConcept::WRITESTAT, { writeExpr });
            *statementAST = ASTFactory::makeFamily(compositeConcept::STATEMENT, { tempStatement });
            std::cout << "STATEMENT -> WRITE OPENPAR EXPR CLOSEPAR SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> WRITE OPENPAR EXPR CLOSEPAR SEMICOLON \n";
            success = true;
        }
        else success = false;

    }
    else if (checkFirstSet("STATEMENT", 2)) {
        AST* whileExpr = nullptr;
        AST* whileBody = nullptr;

        if (match(TokenType::WHILE) && match(TokenType::OPENPAR) && relexpr(&whileExpr) && match(TokenType::CLOSEPAR)
            && statblock(&whileBody) && match(TokenType::SEMICOLON)) {
            AST* tempStatement = nullptr;
            tempStatement = ASTFactory::makeFamily(compositeConcept::WHILESTAT, { whileExpr, whileBody });
            *statementAST = ASTFactory::makeFamily(compositeConcept::STATEMENT, { tempStatement });
            std::cout << "STATEMENT -> WHILE OPENPAR RELEXPR CLOSEPAR STATBLOCK SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> WHILE OPENPAR RELEXPR CLOSEPAR STATBLOCK SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATEMENT", 3)) {
        AST* returnExpr = nullptr;
        if (match(TokenType::RETURN) && match(TokenType::OPENPAR) && expr(&returnExpr) && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)) {
            AST* tempStatement = nullptr;
            tempStatement = ASTFactory::makeFamily(compositeConcept::RETURNSTAT, { returnExpr });
            *statementAST = ASTFactory::makeFamily(compositeConcept::STATEMENT, { tempStatement });
            std::cout << "STATEMENT -> RETURN OPENPAR EXPR CLOSEPAR SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> RETURN OPENPAR EXPR CLOSEPAR SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATEMENT", 4)) {
        AST* var = nullptr;
        if (match(TokenType::READ) && match(TokenType::OPENPAR) && variable(&var) && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)) {
            AST* tempStatement = nullptr;
            tempStatement = ASTFactory::makeFamily(compositeConcept::READSTAT, { var });
            *statementAST = ASTFactory::makeFamily(compositeConcept::STATEMENT, { tempStatement });

            std::cout << "STATEMENT -> READ OPENPAR VARIABLE CLOSEPAR SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> READ OPENPAR VARIABLE CLOSEPAR SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATEMENT", 5)) {
        AST* ifExpr = nullptr;
        AST* thenBody = nullptr;
        AST* elseBody = nullptr;
        if (match(TokenType::IF) && match(TokenType::OPENPAR) && relexpr(&ifExpr) && match(TokenType::CLOSEPAR)
            && match(TokenType::THEN) && statblock(&thenBody) && match(TokenType::ELSE) && statblock(&elseBody) && match(TokenType::SEMICOLON)) {
            AST* tempStatement = nullptr;
            tempStatement = ASTFactory::makeFamily(compositeConcept::IFSTAT, { ifExpr, thenBody, elseBody });
            *statementAST = ASTFactory::makeFamily(compositeConcept::STATEMENT, { tempStatement });
            std::cout << "STATEMENT -> IF OPENPAR RELEXPR CLOSEPAR THEN STATBLOCK ELSE STATBLOCK SEMICOLON" << std::endl;
            outDerivation << "STATEMENT -> IF OPENPAR RELEXPR CLOSEPAR THEN STATBLOCK ELSE STATBLOCK SEMICOLON \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcallorassign(AST** funcOrAssignStatS) {
    bool success = false;
    //if (!skipErrors("FUNCALLORASSIGN")) return false;
    if (checkFirstSet("FUNCALLORASSIGN", 0)) {
        AST* idorSelf = nullptr;
        AST* funcOrAssignStat2 = nullptr;
        if (idOrSelf(&idorSelf) && funcallorassign2(&funcOrAssignStat2, idorSelf)) {

            *funcOrAssignStatS = funcOrAssignStat2;

            std::cout << "FUNCALLORASSIGN -> IDORSELF FUNCALLORASSIGN2" << std::endl;
            outDerivation << "FUNCALLORASSIGN -> IDORSELF FUNCALLORASSIGN2 \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcallorassign2(AST** funcOrAssignStatSNest, AST* leftVar) {
    bool success = false;
    //if (!skipErrors("FUNCALLORASSIGN2")) return false;
    if (checkFirstSet("FUNCALLORASSIGN2", 0)) {
        AST* indiceRept = nullptr;
        AST* varOrFuncNest = nullptr;
        if (indices(&indiceRept)) {
            AST* indiceList = nullptr;
            if (indiceRept) {
                indiceList = ASTFactory::makeFamily(compositeConcept::ARRAYSIZELIST, { indiceRept });
                leftVar = ASTFactory::makeFamily(compositeConcept::VARIABLE, { leftVar, indiceList });
            }
            
            
            if (funcasllorassign3(funcOrAssignStatSNest, leftVar)) {
                std::cout << "funcallorassign2 called with funcOrAssignStatSNest = " << funcOrAssignStatSNest << std::endl;
                std::cout << "FUNCALLORASSIGN2 -> INDICES FUNCALLORASSIGN3" << std::endl;
                outDerivation << "FUNCALLORASSIGN2 -> INDICES FUNCALLORASSIGN3 \n";
                success = true;
            }
        }
        else success = false;
    }
    else if (checkFirstSet("FUNCALLORASSIGN2", 1)) {
        AST* aParamsS = nullptr;
        AST* funCallNest = nullptr;
        if (match(TokenType::OPENPAR) && aParams(&aParamsS) && match(TokenType::CLOSEPAR)) {
            AST* funCallS = ASTFactory::makeFamily(compositeConcept::FUNCCALL, { leftVar, aParamsS });

            if (funcallorassign4(funcOrAssignStatSNest, funCallS)) {
                std::cout << "FUNCALLORASSIGN2 -> OPENPAR AAPARMS CLOSEPAR FUNCALLORASSIGN4" << std::endl;
                outDerivation << "FUNCALLORASSIGN2 -> OPENPAR AAPARMS CLOSEPAR FUNCALLORASSIGN4 \n";
                success = true;
            }
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::funcasllorassign3(AST** assignOrNest, AST* leftVar) {
    bool success = false;
    //if (!skipErrors("FUNCALLORASSIGN3")) return false;
    if (checkFirstSet("FUNCALLORASSIGN3", 0)) {
        AST* assignOpAST = nullptr;
        AST* exprS = nullptr;

        if (assignOp(&assignOpAST) && expr(&exprS)) {
            
            //AST* tempAssign = ASTFactory::makeFamily(compositeConcept::ASSIGNSTAT, { assignOpAST, exprS });
            leftVar->makeSiblings(assignOpAST);
            leftVar->makeSiblings(exprS);
            *assignOrNest = ASTFactory::makeFamily(compositeConcept::ASSIGNSTAT, { leftVar });
            
            std::cout << "FUNCALLORASSIGN3 -> ASSIGNOP EXPR" << std::endl;
            outDerivation << "FUNCALLORASSIGN3 -> ASSIGNOP EXPR \n";
            success = true;
        }
    }
    else if (checkFirstSet("FUNCALLORASSIGN3", 1)) {
        AST* funcOrAssignNest = nullptr;
        if (match(TokenType::DOT) && match(TokenType::ID)){
            AST* varID = attrStack.top(); attrStack.pop();
            AST* dot = attrStack.top(); attrStack.pop();
            ASTFactory::makeFamily(dot, { leftVar, varID });
            if (funcallorassign2(&funcOrAssignNest, dot)){
                
                    *assignOrNest = funcOrAssignNest;


                    std::cout << "FUNCALLORASSIGN3 -> DOT ID FUNCALLORASSIGN2" << std::endl;
                    outDerivation << "FUNCALLORASSIGN3 -> DOT ID FUNCALLORASSIGN2 \n";
                    success = true;
            }
        }
    }
    else {}
    return success;
}

bool Parser::funcallorassign4(AST** funcNest, AST* leftVar) {
    bool success = false;
    //if (!skipErrors("FUNCALLORASSIGN4")) return false;
    if (checkFirstSet("FUNCALLORASSIGN4", 0)) {
        AST* funcOrAssignNest = nullptr;
        if (match(TokenType::DOT) && match(TokenType::ID) && funcallorassign2(&funcOrAssignNest, attrStack.top())) {
            AST* varID = attrStack.top(); attrStack.pop();
            AST* dot = attrStack.top(); attrStack.pop();
            ASTFactory::makeFamily(dot, { leftVar, funcOrAssignNest });
            *funcNest = funcOrAssignNest;

            std::cout << "FUNCALLORASSIGN4 -> DOT ID FUNCALLORASSIGN2" << std::endl;
            outDerivation << "FUNCALLORASSIGN4 -> DOT ID FUNCALLORASSIGN2 \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFollowSet("FUNCALLORASSIGN4")) {
        *funcNest = leftVar;
        std::cout << "FUNCALLORASSIGN4 -> EPSILON" << std::endl;
        outDerivation << "FUNCALLORASSIGN4 -> EPSILON \n";
        success = true;
    }
    else success = false;
    return success;
}

bool Parser::statblock(AST** statBlock) {
    bool success = false;

    //if (!skipErrors("STATBLOCK")) return false;

    if (checkFirstSet("STATBLOCK", 0)) {
        AST* statementAST = nullptr;
        if (statement(&statementAST)) {
            *statBlock = ASTFactory::makeFamily(compositeConcept::STATEMENTLIST, { statementAST });
            std::cout << "STATBLOCK -> STATEMENT" << std::endl;
            outDerivation << "STATBLOCK -> STATEMENT \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFirstSet("STATBLOCK", 1)) {
        AST* statementList = nullptr;
        if (match(TokenType::OPENCURLY) && statements(&statementList) && match(TokenType::CLOSECURLY)) {
            *statBlock = ASTFactory::makeFamily(compositeConcept::STATEMENTLIST, { statementList });
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


bool Parser::statements(AST** statementList) {
    bool success = false;
    //if (!skipErrors("STATEMENTS")) return false;
    if (checkFirstSet("STATEMENTS", 0)) {
        AST* statementAST = nullptr;
        AST* statementListSibling = nullptr;
        if (statement(&statementAST) && statements(&statementListSibling)) {
            statementAST->makeSiblings(statementListSibling);
            *statementList = statementAST;
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

bool Parser::expr(AST** exprS) {
    bool success = false;
    //if (!skipErrors("EXPR")) return false;

    if (checkFirstSet("EXPR", 0)) {
        AST* arithExprFirst = nullptr;
        if (arithexpr(&arithExprFirst) && expr2(exprS, arithExprFirst)) {
            std::cout << "EXPR -> ARITHEXPR EXPR2" << std::endl;
            outDerivation << "EXPR -> ARITHEXPR EXPR2 \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    
    return success;
}

bool Parser::expr2(AST** exprRest, AST* arithExprFirst) {
    bool success = false;
    //if (!skipErrors("EXPR2"))return false;
    if (checkFirstSet("EXPR2", 0)) {
        AST* relOpAST = nullptr;
        AST* restArithExpr = nullptr;
        if (relOp(&relOpAST) && arithexpr(&restArithExpr)) {
            ASTFactory::makeFamily(relOpAST, { arithExprFirst, restArithExpr });
            *exprRest = relOpAST;
            std::cout << "EXPR2 -> RELOP ARITHEXPR" << std::endl;
            outDerivation << "EXPR2 -> RELOP ARITHEXPR \n";
            success = true;
        }
        else success = false;
    }
    else if (checkFollowSet("EXPR2")) {
        *exprRest = arithExprFirst;
        std::cout << "EXPR2 -> EPSILON" << std::endl;
        outDerivation << "EXPR2 -> EPSILON \n";
        success = true;
    }
    else success = false;

    return success;
}

bool Parser::relexpr(AST** relExprS) {
    bool success = false;
    //if (!skipErrors("RELEXPR")) return false;

    if (checkFirstSet("RELEXPR", 0)) {
        AST* leftArithExpr = nullptr;
        AST* relOpS = nullptr;
        AST* rightArithExpr = nullptr;
        if (arithexpr(&leftArithExpr) && relOp(&relOpS) && arithexpr(&rightArithExpr)) {
            ASTFactory::makeFamily(relOpS, { leftArithExpr, rightArithExpr });
            *relExprS = relOpS;
            std::cout << "RELEXPR -> ARITHEXPR RELOP ARITHEXPR" << std::endl;
            outDerivation << "RELEXPR -> ARITHEXPR RELOP ARITHEXPR \n";
            success = true;
        }
        else success = false;
    }
    else success = false;
    return success;
}

bool Parser::arithexpr(AST** arithExprS) {
    bool success = false;
    //if (!skipErrors("ARITHEXPR")) return false;

    if (checkFirstSet("ARITHEXPR", 0)) {

        AST* leftTerm = nullptr;
        AST* arithExprRest = nullptr;
        if (term(&leftTerm) && rightrecarithexpr(arithExprS, leftTerm)) {

            std::cout << "ARITHEXPR -> TERM RIGHTRECARITHEXPR" << std::endl;
            outDerivation << "ARITHEXPR -> TERM RIGHTRECARITHEXPR \n";
            success = true;
        }
    }
    return success;
}

bool Parser::rightrecarithexpr(AST** arithExprRest, AST* leftTerm) {
    bool success = false;
    //if (!skipErrors("RIGHTRECARITHEXPR"))return false;

    if (checkFirstSet("RIGHTRECARITHEXPR", 0)) {
        AST* addOpAST = nullptr;
        AST* rightTerm = nullptr;
        AST* rightTermRest = nullptr;
        if (addOp(&addOpAST) && term(&rightTerm) && rightrecarithexpr(&rightTermRest, rightTerm)) {

            ASTFactory::makeFamily(addOpAST, { leftTerm, rightTermRest });
            *arithExprRest = addOpAST;
            std::cout << "RIGHTRECARITHEXPR -> ADDOP TERM RIGHTRECARITHEXPR" << std::endl;
            outDerivation << "RIGHTRECARITHEXPR -> ADDOP TERM RIGHTRECARITHEXPR \n";
            success = true;
        }

    }
    else if (checkFollowSet("RIGHTRECARITHEXPR")) {
        *arithExprRest = leftTerm;
        std::cout << "RIGHTRECARITHEXPR -> EPSILON" << std::endl;
        outDerivation << "RIGHTRECARITHEXPR -> EPSILON \n";
        success = true;
    }

    return success;
}


bool Parser::sign(AST** signS) {
    bool success = false;
    //if (!skipErrors("SIGN")) return false;

    if (checkFirstSet("SIGN", 0)) {
        if (match(TokenType::ADD)) {
            *signS = attrStack.top(); attrStack.pop();
            std::cout << "SIGN -> ADD" << std::endl;
            outDerivation << "SIGN -> ADD \n";
            success = true;
        }
    }
    else if (checkFirstSet("SIGN", 1)) {
        if (match(TokenType::SUBT)) {
            *signS = attrStack.top(); attrStack.pop();
            std::cout << "SIGN -> SUBT" << std::endl;
            outDerivation << "SIGN -> SUBT \n";
            success = true;
        }
    }
    return success;
}

bool Parser::term(AST** termS) {
    bool success = false;
    //if (!skipErrors("TERM")) return false;

    if (checkFirstSet("TERM", 0)) {
        AST* leftFactor = nullptr;
        AST* termRest = nullptr;
        if (factor(&leftFactor, nullptr) && rightrecterm(&termRest, leftFactor)) {
            *termS = termRest;
            std::cout << "TERM -> FACTOR RIGHTRECTERM" << std::endl;
            outDerivation << "TERM -> FACTOR RIGHTRECTERM \n";
            success = true;
        }

    }
    return success;
}

bool Parser::rightrecterm(AST** termTail, AST* leftFactor) {
    bool success = false;
    //if (!skipErrors("RIGHTRECTERM")) return false;

    if (checkFirstSet("RIGHTRECTERM", 0)) {
        AST* multOpAST = nullptr;
        AST* rightFactor = nullptr;
        AST* termTailRest = nullptr;
        if (multOp(&multOpAST) && factor(&rightFactor, nullptr) && rightrecterm(&termTailRest, rightFactor)) {

            ASTFactory::makeFamily(multOpAST, { leftFactor, termTailRest });
            *termTail = multOpAST;

            std::cout << "RIGHTRECTERM -> MULTOP FACTOR RIGHTRECTERM" << std::endl;
            outDerivation << "RIGHTRECTERM -> MULTOP FACTOR RIGHTRECTERM \n";
            success = true;
        }

    }
    else if (checkFollowSet("RIGHTRECTERM")) {
        *termTail = leftFactor;
        std::cout << "RIGHTRECTERM -> EPSILON" << std::endl;
        outDerivation << "RIGHTRECTERM -> EPSILON \n";
        success = true;
    }
    
    return success;
}

bool Parser::factor(AST** factorS, AST* leftFactor) {
    bool success = false;
    //if (!skipErrors("FACTOR"))return false;

    if (checkFirstSet("FACTOR", 0)) {
        AST* signS = nullptr;
        AST* factorSibling = nullptr;
        if (sign(&signS) && factor(&factorSibling, leftFactor)) {
            ASTFactory::makeFamily(signS, { leftFactor, factorSibling });
            *factorS = signS;
            std::cout << "FACTOR -> SIGN FACTOR" << std::endl;
            outDerivation << "FACTOR -> SIGN FACTOR \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 1)) {
        AST* idorSelf = nullptr;
        AST* factor2S = nullptr;
        AST* factoRest = nullptr;
        if (idOrSelf(&idorSelf) && factor2(&factor2S, idorSelf) && reptvariableorfunctioncall(&factoRest, factor2S)) {
            *factorS = factoRest;
            std::cout << "FACTOR -> IDORSELF FACTOR2 REPTVARIABLEORFUNCTIONCALL" << std::endl;
            outDerivation << "FACTOR -> IDORSELF FACTOR2 REPTVARIABLEORFUNCTIONCALL \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 2)) {
        AST* Factor = nullptr;
        if (match(TokenType::NOT) && factor(&Factor, nullptr)) {
            AST * not = attrStack.top(); attrStack.pop();
            not->adoptChild(Factor);
            *factorS = not;
            std::cout << "FACTOR -> NOT FACTOR" << std::endl;
            outDerivation << "FACTOR -> NOT FACTOR \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 3)) {
        if (match(TokenType::INTEGER_VAL)) {
            *factorS = attrStack.top(); attrStack.pop();
            std::cout << "FACTOR -> INTEGER LITERAL" << std::endl;
            outDerivation << "FACTOR -> INTEGER LITERAL \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 4)) {
        if (match(TokenType::FLOAT_VAL)) {
            *factorS = attrStack.top(); attrStack.pop();
            std::cout << "FACTOR -> FLOAT LITERAL" << std::endl;
            outDerivation << "FACTOR -> FLOAT LITERAL \n";
            success = true;
        }
    }
    else if (checkFirstSet("FACTOR", 5)) {
        AST* arithExprS = nullptr;
        if (match(TokenType::OPENPAR) && arithexpr(&arithExprS) && match(TokenType::CLOSEPAR)) {
            *factorS = arithExprS;
            std::cout << "FACTOR -> OPENPAR ARITHEXPR CLOSEPAR" << std::endl;
            outDerivation << "FACTOR -> OPENPAR ARITHEXPR CLOSEPAR \n";
            success = true;
        }
    }
    else success = false;
    return success;
}

bool Parser::factor2(AST** factorContinue, AST* leftVar) {
    bool success = false;

    //if (!skipErrors("FACTOR2"))return false;

    if (checkFirstSet("FACTOR2", 0)) {
        AST* indiceRept = nullptr;
        AST* funcOrVarNest = nullptr;
        if (indices(&indiceRept)) {
            AST* indiceList = nullptr;
            if (indiceRept) {
                indiceList = ASTFactory::makeFamily(compositeConcept::INDICELIST, { indiceRept });
            }
            AST* varS = ASTFactory::makeFamily(compositeConcept::VARIABLE, { leftVar, indiceList });
            *factorContinue = varS;

            std::cout << "FACOTR2 -> INDICES" << std::endl;
            outDerivation << "FACOTR2 -> INDICES \n";
            success = true;
        }
        
    }
    else if (checkFirstSet("FACTOR2", 1)) {
        AST* aParamsS = nullptr;
        if (match(TokenType::OPENPAR) && aParams(&aParamsS) && match(TokenType::CLOSEPAR)) {
            AST* funcCall = ASTFactory::makeFamily(compositeConcept::VARORFUNCTIONCALLLIST, { leftVar, aParamsS });
            *factorContinue = funcCall;
            std::cout << "FACTOR2 -> OPENPAR APARAMS CLOSEPAR" << std::endl;
            outDerivation << "FACTOR2 -> OPENPAR APARAMS CLOSEPAR \n";
            success = true;
        }
    }
    else if (checkFollowSet("FACTOR2")) {
        *factorContinue = leftVar;
        std::cout << "FACTOR2 -> EPSILON" << std::endl;
        outDerivation << "FACTOR2 -> EPSILON \n";
        success = true;
    }

    return success;
}

bool Parser::indices(AST** indiceRept) {
    bool success = false;

    //if (!skipErrors("INDICES"))return false;

    if (checkFirstSet("INDICES", 0)) {
        AST* indiceAST = nullptr;
        AST* indiceSiblings = nullptr;
        if (indice(&indiceAST) && indices(&indiceSiblings)) {
            if (indiceSiblings) {
                indiceAST->makeSiblings(indiceSiblings);
            }
            *indiceRept = indiceAST;
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

bool Parser::reptvariableorfunctioncall(AST** varOrFunc, AST* left) {
    bool success = false;
    //if (!skipErrors("REPTVARIABLEORFUNCTIONCALL"))return false;

    if (checkFirstSet("REPTVARIABLEORFUNCTIONCALL", 0)) {
        AST* varOrFuncNest = nullptr;
        AST* varOrFuncRest = nullptr;
        if (idNest(&varOrFuncNest, left ) && reptvariableorfunctioncall(&varOrFuncRest, varOrFuncNest)) {
            *varOrFunc = varOrFuncRest;
            std::cout << "REPTVARIABLEORFUNCTIONCALL -> IDNEST REPTVARIABLEORFUNCTIONCALL" << std::endl;
            outDerivation << "REPTVARIABLEORFUNCTIONCALL -> IDNEST REPTVARIABLEORFUNCTIONCALL \n";
            success = true;
        }

    }
    else if (checkFollowSet("REPTVARIABLEORFUNCTIONCALL")) {
        *varOrFunc = left;
        std::cout << "REPTVARIABLEORFUNCTIONCALL -> EPSILON" << std::endl;
        outDerivation << "REPTVARIABLEORFUNCTIONCALL -> EPSILON \n";
        success = true;
    }
    return success;
}

bool Parser::variable(AST** varS) {
    bool success = false;
    //if (!skipErrors("VARIABLE"))return false;

    if (checkFirstSet("VARIABLE", 0)) {
        AST* idorSelf = nullptr;
        AST* varRest = nullptr;
        if (idOrSelf(&idorSelf) && variable2(&varRest, idorSelf)) {
            AST* varID = attrStack.top(); attrStack.pop();
            *varS = varRest;
            std::cout << "VARIABLE -> IDORSELF VARIABLE2" << std::endl;
            outDerivation << "VARIABLE -> IDORSELF VARIABLE2 \n";
            success = true;
        }
    }
    return success;
}

bool Parser::variable2(AST** varRestS, AST* leftVar) {
    bool success = false;
    //if (!skipErrors("VARIABLE2"))return false;
    if (checkFirstSet("VARIABLE2", 0)) {
        AST* indiceRept = nullptr;
        AST* varIdTail = nullptr;
        if (indices(&indiceRept) && reptvariable(&varIdTail, leftVar)) {

            if (indiceRept) {
                leftVar->makeSiblings(indiceRept);
            }
            *varRestS = varIdTail;
            std::cout << "VARIABLE2 -> INDICES REPTVARIABLE" << std::endl;
            outDerivation << "VARIABLE2 -> INDICES REPTVARIABLE \n";
            success = true;
        }
    }
    else if (checkFirstSet("VARIABLE2", 1)) {
        AST* aParamsS = nullptr;
        AST* varNest = nullptr;
        if (match(TokenType::OPENPAR) && aParams(&aParamsS) && match(TokenType::CLOSEPAR) && varIdNest(&varNest, leftVar)) {
            varNest->makeSiblings(aParamsS);
            *varRestS = varNest;

            std::cout << "VARIABLE2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST" << std::endl;
            outDerivation << "VARIABLE2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST \n";
            success = true;
        }
    }
    

    return success;
}

bool Parser::reptvariable(AST** varIdTailS, AST* leftVarId) {
    bool success = false;
    //if (!skipErrors("REPTVARIABLE"))return false;
    if (checkFirstSet("REPTVARIABLE", 0)) {
        AST* varNest = nullptr;
        AST* reptVar = nullptr;
        if (varIdNest(&varNest, leftVarId) && reptvariable(&reptVar, leftVarId)) {
            varNest->makeSiblings(reptVar);
            *varIdTailS = varNest;
    
            std::cout << "REPTVARIABLE -> VARIDNEST REPTVARIABLE" << std::endl;
            outDerivation << "REPTVARIABLE -> VARIDNEST REPTVARIABLE \n";
            success = true;
        }
    }
    else if (checkFollowSet("REPTVARIABLE")) {
        *varIdTailS = leftVarId;
        std::cout << "REPTVARIABLE -> EPSILON" << std::endl;
        outDerivation << "REPTVARIABLE -> EPSILON \n";
        success = true;
    }
    return success;
}

bool Parser::varIdNest(AST** varNest, AST* leftVarId) {
    bool success = false;
    //if (!skipErrors("VARIDNEST"))return false;

    if (checkFirstSet("VARIDNEST", 0)) {
        AST* varIDNest = nullptr;
        if (match(TokenType::DOT) && match(TokenType::ID) && varIdNest2(&varIDNest, attrStack.top())) {
            AST* rhsID = attrStack.top(); attrStack.pop();
            AST* dot = attrStack.top(); attrStack.pop();
            ASTFactory::makeFamily(dot, { leftVarId, varIDNest });
            *varNest = dot;
            std::cout << "VARIDNEST -> DOT ID VARIDEST2" << std::endl;
            outDerivation << "VARIDNEST -> DOT ID VARIDEST2 \n";
            success = true;
        }
    }
    return success;
}

bool Parser::varIdNest2(AST** varNestTail, AST* leftVarId) {
    bool success = false;
    //if (!skipErrors("VARIDNEST2"))return false;

    if (checkFirstSet("VARIDNEST2", 0)) {
        AST* indiceRept = nullptr;
            
        if (indices(&indiceRept)) {
            AST* indiceList = nullptr;
            if (indiceRept) {
                indiceList = ASTFactory::makeFamily(compositeConcept::INDICELIST, { indiceRept });
            }
            AST* varS = ASTFactory::makeFamily(compositeConcept::VARORFUNCTIONCALLLIST, { leftVarId, indiceList });
            *varNestTail = varS;

            std::cout << "VARIDNEST2 -> INDICES " << std::endl;
            outDerivation << "VARIDNEST2 -> INDICES \n";
            success = true;
        }
        
    }
    else if (checkFirstSet("VARIDNEST2", 1)) {
        AST* aParamsS = nullptr;
        AST* varNest = nullptr;
        if (match(TokenType::OPENPAR) && aParams(&aParamsS) && match(TokenType::CLOSEPAR) && varIdNest(&varNest, aParamsS)) {

            std::cout << "VARIDNEST2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST" << std::endl;
            outDerivation << "VARIDNEST2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST \n";
            success = true;
        }
    }
    else if(checkFollowSet("VARIDNEST2")) {
        *varNestTail = leftVarId;
        std::cout << "VARIDNEST2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST" << std::endl;
        outDerivation << "VARIDNEST2 -> OPENPAR APARAMS CLOSEPAR VARIDNEST \n";
        success = true;
    };

    return success;
}

bool Parser::indice(AST** indiceAST) {
    bool success = false;
    //if (!skipErrors("INDICE")) return false;

    if (checkFirstSet("INDICE", 0)) {
        AST* arithExprS = nullptr;
        if (match(TokenType::OPENSQUARE) && arithexpr(&arithExprS) && match(TokenType::CLOSESQUARE)) {
            AST* tempIndice = arithExprS;
            *indiceAST = ASTFactory::makeFamily(compositeConcept::INDICE, { tempIndice });
            std::cout << "INDICE -> OPENSQUARE ARITHEXPR CLOSESQUARE" << std::endl;
            outDerivation << "INDICE -> OPENSQUARE ARITHEXPR CLOSESQUARE \n";
            success = true;
        }
    }

    return success;
}

bool Parser::idNest(AST** IDNest, AST* leftVar) {
    bool success = false;

    //if (!skipErrors("IDNEST"))return false;

    if (checkFirstSet("IDNEST", 0)) {
        AST* idNestTail = nullptr;
        if (match(TokenType::DOT) && match(TokenType::ID) && idNest2(&idNestTail, attrStack.top())) {
            AST* rhsID = attrStack.top(); attrStack.pop();
            AST* dot = attrStack.top(); attrStack.pop();
            ASTFactory::makeFamily(dot, { leftVar, idNestTail });
            *IDNest = dot;
            std::cout << "IDNEST -> DOT ID IDNEST2" << std::endl;
            outDerivation << "IDNEST -> DOT ID IDNEST2 \n";
            success = true;
        }
    }

    return success;
}

bool Parser::idNest2(AST** idNest, AST* leftVar) {
    bool success = false;

    //if (!skipErrors("IDNEST2")) return false;

    if (checkFirstSet("IDNEST2", 0)) {
            
        AST* indiceRept = nullptr;
        if (indices(&indiceRept)) {
            AST* indiceList = nullptr;
            if (indiceRept) {
                indiceList = ASTFactory::makeFamily(compositeConcept::INDICELIST, { indiceRept });
            }
            AST* varS = ASTFactory::makeFamily(compositeConcept::VARIABLE, { leftVar, indiceList });
            *idNest = varS;
            std::cout << "IDNEST2 -> INDICES" << std::endl;
            outDerivation << "IDNEST2 -> INDICES \n";
            success = true;


        }
    }
    else if (checkFirstSet("IDNEST2", 1)) {
        AST* aParamsS = nullptr;
        if (match(TokenType::OPENPAR) && aParams(&aParamsS) && match(TokenType::CLOSEPAR)) {
            
            AST* funcCall = ASTFactory::makeFamily(compositeConcept::FUNCCALL, { leftVar, aParamsS });
            *idNest = funcCall;
        
            std::cout << "IDNEST2 -> OPENPAR APARAMS CLOSEPAR" << std::endl;
            outDerivation << "IDNEST2 -> OPENPAR APARAMS CLOSEPAR \n";
            success = true;
        }
    }
    else if (checkFollowSet("IDNEST2")) {
        *idNest = leftVar;
        std::cout << "IDNEST2 -> EPSILON" << std::endl;
        outDerivation << "IDNEST2 -> EPSILON \n";
        success = true;
    }
    return success;
}

bool Parser::arraySize(AST** arraySizeAST) {
    bool success = false;
    //if (!skipErrors("ARRAYSIZE")) return false;

    if (checkFirstSet("ARRAYSIZE", 0)) {
        if (match(TokenType::OPENSQUARE) && arraySize2(arraySizeAST)) {
            std::cout << "ARRAYSIZE -> OPENSQUARE ARRAYSIZE2" << std::endl;
            outDerivation << "ARRAYSIZE -> OPENSQUARE ARRAYSIZE2 \n";
            success = true;
        }
    }
    return success;
}

bool Parser::arraySize2(AST** arraySizeAST) {
    bool success = false;
    //if (!skipErrors("ARRAYSIZE2"))return false;

    if (checkFirstSet("ARRAYSIZE2", 0)) {
       
        if (match(TokenType::CLOSESQUARE)) {
            std::cout << "ARRAYSIZE2 -> CLOSESQUARE" << std::endl;
            outDerivation << "ARRAYSIZE2 -> CLOSESQUARE \n";
            success = true;
        }
    }
    else if (checkFirstSet("ARRAYSIZE2", 1)) {
        
        if (match(TokenType::INTEGER_VAL) && match(TokenType::CLOSESQUARE)) {
            AST* intNum = attrStack.top();
            attrStack.pop();
            AST* arrayDim = ASTFactory::makeFamily(compositeConcept::ARRAYSIZE, { intNum });
            *arraySizeAST = arrayDim;
            std::cout << "ARRAYSIZE2 -> INTEGERVAL CLOSESQUARE" << std::endl;
            outDerivation << "ARRAYSIZE2 -> INTEGERVAL CLOSESQUARE \n";
            success = true;
        }
    }
    
    else {}
    return success;
}

bool Parser::arraySizes(AST** arraySizeAST) {
    bool success = false;

    //if (!skipErrors("ARRAYSIZES"))return false;

    if (checkFirstSet("ARRAYSIZES", 0)) {
        AST* arraySizeSibling = nullptr;
        if (arraySize(arraySizeAST) && arraySizes(&arraySizeSibling)) {
            
            if (arraySizeSibling) {
               // *arraySizeAST->makeSibling(arraySizeSibling);
            }
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

bool Parser::type(AST** typeAST) {
    bool success = false;

    //if (!skipErrors("TYPE"))return false;

    if (checkFirstSet("TYPE", 0)) {
        if (match(TokenType::INT_T)) {
            *typeAST = attrStack.top(); attrStack.pop();
            std::cout << "TYPE -> INT" << std::endl;
            outDerivation << "TYPE -> INT \n";
            success = true;
        }
    }
    else if (checkFirstSet("TYPE", 1)) {
        if (match(TokenType::ID)) {
            *typeAST = attrStack.top(); attrStack.pop();
            std::cout << "TYPE -> ID" << std::endl;
            outDerivation << "TYPE -> ID \n";
            success = true;
        }
    }
    else if (checkFirstSet("TYPE", 2)) {
        if (match(TokenType::FLOAT_T)) {
            *typeAST = attrStack.top(); attrStack.pop();
            std::cout << "TYPE -> FLOAT" << std::endl;
            outDerivation << "TYPE -> FLOAT \n";
            success = true;
        }
    }
    else {}
    return success;
}

bool Parser::returnType(AST** returnTypeAST) {
    bool success = false;
    //if (!skipErrors("RETURNTYPE"))return false;
    if (checkFirstSet("RETURNTYPE", 0)) {
        if (type(returnTypeAST)) {
            std::cout << "RETURNTYPE -> TYPE" << std::endl;
            outDerivation << "RETURNTYPE -> TYPE \n";
            success = true;
        }
    }
    else if (checkFirstSet("RETURNTYPE", 1)) {
        if (match(TokenType::VOID)) {
            *returnTypeAST = attrStack.top(); attrStack.pop();
            std::cout << "RETURNTYPE -> VOID" << std::endl;
            outDerivation << "RETURNTYPE -> VOID \n";
            success = true;
        }
    }
    else {}

    return success;
}

bool Parser::aParams(AST** aParamsS) {
    bool success = false;
    //if (!skipErrors("APARAMS"))return false;

    if (checkFirstSet("APARAMS", 0)) {
        AST* exprS = nullptr;
        AST* aParamsRest = nullptr;
        if (expr(&exprS) && reptaParams1(&aParamsRest)) {
            *aParamsS = ASTFactory::makeFamily(compositeConcept::APARAMSLIST, { exprS, aParamsRest });
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

bool Parser::reptaParams1(AST** aParamsRest) {
    bool success = false;
    //if (!skipErrors("REPTAPARAMS1"))return false;

    if (checkFirstSet("REPTAPARAMS1", 0)) {
        AST* aParamsRestSiblings = nullptr;
        AST* aParamsTailS = nullptr;
        if (aParamsTail(&aParamsTailS) && reptaParams1(&aParamsRestSiblings)) {

            if (aParamsRestSiblings) {
                aParamsTailS->makeSiblings(aParamsRestSiblings);
            }
            *aParamsRest = aParamsTailS;

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

bool Parser::aParamsTail(AST** aParamsRest) {
    bool success = false;
    //if (!skipErrors("APARAMSTAIL"))return false;

    if (checkFirstSet("APARAMSTAIL", 0)) {
        AST* exprS = nullptr;
        if (match(TokenType::COMMA) && expr(&exprS)) {
            *aParamsRest = exprS;
            std::cout << "APARAMSTAIL -> COMMA EXPR " << std::endl;
            outDerivation << "APARAMSTAIL -> COMMA EXPR \n";
            success = true;
        }
    }
    return success;
}

bool Parser::fParams(AST** fParamsAST) {
    bool success = false;

    //if (!skipErrors("FPARAMS"))return false;

    if (checkFirstSet("FPARAMS", 0)) {

        AST* typeAST = nullptr;
        AST* arraySizeAST = nullptr;
        AST* fParamsTail = nullptr;
        if (match(TokenType::ID) && match(TokenType::COLON) && type(&typeAST) && arraySizes(&arraySizeAST) && reptfParams1(&fParamsTail)) {

            AST* fParamID = attrStack.top(); 
            attrStack.pop();
            AST* arraySizeList = nullptr;

            if (arraySizeAST) {
                arraySizeList = ASTFactory::makeFamily(compositeConcept::ARRAYSIZELIST, { arraySizeAST });
            }

            AST* fParam = ASTFactory::makeFamily(compositeConcept::FPARAMS, {  fParamID, typeAST });
            fParam->makeSiblings(fParamsTail);

            *fParamsAST = ASTFactory::makeFamily(compositeConcept::FPARAMSLIST, { fParam });

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

bool Parser::reptfParams1(AST** fParamsTail) {
    bool success = false;

    //if (!skipErrors("REPTFPARAMS1"))return false;

    if (checkFirstSet("REPTFPARAMS1", 0)) {
        AST* fParamsTailSibling = nullptr;
        if (fParamstail(fParamsTail) && reptfParams1(&fParamsTailSibling)) {
            (*fParamsTail)->makeSiblings(fParamsTailSibling);
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

bool Parser::fParamstail(AST** fParamsTail) {
    bool success = false;

    //if (!skipErrors("FPARAMSTAIL"))return false;

    if (checkFirstSet("FPARAMSTAIL", 0)) {
        AST* typeAST = nullptr;
        AST* arraySizeAST = nullptr;
        if (match(TokenType::COMMA) && match(TokenType::ID) && match(TokenType::COLON) && type(&typeAST) && arraySizes(&arraySizeAST)) {
            AST* fParamsID = attrStack.top(); attrStack.pop();
            AST* arraySizeList = nullptr;

            if (arraySizeAST) {
                arraySizeList = ASTFactory::makeFamily(compositeConcept::ARRAYSIZELIST, { arraySizeAST });
            }
            
            *fParamsTail = ASTFactory::makeFamily(compositeConcept::FPARAMS, { fParamsID, typeAST});
            std::cout << "FPARAMSTAIL -> COMMA ID COLON TYPE ARRAYSIZES" << std::endl;
            outDerivation << "FPARAMSTAIL -> COMMA ID COLON TYPE ARRAYSIZES \n";
            success = true;
        }
    }

    return success;
}

bool Parser::assignOp(AST** assignOpS){
    bool success = false;

    //if (!skipErrors("ASSIGNOP"))return false;

    if (checkFirstSet("ASSIGNOP", 0)) {
        if (match(TokenType::ASSIGN)) {
            *assignOpS = attrStack.top(); attrStack.pop();
            std::cout << "ASSIGNOP -> ASSIGN" << std::endl;
            outDerivation << "ASSIGNOP -> ASSIGN \n";
            success = true;
        }
    }
    return success;
}

bool Parser::relOp(AST** relOpS) {
    bool success = false;

    //if (!skipErrors("RELOP"))return false;

    if (checkFirstSet("RELOP", 0)) {
        if (match(TokenType::NOTEQ)) {
            *relOpS = attrStack.top();
            attrStack.pop();
            std::cout << "RELOP -> NOTEQ " << std::endl;
            outDerivation << "RELOP -> NOTEQ \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 1)) {
        if (match(TokenType::LTEQ)) {
            *relOpS = attrStack.top();
            attrStack.pop();
            std::cout << "RELOP -> LTEQ " << std::endl;
            outDerivation << "RELOP -> LTEQ \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 2)) {
        if (match(TokenType::LT)) {
            *relOpS = attrStack.top();
            attrStack.pop();
            std::cout << "RELOP -> NOTEQ " << std::endl;
            outDerivation << "RELOP -> NOTEQ \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 3)) {
        if (match(TokenType::GTEQ)) {
            *relOpS = attrStack.top();
            attrStack.pop();
            std::cout << "RELOP -> GTEQ" << std::endl;
            outDerivation << "RELOP -> GTEQ \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 4)) {
        if (match(TokenType::GT)) {
            *relOpS = attrStack.top();
            attrStack.pop();
            std::cout << "RELOP -> GT" << std::endl;
            outDerivation << "RELOP -> GT \n";
            success = true;
        }
    }
    else if (checkFirstSet("RELOP", 5)) {
        if (match(TokenType::EQ)) {
            *relOpS = attrStack.top();
            attrStack.pop();
            std::cout << "RELOP -> EQ " << std::endl;
            outDerivation << "RELOP -> EQ \n";
            success = true;
        }
    }
    else {}

    return success;
}

bool Parser::addOp(AST** addOpS) {
    bool success = false;
    //if (!skipErrors("ADDOP"))return false;
    
    if (checkFirstSet("ADDOP", 0)) {
        if (match(TokenType::ADD)) {
            *addOpS = attrStack.top();
            attrStack.pop();
            std::cout << "ADDOP -> ADD" << std::endl;
            outDerivation << "ADDOP -> ADD \n";
            success = true;
        }
    }
    else if (checkFirstSet("ADDOP", 1)) {
        if (match(TokenType::OR)) {
            *addOpS = attrStack.top();
            attrStack.pop();
            std::cout << "ADDOP -> OR " << std::endl;
            outDerivation << "ADDOP -> OR \n";
            success = true;
        }
    }
    else if (checkFirstSet("ADDOP", 2)) {
        if (match(TokenType::SUBT)) {
            *addOpS = attrStack.top();
            attrStack.pop();
            std::cout << "ADDOP -> SUBT " << std::endl;
            outDerivation << "ADDOP -> SUBT \n";
            success = true;
        }
    }
    else {}

    return success;
}

bool Parser::multOp(AST** multOpS) {
    bool success = false;

    //if (!skipErrors("MULTOP"))return false;

    if (checkFirstSet("MULTOP", 0)) {
        if (match(TokenType::AND)) {
            *multOpS = attrStack.top(), attrStack.pop();
            std::cout << "MULTOP -> AND " << std::endl;
            outDerivation << "MULTOP -> AND \n";
            success = true;
        }
    }
    else if (checkFirstSet("MULTOP", 1)) {
        if (match(TokenType::DIV)) {
            *multOpS = attrStack.top(), attrStack.pop();
            std::cout << "MULTOP -> DIV  " << std::endl;
            outDerivation << "MULTOP -> DIV \n";
            success = true;
        }
    }
    else if (checkFirstSet("MULTOP", 2)) {
        if (match(TokenType::MULT)) {
            *multOpS = attrStack.top(), attrStack.pop();
            std::cout << "MULTOP -> MULT  " << std::endl;
            outDerivation << "MULTOP -> MULT \n";
            success = true;
        }
    }
    else {}

    return success;
}

bool Parser::idOrSelf(AST** idorSelf) {
    bool success = false;

    //if (!skipErrors("IDORSELF"))return false;

    if (checkFirstSet("IDORSELF", 0)) {
       
        if (match(TokenType::SELF)) {
            *idorSelf = attrStack.top(); attrStack.pop();
            std::cout << "IDORSELF -> SELF" << std::endl;
            outDerivation << "IDORSELF -> SELF \n";
            success = true;
        }
    }
    else if (checkFirstSet("IDORSELF", 1)) {
        if (match(TokenType::ID)) {
            *idorSelf = attrStack.top(); attrStack.pop();
            std::cout << "IDORSELF -> ID" << std::endl;
            outDerivation << "IDORSELF -> ID \n";
            success = true;
        }
    }
    else{}

    return success;
}





