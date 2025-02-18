#include "parser.h"


Parser::Parser(std::ifstream& source, std::ostream& outDerivation, std::ofstream& syntaxErrors, Lexer& lexer)
    :source(source), outDerivation(outDerivation), syntaxErrors(syntaxErrors), lexer(lexer){
    


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

bool Parser::checkFirstSet(std::string funcName){
    return firstSet.count(funcName) > 0;
}

bool Parser::checkFollowSet(std::string funcName){
    return followSet.count(funcName) > 0;
}
bool Parser::startParse(){
    std::cout<<"Started Parsing"<<std::endl;
    if(start() && match(TokenType::ENDOFILE)){
        std::cout<<"Parsing Ended"<<std::endl;
        return true;}
    else { 
        std::cout << "Stopped at"<<lookAhead.getLexeme() <<"Type: "<<lookAhead.getType() << lookAhead.getLine()<< std::endl;
        return false; }

}

bool Parser::start(){
    
    if(lookAhead.getType() == TokenType::FUNCTION || lookAhead.getType() == TokenType::CONSTRUCTOR || lookAhead.getType() == TokenType::CLASS
        || lookAhead.getType() == TokenType::IMPLEMENTATION){
        if(prog()){
            std::cout<<"start->prog"<<std::endl;
            outDerivation<<"Start -> prog \n";
            return true;
        }
        else{
            return false;
        }
    }
    /*
    else if(lookAhead.getType() == TokenType::COMMENT){
        lookAhead.getType() = lexer.nextToken().getType();
        return start();
    }*/
    else if(lookAhead.getType() == TokenType::ENDOFILE){
        std::cout<<"start->EOF"<<std::endl;
        return true;
    }
    else if(lookAhead.getType() == TokenType::ENDOFILE){
        return true;
    }
    else return false;
};

bool Parser::prog(){
    if(lookAhead.getType() == TokenType::FUNCTION || lookAhead.getType() == TokenType::CONSTRUCTOR || lookAhead.getType() == TokenType::CLASS
        || lookAhead.getType() == TokenType::IMPLEMENTATION){

        if(rept_prog0()){
            std::cout<<"prog->rept_prog0"<<std::endl;
            return true;
        }
        else{
            return false;
        }
    }
    else if(match(TokenType::ENDOFILE)){
        std::cout<<"prog->EOF"<<std::endl;
        return true;
    }
    else{
        return false;
    }
};
bool Parser::rept_prog0(){
    if(lookAhead.getType() == TokenType::FUNCTION || lookAhead.getType() == TokenType::CONSTRUCTOR || lookAhead.getType() == TokenType::CLASS 
        || lookAhead.getType() == TokenType::IMPLEMENTATION){
        if(classOrImpleOrFunc() && rept_prog0()){
            std::cout<<"rept_prog0 -> classOrImplOrFunc rept_prog0"<<std::endl;
            return true;
        }
        else{
            return false;
        }
    }
    else if(lookAhead.getType() == TokenType::ENDOFILE){
        std::cout<<"rept_prog-> EPSILON"<<std::endl;
        return true;
    }
    return false;
};
bool Parser::classOrImpleOrFunc(){
    if(lookAhead.getType() == TokenType::IMPLEMENTATION){
        if(implDef()){
            std::cout<<"classOrImpleOrFunc -> implDef"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLASS){
        if(classDecl()){
            std::cout<<"classOrImpleOrFunc-> classDecl"<<std::endl;
            return true;
        }
        else return false;

    }
    else if(lookAhead.getType() == TokenType::FUNCTION || lookAhead.getType() == TokenType::CONSTRUCTOR){
        if(funcDef()){
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
    if (lookAhead.getType() == TokenType::CLASS) {
            if (match(TokenType::CLASS) && match(TokenType::ID) && opt_classDecl2() && match(TokenType::OPENCURLY)
                && rept_classDecl4() && match(TokenType::CLOSECURLY) && match(TokenType::SEMICOLON)) {
                std::cout << "classDecl -> class id opt_classDecl2 { rept_classDecl4 }" << std::endl;
                return true;
            }
            else return false;
        }
    else return false;
};
bool Parser::opt_classDecl2(){
    if(lookAhead.getType() == TokenType::ISA){
        if(match(TokenType::ISA) && match(TokenType::ID) && rept_opt_classDecl22()){
            std::cout<<"opt_classDecl2 -> isa id rept_opt_classDecl22"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::OPENCURLY){
        return true;
    }
    else return false;
};
bool Parser::rept_opt_classDecl22(){
    if(lookAhead.getType() == TokenType::COMMA){
            if(match(TokenType::COMMA) && match(TokenType::ID) && rept_opt_classDecl22()){
                std::cout<<"rept_opt_classDecl22 -> , ID rept_opt_classDecl22"<<std::endl;
                return true;
            }
            else return false;
    }
    else if(lookAhead.getType() == TokenType::OPENCURLY){
        return true;
    }
    else return false;
};
bool Parser::rept_classDecl4(){
    if(lookAhead.getType() == TokenType::PRIVATE || lookAhead.getType() == TokenType::PUBLIC){
        if(visibility() && memberDecl() && rept_classDecl4()){
            std::cout<<"rept_classDecl4 -> visibility memberDecl rept_classDecl4"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSECURLY){
        return true;
    }
    else return false;
};
bool Parser::implDef(){
    if(match(TokenType::IMPLEMENTATION)){
        if(match(TokenType::ID)){
            if(match(TokenType::OPENCURLY)){
                    if(rept_implDef3() && match(TokenType::CLOSECURLY)){
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
    if(lookAhead.getType() == TokenType::FUNCTION || lookAhead.getType() == TokenType::CONSTRUCTOR){
        if(funcDef()&& rept_implDef3()){
            std::cout<<"rept_implDef3 -> funcDef rept_implDef3"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSECURLY){
        std::cout<<"rept_implDef3 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::funcDef(){
    if(lookAhead.getType() == TokenType::FUNCTION || lookAhead.getType() == TokenType::CONSTRUCTOR){
        if(funcHead() && funcBody()){
            std::cout<<"funcDef -> funchHead funcBody"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::funcHead(){
    if(lookAhead.getType() == TokenType::CONSTRUCTOR){
        if(match(TokenType::CONSTRUCTOR) && match(TokenType::OPENPAR) && fParams() && match(TokenType::CLOSEPAR)){
            std::cout<<"funcHead -> constructor ( fParams )"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::FUNCTION){
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
    if(lookAhead.getType() == TokenType::OPENCURLY){
        if(match(TokenType::OPENCURLY) && rept_funcBody1() && match(TokenType::CLOSECURLY)){
            std::cout<<"funcBody -> { rept_funcBody1 }";
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::rept_funcBody1(){
    if(lookAhead.getType() == TokenType::IF || lookAhead.getType() == TokenType::READ || lookAhead.getType() == TokenType::RETURN || lookAhead.getType() == TokenType::WHILE
        || lookAhead.getType() == TokenType::WRITE || lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF 
        || lookAhead.getType() == TokenType::LOCAL){
        if(localVarDeclOrStat() && rept_funcBody1()){
            std::cout<<"rept_funcBody1 -> localVarDeclOrStat rept_funcBody1"<<std::endl;
            return true;
        } 
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSECURLY){
        std::cout<<"rept_funcBody1 -> EPSILON"<<std::endl;
        return true;
    }
    return false;
};
bool Parser::localVarDeclOrStat(){
    if(lookAhead.getType() == TokenType::LOCAL){
        if(localVarDecl()){
            std::cout<<"localVarDeclorStat -> localVarDecl"<<std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::IF || lookAhead.getType() == TokenType::READ || lookAhead.getType() == TokenType::RETURN
        || lookAhead.getType() == TokenType::WHILE || lookAhead.getType() == TokenType::WRITE || lookAhead.getType() == TokenType::ID
        || lookAhead.getType() == TokenType::SELF) {
        if(statement()){
            std::cout<<"localVarDeclOrStat -> statement"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::arithExpr(){
    if(lookAhead.getType() == TokenType::OPENPAR || lookAhead.getType() == TokenType::FLOAT_VAL || lookAhead.getType() == TokenType::INTEGER_VAL
        || lookAhead.getType() == TokenType::NOT || lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT){
        if(term() && rightrec_arithExpr()){
            std::cout<<"arithExpr -> term rightrec_arithExpr"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::rightrec_arithExpr(){
    if(lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT || lookAhead.getType() == TokenType::OR){
        if(addOp() && term() && rightrec_arithExpr()){
            std::cout<<"rightrec_arithExpr -> addOp term rightrec_arithExpr"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::GT || lookAhead.getType() == TokenType::GTEQ || lookAhead.getType() == TokenType::LT || lookAhead.getType() == TokenType::LTEQ
        || lookAhead.getType() == TokenType::NOTEQ || lookAhead.getType() == TokenType::EQ || lookAhead.getType() == TokenType::CLOSEPAR
        || lookAhead.getType() == TokenType::COMMA || lookAhead.getType() == TokenType::SEMICOLON || lookAhead.getType() == TokenType::CLOSESQUARE){
        std::cout<<"rightrec_arithExpr -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::term(){
    if(lookAhead.getType() == TokenType::OPENPAR || lookAhead.getType() == TokenType::FLOAT_VAL || lookAhead.getType() == TokenType::INTEGER_VAL
        || lookAhead.getType() == TokenType::NOT || lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT){
        if(factor() && rightrec_term()){
            std::cout<<"term -> factor rightrec_term"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::rightrec_term(){
    if(lookAhead.getType() == TokenType::MULT || lookAhead.getType() == TokenType::DIV || lookAhead.getType() == TokenType::AND){
        if(multOp() && factor() && rightrec_term()){
            std::cout<<"rightrec_term -> multOp factor rightrec_term"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::GT || lookAhead.getType() == TokenType::GTEQ || lookAhead.getType() == TokenType::LT || lookAhead.getType() == TokenType::LTEQ
        || lookAhead.getType() == TokenType::NOTEQ || lookAhead.getType() == TokenType::EQ || lookAhead.getType() == TokenType::CLOSEPAR
        || lookAhead.getType() == TokenType::COMMA || lookAhead.getType() == TokenType::SEMICOLON || lookAhead.getType() == TokenType::CLOSESQUARE
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT || lookAhead.getType() == TokenType::OR){
        std::cout<<"righrec_term -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::factor(){
    if(lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT){
        if(sign() && factor()){
            std::cout<<"factor -> sign factor"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::NOT){
        if(match(TokenType::NOT) && factor()){
            std::cout<<"factor -> not factor"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::INTEGER_VAL){
        if(match(TokenType::INTEGER_VAL)){
            std::cout<<"factor -> intLit"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::FLOAT_VAL){
        if(match(TokenType::FLOAT_VAL)){
            std::cout<<"factor -> floatLit"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF){
        if(idOrSelf() && factor2() && VarOrFunc()){
            std::cout<<"factor -> idnest id varOrFunc"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::OPENPAR){
        if(match(TokenType::OPENPAR) && arithExpr() && match(TokenType::CLOSEPAR)){
            std::cout<<"factor -> ( arithExpr )"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
    
};

bool Parser::factor2() {
    if (lookAhead.getType() == TokenType::OPENSQUARE) {
        if (rept_idnest10()) {
            std::cout << "factor2 -> rept_idnest10" << std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::OPENPAR) {
        if (match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR)) {
            std::cout << "factor 2 -> ( aParams )" << std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::GT || lookAhead.getType() == TokenType::GTEQ || lookAhead.getType() == TokenType::LT || lookAhead.getType() == TokenType::LTEQ
        || lookAhead.getType() == TokenType::NOTEQ || lookAhead.getType() == TokenType::EQ || lookAhead.getType() == TokenType::CLOSEPAR
        || lookAhead.getType() == TokenType::COMMA || lookAhead.getType() == TokenType::SEMICOLON || lookAhead.getType() == TokenType::CLOSESQUARE
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT || lookAhead.getType() == TokenType::OR ||
        lookAhead.getType() == TokenType::MULT || lookAhead.getType() == TokenType::DIV || lookAhead.getType() == TokenType::AND
        || lookAhead.getType() == TokenType::DOT || lookAhead.getType() == TokenType::ASSIGN) {
        std::cout << "factor2 -> EPSILON" << std::endl;
        return true;
    }
}
//TODO: work the logic where epsilon is in one of the sets
bool Parser::VarOrFunc(){
    if(lookAhead.getType() == TokenType::DOT){
        if(idNest() && VarOrFunc()){
            std::cout<<"VarOrFunc -> idnest VarOrFunc"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::GT || lookAhead.getType() == TokenType::GTEQ || lookAhead.getType() == TokenType::LT || lookAhead.getType() == TokenType::LTEQ
        || lookAhead.getType() == TokenType::NOTEQ || lookAhead.getType() == TokenType::EQ || lookAhead.getType() == TokenType::CLOSEPAR
        || lookAhead.getType() == TokenType::COMMA || lookAhead.getType() == TokenType::SEMICOLON || lookAhead.getType() == TokenType::CLOSESQUARE
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT || lookAhead.getType() == TokenType::OR ||
        lookAhead.getType() == TokenType::MULT || lookAhead.getType() == TokenType::DIV || lookAhead.getType() == TokenType::AND || lookAhead.getType() == TokenType::ASSIGN){
        std::cout<<"varOrFunc -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::arraySize(){
    if(lookAhead.getType() == TokenType::OPENSQUARE){
        if(match(TokenType::OPENSQUARE) && arraySizeTail()){
            std::cout<<"arraySize -> [ arraySizeTail"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::arraySizeTail(){
    if(lookAhead.getType() == TokenType::CLOSESQUARE){
        if(match(TokenType::CLOSESQUARE)){
            std::cout<<"arraySizeTail -> ]"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::INTEGER_VAL){
        if(match(TokenType::INTEGER_VAL) && match(TokenType::CLOSESQUARE)){
            std::cout<<"arraySizetail -> intNum ]"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::type(){
    if(lookAhead.getType() == TokenType::INT_T){
        if(match(TokenType::INT_T)){
            std::cout<<"type -> int"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::ID){
        if(match(TokenType::ID)){
            std::cout<<"type -> ID"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::FLOAT_T){
        if(match(TokenType::FLOAT_T)){
            std::cout<<"type -> float"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
    
};
bool Parser::returnType(){
    if(lookAhead.getType() == TokenType::FLOAT_T || lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::INT_T){
        if(type()){
            std::cout<<"returnType -> type"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::VOID){
        if(match(TokenType::VOID)){
            std::cout<<"returntype -> void"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::memberDecl(){
    if(lookAhead.getType() == TokenType::FUNCTION || lookAhead.getType() == TokenType::CONSTRUCTOR){
        if(funcDecl()){
            std::cout<<"memberDecl -> funcDecl"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::ATTRIBUTE){
        if(attributeDecl()){
            std::cout<<"memberDecl -> attributeDecl"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::funcDecl(){
    if(lookAhead.getType() == TokenType::FUNCTION || lookAhead.getType() == TokenType::CONSTRUCTOR){
        if(funcHead() && match(TokenType::SEMICOLON)){
            std::cout<<"funcDecl -> funcHead"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::attributeDecl(){
    if(lookAhead.getType() == TokenType::ATTRIBUTE){
        if(match(TokenType::ATTRIBUTE) && varDecl()){
            std::cout<<"funcDecl -> attribute varDecl"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::varDecl(){
    if(lookAhead.getType() == TokenType::ID){
        if(match(TokenType::ID) && match(TokenType::COLON) && type() && rept_varDecl3() && match(TokenType::SEMICOLON)){
            std::cout<<"varDecl -> id : type rept_varDecl3"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::rept_varDecl3(){
    if(lookAhead.getType() == TokenType::OPENSQUARE){
        if(arraySize() && rept_varDecl3()){
            std::cout<<"rept_varDecl3 -> arraySize rept_Decl3"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::SEMICOLON){
        std::cout<<"rept_varDecl3 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::expr(){
    if(lookAhead.getType() == TokenType::OPENPAR || lookAhead.getType() == TokenType::FLOAT_VAL || lookAhead.getType() == TokenType::INTEGER_VAL
        || lookAhead.getType() == TokenType::NOT || lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT){
        if(arithExpr() && relExprRest()){
            std::cout<<"expr -> arithExpr relExprRest"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::relExprRest(){
    if(lookAhead.getType() == TokenType::GT || lookAhead.getType() == TokenType::GTEQ || lookAhead.getType() == TokenType::LT || lookAhead.getType() == TokenType::LTEQ
        || lookAhead.getType() == TokenType::NOTEQ || lookAhead.getType() == TokenType::EQ){
        if(relOp() && arithExpr()){
            std::cout<<"relExprRest -> relOp arithExpr"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSEPAR || lookAhead.getType() == TokenType::COMMA || 
        lookAhead.getType() == TokenType::SEMICOLON){
        std::cout<<"relExprRest -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::fParams(){
    if(lookAhead.getType() == TokenType::ID){
        if(match(TokenType::ID) && match(TokenType::COLON) && type() && rept_fParamas3() && rept_fParams4()){
            std::cout<<"fParams -> id : type rept_fParams3 rept_fParams4"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSEPAR){
        std::cout<<"fParams -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::rept_fParamas3(){
    if(lookAhead.getType() == TokenType::OPENSQUARE){
        if(arraySize() && rept_fParamas3()){
            std::cout<<"rept_fParams3 -> arraySize rept_fParams3"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSEPAR || lookAhead.getType() == TokenType::COMMA){
        std::cout<<"rept_fParams3 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::rept_fParams4(){
    if(lookAhead.getType() == TokenType::COMMA){
        if(fParamsTail() && rept_fParams4()){
            std::cout<<"rept_fParams4 -> fParamsTail rept_fParams4"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSEPAR){
        std::cout<<"rept_fParams4 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::fParamsTail(){
    if(lookAhead.getType() == TokenType::COMMA){
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
     if(lookAhead.getType() == TokenType::OPENSQUARE){
        if(arraySize() && rept_fParamsTail4()){
            std::cout<<"rept_fParamsTail4 -> arraySize rept_fParamsTail4"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSEPAR || lookAhead.getType() == TokenType::COMMA){
        std::cout<<"rept_fParamsTail4 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::aParams(){
    if(lookAhead.getType() == TokenType::OPENPAR || lookAhead.getType() == TokenType::FLOAT_VAL || lookAhead.getType() == TokenType::INTEGER_VAL
        || lookAhead.getType() == TokenType::NOT || lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT){
        if(expr() && rept_aParams1()){
            std::cout<<"aParams -> expr rept_aParams1"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSEPAR){
        std::cout<<"aParams -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::rept_aParams1(){
     if(lookAhead.getType() == TokenType::COMMA){
        if(aParamsTail() && rept_aParams1()){
            std::cout<<"rept_aParams1 -> aParamsTail rept_aParams1"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSEPAR){
        std::cout<<"rept_aParams1 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::aParamsTail(){
    if(lookAhead.getType() == TokenType::COMMA){
        if(match(TokenType::COMMA) && expr()){
            std::cout<<"aParamsTail -> , expr"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::idOrSelf(){
    if(lookAhead.getType() == TokenType::SELF){
        if(match(TokenType::SELF)){
            std::cout<<"idOrSelf -> self"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::ID){
        if(match(TokenType::ID)){
            std::cout<<"idOrSelf -> id"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::idNest(){
    if(lookAhead.getType() == TokenType::DOT){
        if (match(TokenType::DOT) && match(TokenType::ID) && idNest2()) {
            std::cout << "idNest -> . id idnest2 " << std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};

bool Parser::idNest2() {
    if (lookAhead.getType() == TokenType::OPENSQUARE) {
        if (rept_idnest10()) {
            std::cout << "idNest2 -> rept_idnest10" << std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::OPENPAR) {
        if (match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR)) {
            std::cout << "idNest2 -> ( aParams )" << std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::GT || lookAhead.getType() == TokenType::GTEQ || lookAhead.getType() == TokenType::LT || lookAhead.getType() == TokenType::LTEQ
        || lookAhead.getType() == TokenType::NOTEQ || lookAhead.getType() == TokenType::EQ || lookAhead.getType() == TokenType::CLOSEPAR
        || lookAhead.getType() == TokenType::COMMA || lookAhead.getType() == TokenType::SEMICOLON || lookAhead.getType() == TokenType::CLOSESQUARE
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT || lookAhead.getType() == TokenType::OR ||
        lookAhead.getType() == TokenType::MULT || lookAhead.getType() == TokenType::DIV || lookAhead.getType() == TokenType::AND ||
        lookAhead.getType() == TokenType::DOT || lookAhead.getType() == TokenType::ASSIGN) {
        std::cout << "idnest2 -> EPSILON" << std::endl;
        return true;
    }
    else return false;
}
bool Parser::rept_idnest10(){
    if(lookAhead.getType() == TokenType::OPENSQUARE){
        if(indice() && rept_idnest10()){
            std::cout<<"rept_idnest10 -> indice rept_idnest10"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::GT || lookAhead.getType() == TokenType::GTEQ || lookAhead.getType() == TokenType::LT || lookAhead.getType() == TokenType::LTEQ
        || lookAhead.getType() == TokenType::NOTEQ || lookAhead.getType() == TokenType::EQ || lookAhead.getType() == TokenType::CLOSEPAR
        || lookAhead.getType() == TokenType::COMMA || lookAhead.getType() == TokenType::SEMICOLON || lookAhead.getType() == TokenType::CLOSESQUARE
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT || lookAhead.getType() == TokenType::OR ||
        lookAhead.getType() == TokenType::MULT || lookAhead.getType() == TokenType::DIV || lookAhead.getType() == TokenType::AND ||
        lookAhead.getType() == TokenType::DOT || lookAhead.getType() == TokenType::ASSIGN){

        std::cout<<"rept_idnest10 -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::indice(){
    if(lookAhead.getType() == TokenType::OPENSQUARE){
        if(match(TokenType::OPENSQUARE) && arithExpr() && match(TokenType::CLOSESQUARE)){
            std::cout<<"indice -> [ arithExpr ]"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};

bool Parser::variable(){
    if(lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF){
        if(idOrSelf() && variable2()){
            std::cout<<"variable -> idnest id rept_idnest10"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::variable2() {
    if (lookAhead.getType() == TokenType::OPENSQUARE || lookAhead.getType() == TokenType::DOT) {
        if (rept_idnest10() && rept_variable()) {
            std::cout << "variable2 -> rept_idnest10 rept_variable" << std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::OPENPAR) {
        if (match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR) && idNest()) {
            std::cout << "( aParams ) idnest" << std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::CLOSEPAR || lookAhead.getType() == TokenType::ASSIGN) {
        std::cout << "variable2 -> EPSILON" << std::endl;
        return true;
    }
    else return false;
}

bool Parser::rept_variable() {
    if (lookAhead.getType() == TokenType::DOT) {
        if (varIdNest() && rept_variable()) {
            std::cout << "rept_variable -> varidnest rept_variable" << std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::CLOSEPAR || lookAhead.getType() == TokenType::ASSIGN) {
        std::cout << "rept_variable -> EPSILON" << std::endl;
        return true;
    }
}

bool Parser::varIdNest() {
    if (lookAhead.getType() == TokenType::DOT) {
        if (match(TokenType::DOT) && match(TokenType::ID) && varIdNest2()) {
            std::cout << "varidnest -> . id varidnest2" << std::endl;
            return true;
        }
        else return false;
    }
    else return false;
}

bool Parser::varIdNest2() {
    if (lookAhead.getType() == TokenType::OPENSQUARE) {
        if (rept_idnest10()) {
            std::cout << "varidnest2 -> rept_idnest10" << std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::OPENPAR) {
        if (match(TokenType::OPENPAR) && aParams() && match(TokenType::CLOSEPAR) && varIdNest()) {
            std::cout << "varidnest2 -> ( aParams ) varidnest" << std::endl;
            return true;
        }
        else return false;
    }
    else if (lookAhead.getType() == TokenType::CLOSEPAR || lookAhead.getType() == TokenType::ASSIGN || lookAhead.getType() == TokenType::DOT) {
        std::cout << "varidnest2 -> EPSILON" << std::endl;
        return true;
    }
    else return false;
}

bool Parser::localVarDecl(){
    if(lookAhead.getType() == TokenType::LOCAL){
        if(match(TokenType::LOCAL) && varDecl()){
            std::cout<<"localVarDecl -> local varDecl "<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};

bool Parser::relExpr(){
    if(lookAhead.getType() == TokenType::OPENPAR || lookAhead.getType() == TokenType::FLOAT_VAL || lookAhead.getType() == TokenType::INTEGER_VAL
        || lookAhead.getType() == TokenType::NOT || lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF
        || lookAhead.getType() == TokenType::ADD || lookAhead.getType() == TokenType::SUBT){
        if(arithExpr() && relOp() && arithExpr()){
            std::cout<<"relExpr -> arithExpr relOp arithExpr "<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};

bool Parser::assignOp(){
    if(lookAhead.getType() == TokenType::ASSIGN){
        if(match(TokenType::ASSIGN)){
            std::cout<<"assignOp -> :="<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::relOp(){
    if(lookAhead.getType() == TokenType::GTEQ){
        if(match(TokenType::GTEQ)){
            std::cout<<"relOp -> >="<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::GT){
        if(match(TokenType::GT)){
            std::cout<<"relOp -> >"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::EQ){
        if(match(TokenType::EQ)){
            std::cout<<"relOp -> =="<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::NOTEQ){
        if(match(TokenType::NOTEQ)){
            std::cout<<"relOp -> <>"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::LTEQ){
        if(match(TokenType::LTEQ)){
            std::cout<<"relOp -> <="<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::LT){
        if(match(TokenType::LT)){
            std::cout<<"relOp -> <"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::multOp(){
    if(lookAhead.getType() == TokenType::AND){
        if(match(TokenType::AND)){
            std::cout<<"multOp -> and"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::DIV){
        if(match(TokenType::DIV)){
            std::cout<<"multOp -> /"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::MULT){
        if(match(TokenType::MULT)){
            std::cout<<"multOp -> *"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::addOp(){
    if(lookAhead.getType() == TokenType::OR){
        if(match(TokenType::OR)){
            std::cout<<"addOp -> or"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::SUBT){
        if(match(TokenType::SUBT)){
            std::cout<<"addOp -> -"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::ADD){
        if(match(TokenType::ADD)){
            std::cout<<"addOp -> +"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::sign(){
    if(lookAhead.getType() == TokenType::ADD){
        if(match(TokenType::ADD)){
            std::cout<<"sign -> +"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::SUBT){
        if(match(TokenType::SUBT)){
            std::cout<<"sign -> -"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};
bool Parser::statBlock(){
    if(lookAhead.getType() == TokenType::IF || lookAhead.getType() == TokenType::READ || lookAhead.getType() == TokenType::RETURN
        || lookAhead.getType() == TokenType::WHILE || lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF){
        if(statement()){
            std::cout<<"statBlock -> statement"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::OPENCURLY){
        if(match(TokenType::OPENCURLY) && rept_statBlock1() && match(TokenType::CLOSECURLY)){
            std::cout<<"statBlock -> { rept_statBlock1 }"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::ELSE || lookAhead.getType() == TokenType::SEMICOLON){
        std::cout<<"statBlock -> EPSILON"<<std::endl;
        return true;
    }
    else return false;
};
bool Parser::rept_statBlock1(){
    if(lookAhead.getType() == TokenType::IF || lookAhead.getType() == TokenType::READ || lookAhead.getType() == TokenType::RETURN
        || lookAhead.getType() == TokenType::WHILE || lookAhead.getType() == TokenType::WRITE || lookAhead.getType() == TokenType::ID
        || lookAhead.getType() == TokenType::SELF){
        if(statement() && rept_statBlock1()){
            std::cout<<"rept_statblock1 -> statement rept_statBlock1"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::CLOSECURLY){
        std::cout<<"rept_statBlock1 -> EPSILON"<<std::endl;
        return true;
    }
    else return false; 
};
bool Parser::statement(){
    if(lookAhead.getType() == TokenType::ID || lookAhead.getType() == TokenType::SELF){
        if(idOrSelf() && factor2() && VarOrFunc() && assignStat() && match(TokenType::SEMICOLON)){
            std::cout<<"statement -> variable assignop expr;"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::WRITE){
        if(match(TokenType::WRITE) && match(TokenType::OPENPAR) && expr() && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)){
                std::cout<<"statement -> write (expr) ;"<<std::endl;
                return true;
            }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::WHILE){
        if(match(TokenType::WHILE) && match(TokenType::OPENPAR) && relExpr() && match(TokenType::CLOSEPAR)
            && statBlock() && match(TokenType::SEMICOLON)){
                std::cout<<"statement -> while(relExpr) statBlock ;"<<std::endl;
                return true;
            }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::RETURN){
        if(match(TokenType::RETURN) && match(TokenType::OPENPAR) && expr() && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)){
                std::cout<<"statement -> return (expr) ;"<<std::endl;
                return true;
            }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::READ){
        if(match(TokenType::READ) && match(TokenType::OPENPAR) && variable() && match(TokenType::CLOSEPAR)
            && match(TokenType::SEMICOLON)){
                std::cout<<"statement -> read(variable) ;"<<std::endl;
                return true;
            }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::IF){
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
    if(lookAhead.getType() == TokenType::ASSIGN){
        if(assignOp() && expr()){
            std::cout<<"assignStat -> assignOp expr"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::SEMICOLON){
        std::cout<<"assignStat -> EPSILON"<<std::endl;
        return true;

    }
    else return false;
};


bool Parser::visibility(){
    if(lookAhead.getType() == TokenType::PUBLIC){
        if(match(TokenType::PUBLIC)){
            std::cout<<"visibility -> public"<<std::endl;
            return true;
        }
        else return false;
    }
    else if(lookAhead.getType() == TokenType::PRIVATE){
        if(match(TokenType::PRIVATE)){
            std::cout<<"visibility -> private"<<std::endl;
            return true;
        }
        else return false;
    }
    else return false;
};