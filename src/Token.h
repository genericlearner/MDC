#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

enum class TokenType
{
    UNKNOWN,

    ID,
    INTEGER_VAL,
    FLOAT_VAL,
    COMMENT,
    BLOCK_COMMENT,


    EQ,
    NOTEQ,
    LTEQ,
    GTEQ,
    LT,
    GT,
    ADD,
    SUBT,
    MULT,
    DIV,
    ASSIGN,
    OPENPAR,
    CLOSEPAR,
    OPENCURLY,
    CLOSECURLY,
    OPENSQUARE,
    CLOSESQUARE,
    SEMICOLON,
    COMMA,
    DOT,
    COLON, 
    ARROW,
    SCOPE,
    ENDOFILE,

    OR,
    AND,
    NOT,
    INT_T,
    FLOAT_T,
    VOID,
    CLASS,
    SELF,
    ISA,
    IMPLEMENTATION,
    WHILE,
    IF,
    THEN,
    ELSE, 
    READ,
    WRITE,
    RETURN,
    LOCAL,
    CONSTRUCTOR,
    ATTRIBUTE,
    FUNCTION,
    PUBLIC,
    PRIVATE,
        
    
    INVALID_NUM,
    INVALID_ID,
    INVALID_CHAR,
    UNCLOSED_COMMENT,

};
// Overload the << operator to print TokenType
std::ostream& operator<<(std::ostream& stream, TokenType tokenType);
class Token 
{

    private:
        TokenType type;
        std::string lexeme;
        size_t line;
    public:
        const std::string& getLexeme() const;
        size_t getLine() const;
        TokenType getType() const;

        // Constructor to initialize a token
        Token(TokenType type,const std::string& lexeme, size_t line);
};




#endif
