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
/**
 * @class Token
 * @brief Represents a token in the source code.
 * 
 * The Token class encapsulates information about a token, including its type,
 * lexeme, and the line number where it appears in the source code.
 */

/**
 * @brief Constructs a Token object.
 * 
 * @param type The type of the token.
 * @param lexeme The lexeme (text) of the token.
 * @param line The line number where the token appears.
 */

/**
 * @brief Gets the lexeme of the token.
 * 
 * @return A constant reference to the lexeme string.
 */

/**
 * @brief Gets the line number where the token appears.
 * 
 * @return The line number.
 */

/**
 * @brief Gets the type of the token.
 * 
 * @return The type of the token.
 */
class Token 
{

    private:
        TokenType type;
        std::string lexeme;
        size_t line;
    public:
        const std::string& getLexeme() const;
        size_t getLine() const;
        Token() : type(TokenType::UNKNOWN), lexeme(""), line(0) {};
        TokenType getType() const;

        // Constructor to initialize a token
        Token(TokenType type,const std::string& lexeme, size_t line);
};




#endif
