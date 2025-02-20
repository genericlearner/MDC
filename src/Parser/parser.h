#ifndef PARSER_H
#define PARSER_H
#include "../Lexer/Token.h"
#include <iostream>
#include "unordered_map"
#include "vector"
#include "../Lexer/lexer.h"
#include <fstream>
#include <ostream>

class Parser{

    private:

        std::unordered_map<std::string, std::vector<TokenType>>firstSet;
        std::unordered_map<std::string, std::vector<TokenType>>followSet;
        Token lookAhead;
        Lexer& lexer;
        bool checkFirstSet(std::string funcName);
        bool checkFollowSet(std::string funcName);
        bool epsilonCheck(std::string funcName);
        bool match(TokenType token);
        bool start();
        bool prog();
        bool rept_prog0();
        bool classOrImpleOrFunc();
        bool classDecl();
        bool opt_classDecl2();
        bool rept_opt_classDecl22();
        bool rept_classDecl4();
        bool implDef();
        bool rept_implDef3();
        bool funcDef();
        bool funcHead();
        bool funcBody();
        bool rept_funcBody1();
        bool localVarDeclOrStat();
        bool arithExpr();
        bool rightrec_arithExpr();
        bool term();
        bool rightrec_term();
        bool factor();
        bool factor2();
        bool VarOrFunc();
        bool arraySize();
        bool arraySizeTail();
        bool type();
        bool returnType();
        bool memberDecl();
        bool funcDecl();
        bool attributeDecl();
        bool varDecl();
        bool rept_varDecl3();
        bool expr();
        bool relExprRest();
        bool fParams();
        bool rept_fParamas3();
        bool rept_fParams4();
        bool fParamsTail();
        bool rept_fParamsTail4();
        bool aParams();
        bool rept_aParams1();
        bool aParamsTail();
        bool idOrSelf();
        bool idNest();
        bool idNest2();
        bool rept_idnest10();
        bool indice();
        bool variable();
        bool variable2();
        bool rept_variable();
        bool varIdNest();
        bool varIdNest2();
        bool localVarDecl();
        bool relExpr();
        bool assignOp();
        bool relOp();
        bool multOp();
        bool addOp();
        bool sign();
        bool statBlock();
        bool rept_statBlock1();
        bool statement();
        bool assignStat();
        bool visibility();
        bool skipErrors(std::string funcName);

    public:
        //Parser();
        Parser(std::ifstream& source, std::ostream& outDerivation, std::ofstream& syntaxErrors, Lexer& lexer);
        std::ifstream& source;
        std::ostream& outDerivation;
        std::ofstream& syntaxErrors;

        bool startParse();
        void writeDerivation();
        void writeError();





};

#endif
