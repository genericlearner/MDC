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
#include <stack>
class Parser{

    private:

        std::unordered_map<std::string, std::vector<std::vector<TokenType>>>firstSet;
        std::unordered_map<std::string, std::vector<TokenType>>followSet;
        Token lookAhead;
        Token lastToken;
        Lexer& lexer;
        AST* ast;
        
        std::stack<AST*>attrStack;
        bool checkFirstSet(std::string funcName, int pos);
        bool checkAllFirstSet(std::string funcName);
        bool checkFollowSet(std::string funcName);
        bool epsilonCheck(std::string funcName);
        bool match(TokenType token);
       
        
        bool skipErrors(std::string funcName);

        
        

        bool start(AST** startS);
        bool prog(AST** progS);
        bool classimplfunc(AST** classImplFuncS);
        bool vismemberdecl(AST** visMemberDeclS);
        bool classdecl(AST** classDeclS);
        bool isa1(AST** isa1S);
        bool isa2(AST** isa2S);
        bool impldef(AST** implDefS);
        bool implbody(AST** implBodyS);
        bool funcdef(AST** funcDefS);
        bool visibility(AST** visibilityS);
        bool memdecl(AST** memDeclS);
        bool funcdecl(AST** funcDecl);
        bool funchead(AST** funcHead);
        bool funcbody(AST** funcBodyS);
        bool localvardeclorstat(AST** LocalVarDeclOrStat);
        bool localvardeclorstat2(AST** LocalVarDeclOrStat);
        bool attrdecl(AST** attrDeclS);
        bool localvardecl(AST** localVarDecl);
        bool vardecl(AST** varDecl);
        bool statement(AST** statementAST);
        bool funcallorassign(AST** funcOrAssignStatS);
        bool funcallorassign2();
        bool funcasllorassign3();
        bool funcallorassign4();
        bool statblock(AST** statBlock);
        bool statements(AST** statementList);
        bool expr(AST** exprS);
        bool expr2(AST** exprRest, AST* arithExprFirst);
        bool relexpr(AST** relExprS);
        bool arithexpr(AST** arithExprS);
        bool rightrecarithexpr(AST** arithExprRest, AST* leftTerm);
        bool sign(AST** signS);
        bool term(AST** termS);
        bool rightrecterm();
        bool factor();
        bool factor2();
        bool indice(AST** indiceAST);
        bool indices(AST** indiceRept);
        bool reptvariableorfunctioncall();
        bool variable();
        bool variable2();
        bool reptvariable();
        bool idNest();
        bool idNest2();
        bool varIdNest();
        bool varIdNest2();
        bool arraySize(AST** arraySizeAST);
        bool arraySize2(AST** arraySizeAST);
        bool arraySizes(AST** arraySizeAST);
        bool type(AST** typeAST);
        bool returnType(AST** returnTypeAST);
        bool aParams(AST** aParams);
        bool reptaParams1(AST** aParamsRest);
        bool aParamsTail(AST** aParamsRest);
        bool fParams(AST** fParamsAST);
        bool reptfParams1(AST** fParamsTail);
        bool fParamstail(AST** fParamsTail);
        bool assignOp(AST** assignOpS);
        bool relOp(AST** relOpS);
        bool addOp(AST** addOpS);
        bool multOp(AST** multOpS);
        bool idOrSelf(AST** idorSelf);




        
        

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
