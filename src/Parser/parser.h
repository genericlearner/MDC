#ifndef PARSER_H
#define PARSER_H
#include "../Lexer/Token.h"
#include <iostream>
#include "unordered_map"
#include "vector"
#include "../Lexer/lexer.h"
#include "../AST.h"
#include "../parserUtility.h"
#include <fstream>
#include <ostream>

class Parser{

    private:

        std::unordered_map<std::string, std::vector<std::vector<TokenType>>>firstSet;
        std::unordered_map<std::string, std::vector<TokenType>>followSet;
        Token lookAhead;
        Lexer& lexer;
        AST* ast;
        bool checkFirstSet(std::string funcName, int pos);
        bool checkAllFirstSet(std::string funcName);
        bool checkFollowSet(std::string funcName);
        bool epsilonCheck(std::string funcName);
        bool match(TokenType token);
       
        
        bool skipErrors(std::string funcName);

        
        

        bool start(AST** startS);
        bool prog(AST** progS);
        bool classimplfunc();
        bool vismemberdecl();
        bool classdecl();
        bool isa1();
        bool isa2();
        bool impldef();
        bool implbody();
        bool funcdef();
        bool visibility();
        bool memdecl();
        bool funcdecl();
        bool funchead();
        bool funcbody();
        bool localvardeclorstat();
        bool localvardeclorstat2();
        bool attrdecl();
        bool localvardecl();
        bool vardecl();
        bool statement();
        bool funcallorassign();
        bool funcallorassign2();
        bool funcasllorassign3();
        bool funcallorassign4();
        bool statblock();
        bool statements();
        bool expr();
        bool expr2();
        bool relexpr();
        bool arithexpr();
        bool rightrecarithexpr();
        bool sign();
        bool term();
        bool rightrecterm();
        bool factor();
        bool factor2();
        bool indice();
        bool indices();
        bool reptvariableorfunctioncall();
        bool variable();
        bool variable2();
        bool reptvariable();
        bool idNest();
        bool idNest2();
        bool varIdNest();
        bool varIdNest2();
        bool arraySize();
        bool arraySize2();
        bool arraySizes();
        bool type();
        bool returnType();
        bool aParams();
        bool reptaParams1();
        bool aParamsTail();
        bool fParams();
        bool reptfParams1();
        bool fParamstail();
        bool assignOp();
        bool relOp();
        bool addOp();
        bool multOp();
        bool idOrSelf();




        
        

    public:
        //Parser();
        Parser(std::ifstream& source, std::ostream& outDerivation, std::ofstream& syntaxErrors, Lexer& lexer);
        std::ifstream& source;
        std::ostream& outDerivation;
        std::ofstream& syntaxErrors;

        bool startParse();
        void writeDerivation();
        void writeError();
        AST* getast();





};

#endif
