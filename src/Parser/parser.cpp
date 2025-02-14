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
bool Parser::startParse(){
    lookAhead = lexer->nextToken().getType();
    if(start() && match(TokenType::ENDOFILE))return true;
    else return false;

}
bool Parser::start(){};
bool Parser::prog(){};
bool Parser::rept_prog0(){};
bool Parser::classOrImpleOrFunc(){};
bool Parser::classDecl(){};
bool Parser::opt_classDecl2(){};
bool Parser::rept_opt_classDecl22(){};
bool Parser::rept_classDecl4(){};
bool Parser::implDef(){};
bool Parser::rept_implDef3(){};
bool Parser::funcDef(){};
bool Parser::funcHead(){};
bool Parser::funcBody(){};
bool Parser::rept_funcBody1(){};
bool Parser::localVarDeclOrStat(){};
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