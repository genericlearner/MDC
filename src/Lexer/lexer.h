#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include <fstream>
#include <ostream>
#include <string>


class Lexer
{
    public:
        Lexer();
        Lexer(std::ifstream* source, std::ostream* outLexTokens, std::ofstream* outLexErrors);
        ~Lexer();

        void setOutputFile(std::ostream* outputFile);
        void setErrorFile(std::ofstream* errorFile);
        void setSource(std::ifstream* inputFile);
        Token nextToken();
        char nextChar();
        void backupChar();
        Token createCurrToken(TokenType type, std::string& lexeme, size_t curr_line);
        
    private:
        std::ifstream* source;
        std::ostream* outLexTokens;
        std::ofstream* outLexErrors;
        char currentChar;
        size_t line;

        void writeToken(const Token& token);
        void writeError(const Token& errToken);
        Token errorLoop(std::string &lex);
        Token errorLoopAlpha(std::string &lex);
        Token createToken(TokenType type, const std::string& lexeme);
        Token matchSingleCharToken(TokenType type) ;
        bool isOperatorAlpha(char ch);
        bool isOperatorNum(char ch);
        bool isBracket(char ch);



};

#endif