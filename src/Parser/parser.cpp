#include "parser.h"



Parser::Parser(){
    firstSet["prog"] = {TokenType::FUNCTION, TokenType::CONSTRUCTOR, TokenType::CLASS, TokenType::IMPLEMENTATION};
    firstSet["start"] = {TokenType::FUNCTION, TokenType::CONSTRUCTOR, TokenType::CLASS, TokenType::IMPLEMENTATION};
    firstSet["rept_prog0"] = {TokenType::FUNCTION, TokenType::CONSTRUCTOR, TokenType::CLASS, TokenType::IMPLEMENTATION};
    firstSet["classOrImplOrFunc"] = {TokenType::IMPLEMENTATION, TokenType::CLASS, TokenType::FUNCTION, TokenType::CONSTRUCTOR};
    firstSet["classDecl"] = {TokenType::CLASS};
    firstSet["opt_classDecl2"] = {TokenType::ISA};
    firstSet["rept_opt_classDecl22"] ={TokenType::COMMA};
    firstSet["rept_classDecl4"] = {TokenType::PRIVATE, TokenType::PUBLIC};
    firstSet["implDef"] = {TokenType::IMPLEMENTATION};
    firstSet["rept_implDef3"] = {TokenType::FUNCTION, TokenType::CONSTRUCTOR};
    firstSet["funcDef"] = {TokenType::FUNCTION, TokenType::CONSTRUCTOR};
    firstSet["funcHead"] = {TokenType::CONSTRUCTOR, TokenType::FUNCTION};
    firstSet["funcBody"] = {TokenType::OPENCURLY};
    firstSet["rept_funcBody1"] = {TokenType::IF, TokenType::READ, TokenType::RETURN, TokenType::WHILE, TokenType::WRITE, 
        TokenType::ID, TokenType::SELF, TokenType::LOCAL};
    firstSet["localVarDeclOrStat"] = {TokenType::LOCAL, TokenType::IF, TokenType::READ, TokenType::RETURN, TokenType::WHILE, 
        TokenType::WRITE, TokenType::ID, TokenType::SELF};
    firstSet["arithExpr"] = {TokenType::OPENPAR, TokenType::ID, TokenType::SELF, TokenType::FLOAT_VAL, TokenType::INTEGER_VAL,
        TokenType::NOT, TokenType::ADD, TokenType::SUBT};
    firstSet["rightrec-arithExpr"] = {TokenType::ADD, TokenType::SUBT, TokenType::OR};
    firstSet["term"] = {TokenType::MULT, TokenType::DIV, TokenType::AND};
    firstSet["factor"] = {TokenType::ADD, TokenType::SUBT, TokenType::NOT, TokenType::INTEGER_VAL, TokenType::FLOAT_VAL,
        TokenType::ID, TokenType::SELF, TokenType::OPENPAR};
    firstSet["varOrFunc"] = {TokenType::OPENSQUARE, TokenType::OPENPAR};
    firstSet["arraySize"] = {TokenType::OPENSQUARE};
    firstSet["arraySizeTail"] = {TokenType::INTEGER_VAL, TokenType::CLOSESQUARE};
    firstSet["type"] = {TokenType::INT_T, TokenType::ID, TokenType::FLOAT_T};
    firstSet["returnType"] = {TokenType::FLOAT_T, TokenType::ID, TokenType::INT_T, TokenType::VOID};
    firstSet["memberDecl"] = {TokenType::FUNCTION, TokenType::CONSTRUCTOR, TokenType::ATTRIBUTE};
    firstSet["funcDecl"] = {TokenType::FUNCTION, TokenType::CONSTRUCTOR};
    firstSet["attributeDecl"] = {TokenType::ATTRIBUTE};
    firstSet["varDecl"] = {TokenType::ID};
    firstSet["rept_varDecl3"] = {TokenType::OPENSQUARE};
    firstSet["expr"] = {TokenType::OPENPAR, TokenType::ID, TokenType::SELF, TokenType::FLOAT_VAL, TokenType::INTEGER_VAL,
        TokenType::NOT, TokenType::ADD, TokenType::SUBT};
    firstSet["relExprRest"] = {TokenType::LT, TokenType::LTEQ, TokenType::NOTEQ, TokenType::EQ, TokenType::GT, TokenType::GTEQ};
    firstSet["fParams"] = {TokenType::ID};
    firstSet["rept_fParams3"] = {TokenType::OPENSQUARE};
    firstSet["rept_fParams4"] = {TokenType::COMMA};
    firstSet["fParamsTail"] = {TokenType::COMMA};
    firstSet["rept_fParamsTail4"] = {TokenType::OPENSQUARE};
    firstSet["aParams"] = {TokenType::OPENPAR, TokenType::ID, TokenType::SELF, TokenType::FLOAT_VAL, TokenType::INTEGER_VAL,
        TokenType::NOT, TokenType::ADD, TokenType::SUBT};
    firstSet["rept_aParams1"] = {TokenType::COMMA};
    firstSet["aParamsTail"] = {TokenType::COMMA};
    firstSet["idOrSelf"] = {TokenType::SELF, TokenType::ID};
    firstSet["idNest"] = {TokenType::ID, TokenType::SELF};
    firstSet["rept_idnest10"] = {TokenType::OPENSQUARE};
    firstSet["indice"] = {TokenType::OPENSQUARE};
    firstSet["variable"] = {TokenType::ID, TokenType::SELF};
    firstSet["localcVarDecl"] = {TokenType::LOCAL};
    firstSet["relExpr"] = {TokenType::OPENPAR, TokenType::ID, TokenType::SELF, TokenType::FLOAT_VAL, TokenType::INTEGER_VAL,
        TokenType::NOT, TokenType::ADD, TokenType::SUBT};
    firstSet["assignOp"] = {TokenType::ASSIGN};
    firstSet["relOp"] = {TokenType::LT, TokenType::LTEQ, TokenType::NOTEQ, TokenType::EQ, TokenType::GT, TokenType::GTEQ};
    firstSet["multOp"] = {TokenType::AND, TokenType::DIV, TokenType::MULT};
    firstSet["addOp"] = {TokenType::OR, TokenType::SUBT, TokenType::ADD};
    firstSet["sign"] = {TokenType::ADD, TokenType::SUBT};
    firstSet["statBlock"] = {TokenType::IF, TokenType::READ, TokenType::RETURN, TokenType::WHILE, TokenType::WRITE, 
        TokenType::ID, TokenType::SELF};
    firstSet["rept_statBlock1"] = {TokenType::IF, TokenType::READ, TokenType::RETURN, TokenType::WHILE, TokenType::WRITE, 
        TokenType::ID, TokenType::SELF};
    firstSet["statement"] = {TokenType::ID, TokenType::SELF, TokenType::WRITE, TokenType::WHILE, TokenType::RETURN, 
        TokenType::READ, TokenType::IF};
    firstSet["assignStat"] = {TokenType::ASSIGN};
    firstSet["visibility"] = {TokenType::PUBLIC, TokenType::PRIVATE};

    followSet["start"] = {TokenType::ENDOFILE};
    followSet["prog"] = {TokenType::ENDOFILE};
    followSet["rept_prog"] = {TokenType::ENDOFILE};
    followSet["opt_classDecl2"] = {TokenType::OPENCURLY};
    followSet["rept_opt_classDecl22"] = {TokenType::OPENCURLY};
    followSet["rep_classDecl4"] = {TokenType::CLOSECURLY};
    followSet["rept_implDef3"] = {TokenType::CLOSECURLY};
    followSet["rept_funcBody1"] = {TokenType::CLOSECURLY};
    followSet["rightrec_arithExpr"] = {TokenType::CLOSEPAR, TokenType::COMMA, TokenType::SEMICOLON, TokenType::LT, TokenType::LTEQ,
        TokenType::NOTEQ, TokenType::EQ, TokenType::GT, TokenType::GTEQ, TokenType::CLOSESQUARE};
    followSet["rightrec_term"] = {TokenType::CLOSEPAR, TokenType::COMMA, TokenType::SEMICOLON, TokenType::LT, TokenType::LTEQ,
        TokenType::NOTEQ, TokenType::EQ, TokenType::GT, TokenType::GTEQ, TokenType::CLOSESQUARE, TokenType::ADD, TokenType::SUBT,
        TokenType::OR};
    followSet["varOrFunc"] = {TokenType::CLOSEPAR, TokenType::COMMA, TokenType::SEMICOLON, TokenType::LT, TokenType::LTEQ,
        TokenType::NOTEQ, TokenType::EQ, TokenType::GT, TokenType::GTEQ, TokenType::CLOSESQUARE, TokenType::ADD, TokenType::SUBT,
        TokenType::OR, TokenType::MULT, TokenType::DIV, TokenType::AND, TokenType::DOT, TokenType::ASSIGN};
    followSet["rept_varDecl3"] = {TokenType::SEMICOLON};
    followSet["relExprRest"] = {TokenType::CLOSEPAR, TokenType::COMMA, TokenType::SEMICOLON};
    followSet["fParams"] = {TokenType::CLOSEPAR};
    followSet["rept_fParams3"] = {TokenType::CLOSEPAR, TokenType::COMMA};
    followSet["rept_fParams4"] = {TokenType::CLOSEPAR};
    followSet["rept_fParamsTail4"] = {TokenType::CLOSEPAR, TokenType::COMMA};
    followSet["aParams"] = {TokenType::CLOSEPAR};
    followSet["rept_aParams1"] = {TokenType::CLOSEPAR};
    followSet["rept_idnest10"] = {TokenType::CLOSEPAR, TokenType::COMMA, TokenType::SEMICOLON, TokenType::LT, TokenType::LTEQ,
        TokenType::NOTEQ, TokenType::EQ, TokenType::GT, TokenType::GTEQ, TokenType::CLOSESQUARE, TokenType::ADD, TokenType::SUBT,
        TokenType::OR, TokenType::MULT, TokenType::DIV, TokenType::AND, TokenType::DOT, TokenType::ASSIGN};
    followSet["statBlock"] = {TokenType::ELSE, TokenType::SEMICOLON};
    followSet["rept_statBlock1"] = {TokenType::CLOSECURLY};
    followSet["assignStat"] = {TokenType::SEMICOLON};
};

bool Parser::match(TokenType token){
    if(lookAhead == token){
        lookAhead = lexer->nextToken().getType();
        return true;
    }
    else{
        lookAhead = lexer->nextToken().getType();
        return false;
    }
};

bool Parser::checkFirstSet(std::string funcName){
    bool isValid = false;
    for(int i = 0; i<firstSet[funcName].size(); i++){
        if(lookAhead == firstSet[funcName][i])isValid = true;
    }
    return isValid;
}

bool Parser::checkFollowSet(std::string funcName){
    bool isValid = false;
    for(int i= 0;i<followSet[funcName].size();i++){
        if(lookAhead == followSet[funcName][i]) isValid = true;
    }
    return isValid;
}
bool Parser::startParse(){
    lookAhead = lexer->nextToken().getType();
    if(start() && match(TokenType::ENDOFILE))return true;
    else return false;

}

bool Parser::start(){
    
    if(checkFirstSet("start")){
        if(prog()){
            std::cout<<"start->prog"<<std::endl;
            return true;
        }
        else{
            return false;
        }
    }
    else if(match(TokenType::ENDOFILE)){
        std::cout<<"start->EOF"<<std::endl;
    }
    else{
        return false;
    }
};
bool Parser::prog(){
    if(checkFirstSet("rept_prog0")){
        if(rept_prog0){
            std::cout<<"prog->rept_prog0"<<std::endl;
            return true;
        }
        else{
            return false;
        }
    }
    else if(match(TokenType::ENDOFILE)){
        std::cout<<"prog->EOF"<<std::endl;
    }
    else{
        return false;
    }
};
bool Parser::rept_prog0(){
    if(checkFirstSet("classOrImplOrFunc") && checkFirstSet("rept_prog0")){
        if(classOrImpleOrFunc() && rept_prog0()){
            std::cout<<"rept_prog0 -> classOrImplOrFunc rept_prog0"<<std::endl;
            return true;
        }
        else{
            return false;
        }
    }
    else if(checkFollowSet("rept_prog0")){
        std::cout<<"rept_prog-> EPSILON"<<std::endl;
        return true;
    }
    return false;
};
bool Parser::classOrImpleOrFunc(){
    if(checkFirstSet("implDef")){
        if(implDef){
            std::cout<<"classOrImpleOrFunc -> implDef"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFirstSet("classDecl")){
        if(classDecl){
            std::cout<<"classOrImpleOrFunc->implDef"<<std::endl;
            return true;
        }
        else return false;

    }
    else if(checkFirstSet("funcDef")){
        if(funcDef){
            std::cout<<"classOrImplOrFunc -> funcDef"<<std::endl;
            return true;
        }
        else return false;
    }
    else {
        return false;
    }
};
//check the conditions of the first set for this declaration
bool Parser::classDecl(){
    if(checkFirstSet("opt_classDecl2") && checkFirstSet("rept_classDecl4")){
        if(match(TokenType::CLASS) && match(TokenType::ID) && opt_classDecl2 && match(TokenType::OPENCURLY)
            && rept_classDecl4 && match(TokenType::CLOSECURLY)){
                std::cout<<"classDecl -> class id opt_classDecl2 { rept_classDecl4 }"<<std::endl;
                return true;
            }
        else return false;
    }
    else return false;
};
bool Parser::opt_classDecl2(){
    if(checkFirstSet("rept_opt_classDecl22")){
        if(match(TokenType::ISA) && match(TokenType::ID) && rept_opt_classDecl22){
            std::cout<<"opt_classDecl2 -> isa id rept_opt_classDecl22"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("opt_classDecl2")){
        return true;
    }
    else return false;
};
bool Parser::rept_opt_classDecl22(){
    if(lookAhead == TokenType::COMMA){
        if(lookAhead == TokenType::ID){
            if(rept_opt_classDecl22){
                std::cout<<"rept_opt_classDecl22 -> , ID rept_opt_classDecl22"<<std::endl;
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if(checkFollowSet("rept_opt_classDecl22")){
        return true;
    }
    else return false;
};
bool Parser::rept_classDecl4(){
    if(checkFirstSet("visibility") || checkFirstSet("memberDecl") || checkFirstSet("rept_classDecl4")){
        if(visibility() && memberDecl() && rept_classDecl4()){
            std::cout<<"rept_classDecl4 -> visibility memberDecl rept_classDecl4"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::CLOSECURLY){
        return true;
    }
    else return false;
};
bool Parser::implDef(){
    if(match(TokenType::IMPLEMENTATION)){
        if(match(TokenType::ID)){
            if(match(TokenType::OPENCURLY))
                if(checkFirstSet("rept_implDef3")){
                    if(rept_implDef3){
                        std::cout<<"implDef -> implementation id { rept_implDef3 }"<<std::endl;
                        return true;
                    }
                    else return false;
                }
                else return false;
        }
        else return false;
    }
    else return false;
};
bool Parser::rept_implDef3(){
    if(checkFirstSet("rept_implDef3")){
        if(funcDef()&& rept_implDef3()){
            std::cout<<"rept_implDef3 -> funcDef rept_implDef3"<<std::endl;
        }
        else return false;
    }
    else if(checkFollowSet("rept_implDef3")){
        std::cout<<"rept_implDef3 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::funcDef(){
    if(checkFirstSet("funcDef")){
        if(funcHead() && funcBody()){
            std::cout<<"funcDef -> funchHead funcBody"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::funcHead(){
    if(lookAhead == TokenType::CONSTRUCTOR){
        if(match(TokenType::CONSTRUCTOR) && match(TokenType::OPENPAR) && fParams() && match(TokenType::CLOSEPAR)){
            std::cout<<"funcHead -> constructor ( fParams )"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::FUNCTION){
        if(match(TokenType::FUNCTION) && match(TokenType::ID) && match(TokenType::OPENPAR) && fParams() && match(TokenType::CLOSEPAR)
            && match(TokenType::ARROW) && returnType()){
                std::cout<<"funcHead -> function id {fParams} => returnType"<<std::endl;
                return true;
            }
        else return false;
    }
    else return false;
};
bool Parser::funcBody(){
    if(checkFirstSet("funcBody")){
        if(match(TokenType::OPENCURLY) && rept_funcBody1 && match(TokenType::CLOSECURLY)){
            std::cout<<"funcBody -> { rept_funcBody1 }";
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::rept_funcBody1(){
    if(checkFirstSet("rept_funcBody1")){
        if(localVarDeclOrStat() && rept_funcBody1()){
            std::cout<<"rept_funcBody1 -> localVarDeclOrStat rept_funcBody1"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rept_funcBody1")){
        std::cout<<"rept_funcBody1 -> EPSILON"<<std::endl;
        return true;
    }
    return false;
};
bool Parser::localVarDeclOrStat(){
    if(lookAhead == TokenType::LOCAL){
        if(localVarDecl()){
            std::cout<<"localVarDeclorStat -> localVarDecl"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFirstSet("statement") && lookAhead != TokenType::LOCAL){
        if(statement()){
            std::cout<<"localVarDeclOrStat -> statement"<<std::endl;
            return true;
        }
        else return false;

    }
};
bool Parser::arithExpr(){};
bool Parser::rightrec_arithExpr(){};
bool Parser::term(){};
bool Parser::rightrec_term(){};
bool Parser::factor(){};
bool Parser::VarOrFunc(){};
bool Parser::arraySize(){};
bool Parser::arraySizeTail(){};
bool Parser::type(){};
bool Parser::returnType(){};
bool Parser::memberDecl(){};
bool Parser::funcDecl(){};
bool Parser::attributeDecl(){};
bool Parser::varDecl(){};
bool Parser::rept_varDecl3(){};
bool Parser::expr(){};
bool Parser::relExprRest(){};
bool Parser::fParams(){};
bool Parser::rept_fParamas3(){};
bool Parser::rept_fParams4(){};
bool Parser::fParamsTail(){};
bool Parser::rept_fParamsTail4(){};
bool Parser::aParams(){};
bool Parser::rept_aParams1(){};
bool Parser::aParamsTail(){};
bool Parser::idOrSelf(){};
bool Parser::idNest(){};
bool Parser::rept_idnest10(){};
bool Parser::indice(){};
bool Parser::variable(){};
bool Parser::localVarDecl(){};
bool Parser::relExpr(){};
bool Parser::assignOp(){};
bool Parser::relOp(){};
bool Parser::multOp(){};
bool Parser::addOp(){};
bool Parser::sign(){};
bool Parser::statBlock(){};
bool Parser::rept_statBlock1(){};
bool Parser::statement(){};
bool Parser::assignStat(){};
bool Parser::visibility(){};