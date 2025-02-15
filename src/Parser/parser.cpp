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
    else return false;
};
bool Parser::arithExpr(){
    if(checkFirstSet("arithExpr")){
        if(term() && rightrec_arithExpr()){
            std::cout<<"arithExpr -> term rightrec_arithExpr"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::rightrec_arithExpr(){
    if(checkFirstSet("rightrec_arithExpr")){
        if(addOp() && term() && rightrec_arithExpr()){
            std::cout<<"rightrec_arithExpr -> addOp term rightrec_arithExpr"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rightrec_arithExpr")){
        std::cout<<"rightrec_arithExpr -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::term(){
    if(checkFirstSet("term")){
        if(factor() && rightrec_term()){
            std::cout<<"term -> factor rightrec_term"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::rightrec_term(){
    if(checkFirstSet("rightrec_term")){
        if(multOp() && factor() && rightrec_term()){
            std::cout<<"rightrec_term -> multOp factor rightrec_term"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rightrec_term")){
        std::cout<<"righrec_term -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::factor(){
    if(lookAhead == TokenType::ADD || lookAhead == TokenType::SUBT){
        if(sign() && factor()){
            std::cout<<"factor -> sign factor"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::NOT){
        if(match(TokenType::NOT) && factor()){
            std::cout<<"factor -> not factor"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::INTEGER_VAL){
        if(match(TokenType::INTEGER_VAL)){
            std::cout<<"factor -> intLit"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::FLOAT_VAL){
        if(match(TokenType::FLOAT_VAL)){
            std::cout<<"factor -> floatLit"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::ID || lookAhead == TokenType::SELF){
        if(idNest() && match(TokenType::ID) && VarOrFunc()){
            std::cout<<"factor -> idnest id varOrFunc"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::OPENPAR){
        if(match(TokenType::OPENPAR) && arithExpr() && match(TokenType::CLOSEPAR)){
            std::cout<<"factor -> ( arithExpr )"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
    
};
//TODO: work the logic where epsilon is in one of the sets
bool Parser::VarOrFunc(){
    if(lookAhead == TokenType::OPENSQUARE){
        if(rept_idnest10()){
            std::cout<<"VarOrFunc -> rept_idnest10"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::OPENPAR){
        if(match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR)){
            std::cout<<"VarOrFunc -> ( aParams )"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("VarOrFunc")){
        std::cout<<"varOrFunc -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::arraySize(){
    if(lookAhead == TokenType::OPENSQUARE){
        if(match(TokenType::OPENSQUARE) && arraySizeTail()){
            std::cout<<"arraySize -> [ arraySizeTail"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::arraySizeTail(){
    if(lookAhead == TokenType::CLOSESQUARE){
        if(match(TokenType::CLOSESQUARE)){
            std::cout<<"arraySizeTail -> ]"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::INTEGER_VAL){
        if(match(TokenType::INTEGER_VAL) && match(TokenType::CLOSESQUARE)){
            std::cout<<"arraySizetail -> intNum ]"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::type(){
    if(lookAhead == TokenType::INT_T){
        if(match(TokenType::INT_T)){
            std::cout<<"type -> int"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::ID){
        if(match(TokenType::ID)){
            std::cout<<"type -> ID"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::FLOAT_T){
        if(match(TokenType::FLOAT_T)){
            std::cout<<"type -> float"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
    
};
bool Parser::returnType(){
    if(checkFirstSet("returnType") && lookAhead != TokenType::VOID){
        if(type()){
            std::cout<<"returnType -> type"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::VOID){
        if(match(TokenType::VOID)){
            std::cout<<"returntype -> void"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::memberDecl(){
    if(lookAhead == TokenType::FUNCTION || lookAhead == TokenType::CONSTRUCTOR){
        if(funcDecl()){
            std::cout<<"memberDecl -> funcDecl"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::ATTRIBUTE){
        if(attributeDecl()){
            std::cout<<"memberDecl -> attributeDecl"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::funcDecl(){
    if(checkFirstSet("funcDecl")){
        if(funcHead()){
            std::cout<<"funcDecl -> funcHead"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::attributeDecl(){
    if(checkFirstSet("attributeDecl")){
        if(match(TokenType::ATTRIBUTE) && varDecl()){
            std::cout<<"funcDecl -> attribute varDecl"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::varDecl(){
    if(checkFirstSet("varDecl")){
        if(match(TokenType::ID) && match(TokenType::COLON) && rept_varDecl3()){
            std::cout<<"varDecl -> id : type rept_varDecl3"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::rept_varDecl3(){
    if(checkFirstSet("rept_varDecl3")){
        if(arraySize() && rept_varDecl3()){
            std::cout<<"rept_varDecl3 -> arraySize rept_Decl3"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rept_varDecl3")){
        std::cout<<"rept_varDecl3 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::expr(){
    if(checkFirstSet("expr")){
        if(arithExpr() && relExprRest()){
            std::cout<<"expr -> arithExpr relExprRest"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::relExprRest(){
    if(checkFirstSet("relExprRest")){
        if(relOp() && arithExpr()){
            std::cout<<"relExprRest -> relOp arithExpr"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("relExprRest")){
        std::cout<<"relExprRest -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::fParams(){
    if(checkFirstSet("fParams")){
        if(match(TokenType::ID) && match(TokenType::COLON) && type() && rept_fParamas3() && rept_fParams4){
            std::cout<<"fParams -> id : type rept_fParams3 rept_fParams4"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("fParams")){
        std::cout<<"fParams -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::rept_fParamas3(){
    if(lookAhead == TokenType::OPENSQUARE){
        if(arraySize() && rept_fParamas3()){
            std::cout<<"rept_fParams3 -> arraySize rept_fParams3"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rept_fParams3")){
        std::cout<<"rept_fParams3 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::rept_fParams4(){
    if(lookAhead == TokenType::COLON){
        if(fParamsTail() && rept_fParams4()){
            std::cout<<"rept_fParams4 -> fParamsTail rept_fParams4"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rept_fParams4")){
        std::cout<<"rept_fParams4 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::fParamsTail(){
    if(lookAhead == TokenType::COMMA){
        if(match(TokenType::COMMA) && match(TokenType::ID) && match(TokenType::COLON) && type()
            && rept_fParamsTail4()){
                std::cout<<"fParamsTail -> , id : type rept_fParamstail4"<<std::endl;
                return true;
            }
        else return false;
    }
    else return false;
};
bool Parser::rept_fParamsTail4(){
     if(lookAhead == TokenType::OPENSQUARE){
        if(arraySize() && rept_fParamsTail4()){
            std::cout<<"rept_fParamsTail4 -> arraySize rept_fParamsTail4"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rept_fParamsTail4")){
        std::cout<<"rept_fParamsTail4 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::aParams(){
    if(checkFirstSet("aParams")){
        if(expr() && rept_aParams1()){
            std::cout<<"aParams -> expr rept_aParams1"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("aParams")){
        std::cout<<"aParams -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::rept_aParams1(){
     if(lookAhead == TokenType::COMMA){
        if(aParamsTail() && rept_aParams1()){
            std::cout<<"rept_aParams1 -> aParamsTail rept_aParams1"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rept_aParams1")){
        std::cout<<"rept_aParams1 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::aParamsTail(){
    if(lookAhead == TokenType::COMMA){
        if(match(TokenType::COMMA) && expr()){
            std::cout<<"aParamsTail -> , expr"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::idOrSelf(){
    if(lookAhead == TokenType::SELF){
        if(match(TokenType::SELF)){
            std::cout<<"idOrSelf -> self"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::ID){
        if(match(TokenType::ID)){
            std::cout<<"idOrSelf -> id"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::idNest(){
    if(lookAhead == TokenType::SELF || lookAhead == TokenType::SELF){
        if(idOrSelf() && VarOrFunc() && match(TokenType::DOT)){
            std::cout<<"idNet -> idOrSelf VarOrFunc ."<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::rept_idnest10(){
    if(lookAhead == TokenType::OPENSQUARE){
        if(indice() && rept_idnest10()){
            std::cout<<"rept_idnest10 -> indice rept_idnest10"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rept_idnest10")){
        std::cout<<"rept_idnest10 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::indice(){
    if(lookAhead == TokenType::OPENSQUARE){
        if(match(TokenType::OPENSQUARE) && arithExpr() && match(TokenType::CLOSESQUARE)){
            std::cout<<"indice -> [ arithExpr ]"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};

bool Parser::variable(){
    if(lookAhead == TokenType::ID || lookAhead == TokenType::SELF){
        if(idNest() && match(TokenType::ID) && rept_idnest10()){
            std::cout<<"variable -> idnest id rept_idnest10"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};

bool Parser::localVarDecl(){
    if(lookAhead == TokenType::LOCAL){
        if(match(TokenType::LOCAL) && varDecl()){
            std::cout<<"localVarDecl -> local varDecl "<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};

bool Parser::relExpr(){
    if(checkFirstSet("relExpr")){
        if(arithExpr() && relOp() && arithExpr()){
            std::cout<<"relExpr -> arithExpr relOp arithExpr "<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};

bool Parser::assignOp(){
    if(lookAhead == TokenType::ASSIGN){
        if(match(TokenType::ASSIGN)){
            std::cout<<"assignOp -> :="<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::relOp(){
    if(lookAhead == TokenType::GTEQ){
        if(match(TokenType::GTEQ)){
            std::cout<<"relOp -> >="<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::GT){
        if(match(TokenType::GT)){
            std::cout<<"relOp -> >"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::EQ){
        if(match(TokenType::EQ)){
            std::cout<<"relOp -> =="<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::NOTEQ){
        if(match(TokenType::NOTEQ)){
            std::cout<<"relOp -> <>"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::LTEQ){
        if(match(TokenType::LTEQ)){
            std::cout<<"relOp -> <="<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::LT){
        if(match(TokenType::LT)){
            std::cout<<"relOp -> <"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::multOp(){
    if(lookAhead == TokenType::AND){
        if(match(TokenType::AND)){
            std::cout<<"multOp -> and"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::DIV){
        if(match(TokenType::DIV)){
            std::cout<<"multOp -> /"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::MULT){
        if(match(TokenType::MULT)){
            std::cout<<"multOp -> *"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::addOp(){
    if(lookAhead == TokenType::OR){
        if(match(TokenType::OR)){
            std::cout<<"addOp -> or"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::SUBT){
        if(match(TokenType::SUBT)){
            std::cout<<"addOp -> -"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::ADD){
        if(match(TokenType::ADD)){
            std::cout<<"addOp -> +"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::sign(){
    if(lookAhead == TokenType::ADD){
        if(match(TokenType::ADD)){
            std::cout<<"sign -> +"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::SUBT){
        if(match(TokenType::SUBT)){
            std::cout<<"sign -> -"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::statBlock(){
    if(checkFirstSet("statBlock") && lookAhead != TokenType::OPENCURLY){
        if(statement()){
            std::cout<<"statBlock -> statement"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::OPENCURLY){
        if(match(TokenType::OPENCURLY) && rept_statBlock1() && match(TokenType::CLOSECURLY)){
            std::cout<<"statBlock -> { rept_statBlock1 }"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("statBlock")){
        std::cout<<"statBlock -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::rept_statBlock1(){
    if(checkFirstSet("rept_statBlock1")){
        if(statement() && rept_statBlock1()){
            std::cout<<"rept_statblock1 -> statement rept_statBlock1"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("rept_statBlock1")){
        std::cout<<"rept_statBlock1 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::statement(){
    if(lookAhead == TokenType::ID || lookAhead == TokenType::SELF){
        if(idNest() && match(TokenType::ID) && VarOrFunc() && assignStat() && match(TokenType::SEMICOLON)){
            std::cout<<"statement -> idnest id varOrFunc assignstat;"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::WRITE){
        if(match(TokenType::WRITE) && match(TokenType::OPENPAR) && expr() && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)){
                std::cout<<"statement -> write (expr) ;"<<std::endl;
                return true;
            }
        else return false;
    }
    else if(lookAhead == TokenType::WHILE){
        if(match(TokenType::WHILE) && match(TokenType::OPENPAR) && relExpr() && match(TokenType::CLOSEPAR)
            && statBlock() && match(TokenType::SEMICOLON)){
                std::cout<<"statement -> while(relExpr) statBlock ;"<<std::endl;
                return true;
            }
        else return false;
    }
    else if(lookAhead == TokenType::RETURN){
        if(match(TokenType::RETURN) && match(TokenType::OPENPAR) && expr() && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)){
                std::cout<<"statement -> return (expr) ;"<<std::endl;
                return true;
            }
        else return false;
    }
    else if(lookAhead == TokenType::READ){
        if(match(TokenType::READ) && match(TokenType::OPENPAR) && variable() && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)){
                std::cout<<"statement -> read(variable) ;"<<std::endl;
                return true;
            }
        else return false;
    }
    else if(lookAhead == TokenType::IF){
        if(match(TokenType::IF) && match(TokenType::OPENPAR) && relExpr() && match(TokenType::CLOSEPAR)
            && match(TokenType::THEN) && statBlock() && match(TokenType::ELSE) && statBlock() && match(TokenType::SEMICOLON)){
                std::cout<<"statement -> if(relExpr) then statBlock else statBlock ;"<<std::endl;
                return true;
            }
        else return false;
    }
    else return false;
};
bool Parser::assignStat(){
    if(lookAhead == TokenType::ASSIGN){
        if(assignOp() && expr()){
            std::cout<<"assignStat -> assignOp expr"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(checkFollowSet("assignStat")){
        std::cout<<"assignStat -> EPSILON"<<std::endl;
        return true;

    }
    else return false;
};

bool Parser::visibility(){
    if(lookAhead == TokenType::PUBLIC){
        if(match(TokenType::PUBLIC)){
            std::cout<<"visibility -> public"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead == TokenType::PRIVATE){
        if(match(TokenType::PRIVATE)){
            std::cout<<"visibility -> private"<<std::endl;
            return true;

        }
    }
    else return false;
};