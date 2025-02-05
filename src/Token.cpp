#include "Token.h"



Token::Token(TokenType type,const std::string& lexeme, size_t line){
    this->type = type;
    this->lexeme = lexeme;
    this->line = line;
}
const std::string& Token::getLexeme() const {
    return lexeme;
}

unsigned long long Token::getLine() const {
    return line;
}

TokenType Token::getType() const {
    return type;
}
/**/
std::ostream& operator<<(std::ostream& stream, TokenType tokenType) {
    switch (tokenType) {
        case TokenType::ID: return stream << "ID";
        case TokenType::INTEGER_VAL: return stream << "INTEGER_VAL";
        case TokenType::FLOAT_VAL: return stream << "FLOAT_VAL";
        case TokenType::COMMENT: return stream << "COMMENT";
        case TokenType::BLOCK_COMMENT: return stream << "BLOCK_COMMENT";
        case TokenType::EQ: return stream << "EQ";
        case TokenType::NOTEQ: return stream << "NOTEQ";
        case TokenType::LTEQ: return stream << "LTEQ";
        case TokenType::GTEQ: return stream << "GTEQ";
        case TokenType::LT: return stream << "LT";
        case TokenType::GT: return stream << "GT";
        case TokenType::ADD: return stream << "ADD";
        case TokenType::SUBT: return stream << "SUBT";
        case TokenType::MULT: return stream << "MULT";
        case TokenType::DIV: return stream << "DIV";
        case TokenType::ASSIGN: return stream << "ASSIGN";
        case TokenType::OPENPAR: return stream << "OPENPAR";
        case TokenType::CLOSEPAR: return stream << "CLOSEPAR";
        case TokenType::OPENCURLY: return stream << "OPENCURLY";
        case TokenType::CLOSECURLY: return stream << "CLOSECURLY";
        case TokenType::OPENSQUARE: return stream << "OPENSQUARE";
        case TokenType::CLOSESQUARE: return stream << "CLOSESQUARE";
        case TokenType::SEMICOLON: return stream << "SEMICOLON";
        case TokenType::COMMA: return stream << "COMMA";
        case TokenType::DOT: return stream << "DOT";
        case TokenType::COLON: return stream << "COLON";
        case TokenType::ARROW: return stream << "ARROW";
        case TokenType::SCOPE: return stream << "SCOPE";
        case TokenType::ENDOFILE: return stream << "ENDOFFILE";
        case TokenType::OR: return stream << "OR";
        case TokenType::AND: return stream << "AND";
        case TokenType::NOT: return stream << "NOT";
        case TokenType::INT_T: return stream << "INT_T";
        case TokenType::FLOAT_T: return stream << "FLOAT_T";
        case TokenType::VOID: return stream << "VOID";
        case TokenType::CLASS: return stream << "CLASS";
        case TokenType::SELF: return stream << "SELF";
        case TokenType::ISA: return stream << "ISA";
        case TokenType::IMPLEMENTATION: return stream << "IMPLEMENTATION";
        case TokenType::WHILE: return stream << "WHILE";
        case TokenType::IF: return stream << "IF";
        case TokenType::THEN: return stream << "THEN";
        case TokenType::ELSE: return stream << "ELSE";
        case TokenType::READ: return stream << "READ";
        case TokenType::WRITE: return stream << "WRITE";
        case TokenType::RETURN: return stream << "RETURN";
        case TokenType::LOCAL: return stream << "LOCAL";
        case TokenType::CONSTRUCTOR: return stream << "CONSTRUCTOR";
        case TokenType::ATTRIBUTE: return stream << "ATTRIBUTE";
        case TokenType::FUNCTION: return stream << "FUNCTION";
        case TokenType::PUBLIC: return stream << "PUBLIC";
        case TokenType::PRIVATE: return stream << "PRIVATE";
        case TokenType::INVALID_CHAR: return stream << "INVALID_CHAR";
        case TokenType::INVALID_NUM: return stream << "INVALID_NUM";
        case TokenType::INVALID_ID: return stream << "INVALID_ID";
        case TokenType::UNCLOSED_COMMENT: return stream << "INCOMPLETE_CMT";
        default: return stream << "UNKNOWN";
    }
}