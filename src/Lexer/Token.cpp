#include "Token.h"



Token::Token(TokenType type,const std::string& lexeme, size_t line){
    this->type = type;
    this->lexeme = lexeme;
    this->line = line;
}
const std::string& Token::getLexeme() const {
    return lexeme;
}

size_t Token::getLine() const {
    return line;
}

TokenType Token::getType() const {
    return type;
}
/**/
/**
 * @brief Overloaded stream insertion operator for TokenType.
 *
 * This function allows TokenType values to be output to an ostream.
 * It converts the TokenType enum values to their corresponding string
 * representations and inserts them into the provided output stream.
 *
 * @param stream The output stream to insert the TokenType string representation into.
 * @param tokenType The TokenType value to be converted to a string and inserted into the stream.
 * @return A reference to the output stream with the TokenType string representation inserted.
 */
std::string Token::tokenToString(TokenType token) {
    switch (token) {
    case TokenType::ID: 
        return "ID";
        break;
    case TokenType::INTEGER_VAL: 
        return "INTEGER_VAL";
        break;
    case TokenType::FLOAT_VAL: 
        return   "FLOAT_VAL";
        break;
    case TokenType::COMMENT: 
        return  "COMMENT";
        break;
    case TokenType::BLOCK_COMMENT: 
        return  "BLOCK_COMMENT";
        break;
    case TokenType::EQ: 
        return  "EQ";
        break;
    case TokenType::NOTEQ: 
        return  "NOTEQ";
        break;
    case TokenType::LTEQ: 
        return  "LTEQ";
        break;
    case TokenType::GTEQ: 
        return  "GTEQ";
        break;
    case TokenType::LT: 
        return  "LT";
        break;
    case TokenType::GT: 
        return  "GT";
        break;
    case TokenType::ADD: 
        return  "ADD";
        break;
    case TokenType::SUBT: 
        return  "SUBT";
        break;
    case TokenType::MULT: 
        return  "MULT";
        break;
    case TokenType::DIV: 
        return  "DIV";
        break;
    case TokenType::ASSIGN: 
        return  "ASSIGN";
        break;
    case TokenType::OPENPAR: 
        return  "OPENPAR";
        break;
    case TokenType::CLOSEPAR: 
        return  "CLOSEPAR";
        break;
    case TokenType::OPENCURLY: 
        return  "OPENCURLY";
        break;
    case TokenType::CLOSECURLY: 
        return  "CLOSECURLY";
        break;
    case TokenType::OPENSQUARE: 
        return  "OPENSQUARE";
        break;
    case TokenType::CLOSESQUARE: 
        return  "CLOSESQUARE";
        break;
    case TokenType::SEMICOLON: 
        return  "SEMICOLON";
        break;
    case TokenType::COMMA: 
        return  "COMMA";
        break;
    case TokenType::DOT: 
        return  "DOT";
        break;
    case TokenType::COLON: 
        return  "COLON";
        break;
    case TokenType::ARROW: 
        return  "ARROW";
        break;
    case TokenType::SCOPE: 
        return  "SCOPE";
        break;
    case TokenType::ENDOFILE: 
        return  "ENDOFFILE";
        break;
    case TokenType::OR: 
        return  "OR";
        break;
    case TokenType::AND: 
        return  "AND";
        break;
    case TokenType::NOT: 
        return  "NOT";
        break;
    case TokenType::INT_T: 
        return  "INT_T";
        break;
    case TokenType::FLOAT_T: 
        return  "FLOAT_T";
        break;
    case TokenType::VOID: 
        return  "VOID";
        break;
    case TokenType::CLASS: 
        return  "CLASS";
        break;
    case TokenType::SELF: 
        return  "SELF";
        break;
    case TokenType::ISA: 
        return  "ISA";
        break;
    case TokenType::IMPLEMENTATION: 
        return  "IMPLEMENTATION";
        break;
    case TokenType::WHILE: 
        return  "WHILE";
        break;
    case TokenType::IF: 
        return  "IF";
        break;
    case TokenType::THEN: 
        return  "THEN";
        break;
    case TokenType::ELSE: 
        return  "ELSE";
        break;
    case TokenType::READ: 
        return  "READ";
        break;
    case TokenType::WRITE: 
        return  "WRITE";
        break;
    case TokenType::RETURN: 
        return  "RETURN";
        break;
    case TokenType::LOCAL: 
        return  "LOCAL";
        break;
    case TokenType::CONSTRUCTOR: 
        return  "CONSTRUCTOR";
        break;
    case TokenType::ATTRIBUTE: 
        return  "ATTRIBUTE";
        break;
    case TokenType::FUNCTION: 
        return  "FUNCTION";
        break;
    case TokenType::PUBLIC: 
        return  "PUBLIC";
        break;
    case TokenType::PRIVATE: 
        return  "PRIVATE";
        break;
    case TokenType::INVALID_CHAR: 
        return  "INVALID_CHAR";
        break;
    case TokenType::INVALID_NUM: 
        return  "INVALID_NUM";
        break;
    case TokenType::INVALID_ID: 
        return  "INVALID_ID";
        break;
    case TokenType::UNCLOSED_COMMENT: 
        return  "INCOMPLETE_CMT";
        break;
    default: return  "UNKNOWN";
    }

}
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