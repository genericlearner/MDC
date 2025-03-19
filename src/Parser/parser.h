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
        bool funcallorassign2(AST** funcOrAssignStatSNest, AST* leftVar);
        bool funcasllorassign3(AST** assignOrNest, AST* leftVar);
        bool funcallorassign4(AST** funcNest, AST* leftVar);
        bool statblock(AST** statBlock);
        bool statements(AST** statementList);
        bool expr(AST** exprS);
        bool expr2(AST** exprRest, AST* arithExprFirst);
        bool relexpr(AST** relExprS);
        bool arithexpr(AST** arithExprS);
        bool rightrecarithexpr(AST** arithExprRest, AST* leftTerm);
        bool sign(AST** signS);
        bool term(AST** termS);
        bool rightrecterm(AST** termTail, AST* leftFactor);
        bool factor(AST** factorS, AST* leftFactor);
        bool factor2(AST** factorContinue, AST* leftVar);
        bool indice(AST** indiceAST);
        bool indices(AST** indiceRept);
        bool reptvariableorfunctioncall(AST** varOrFunc, AST* left);
        bool variable(AST** varS);
        bool variable2(AST** varRestS, AST* leftVar);
        bool reptvariable(AST** varIdTailS, AST* leftVarId);
        bool idNest(AST** IDNest, AST* leftVar);
        bool idNest2(AST** idNest, AST* leftVar);
        bool varIdNest(AST** varNest, AST* leftVarId);
        bool varIdNest2(AST** varNestTail, AST* leftVarId);
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
