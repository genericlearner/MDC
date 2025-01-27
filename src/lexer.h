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
        Token createToken(TokenType type, std::string& lexeme);
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



};

#endif