#include "lexer.h"
#include <unordered_map>
// Map of reserved words to their corresponding token types
std::unordered_map<std::string, TokenType>reservedWords = {
    {"or", TokenType::OR},
    {"and", TokenType::AND},
    {"not", TokenType::NOT},
    {"int", TokenType::INT_T},
    {"float", TokenType::FLOAT_T},
    {"void", TokenType::VOID},
    {"class", TokenType::CLASS},
    {"self", TokenType::SELF},
    {"isa", TokenType::ISA},
    {"implementation", TokenType::IMPLEMENTATION},
    {"while", TokenType::WHILE},
    {"if", TokenType::IF},
    {"then", TokenType::THEN},
    {"else",TokenType::ELSE},
    {"read", TokenType::READ},
    {"write", TokenType::WRITE},
    {"return", TokenType::RETURN},
    {"local", TokenType::LOCAL},
    {"constructor", TokenType::CONSTRUCTOR},
    {"attribute", TokenType::ATTRIBUTE},
    {"function", TokenType::FUNCTION},
    {"public", TokenType::PUBLIC},
    {"private", TokenType::PRIVATE},


};


/**
 * @brief Constructs a new Lexer object.
 * 
 * @param source Pointer to the input file stream from which the lexer reads the source code.
 * @param outLexTokens Pointer to the output stream where the lexer writes the recognized tokens.
 * @param outLexErrors Pointer to the output file stream where the lexer writes any lexical errors encountered.
 * Initializes the Lexer with default values. Sets the source, outLexErrors, 
 * and outLexTokens pointers to nullptr. Initializes the current character to 
 * the null character and sets the line number to 1.
 */
Lexer::Lexer()
{
    source = nullptr;
    outLexErrors = nullptr;
    outLexTokens = nullptr;
    currentChar = '\0';
    line = 1;
}
Lexer::Lexer(std::ifstream* source, std::ostream* outLexTokens, std::ofstream* outLexErrors)
{
    this->source = source;
    this->outLexTokens = outLexTokens;
    this->outLexErrors = outLexErrors;
    currentChar = '\0';
    line = 1;
}

Lexer::~Lexer()
{
  
}

void Lexer::setSource(std::ifstream* inputFile)
{
    source = inputFile;
    if(source){
        currentChar = nextChar();
    }
}

void Lexer::setOutputFile(std::ostream* outputFile)
{
    outLexTokens = outputFile;
}

void Lexer::setErrorFile(std::ofstream* errorFile)
{
    outLexErrors = errorFile;
}

/**
 * @brief Retrieves the next character from the source input.
 * 
 * This function reads the next character from the source input stream.
 * If the character is a newline ('\n'), it increments the line counter.
 * If the end of the source input is reached, it returns EOF.
 * 
 * @return char The next character from the source input, or EOF if the end is reached.
 */
char Lexer::nextChar()
{
    if(source &&source->get(currentChar))
    {
        if(currentChar == '\n'){
            line++;
        }
        return currentChar;
    }
    return EOF;
}
/**
 * Handles the error loop for the lexer, capturing invalid tokens.
 *
 * This function continues to read characters until it encounters a whitespace,
 * newline, or EOF. It appends each character to the provided lexeme string.
 * Once the loop terminates, it creates and returns an error token of type
 * INVALID_NUM with the accumulated lexeme.
 *
 * @param lex A reference to the string where the invalid token will be stored.
 * @return A Token object representing the invalid token.
 */
Token Lexer::errorLoop(std::string &lex){
    while(!isspace(currentChar) && currentChar != '\n' && currentChar != EOF){
        lex += currentChar;
        currentChar = nextChar();
    }
    Token errorToken = createToken(TokenType::INVALID_NUM, lex);
    return errorToken ;
    
}

/**
 * @brief Handles the error loop for invalid alphanumeric tokens.
 * 
 * This function continues to read characters until a whitespace, newline, or EOF is encountered.
 * It appends each character to the provided lexeme string.
 * Once the loop terminates, it creates and returns an error token of type INVALID_ID.
 * 
 * @param lex A reference to the string where the invalid token will be stored.
 * @return Token An error token of type INVALID_ID containing the invalid lexeme.
 */
Token Lexer::errorLoopAlpha(std::string &lex){
    while(!isspace(currentChar) && currentChar != '\n' && currentChar != EOF){
        lex += currentChar;
        currentChar = nextChar();
    }
    Token errorToken = createToken(TokenType::INVALID_ID, lex);
    return errorToken ;
    
}

/**
 * Matches a single character token of the specified type.
 *
 * This function creates a token from the current character, writes the token,
 * advances to the next character, and returns the created token.
 *
 * @param type The type of the token to be created.
 * @return The created token.
 */
Token Lexer::matchSingleCharToken(TokenType type){
    std::string lex(1, currentChar);
    Token token = createToken(type, lex);
    writeToken(token);
    currentChar = nextChar();
    return token;
}


/**
 * @brief Backs up one character in the input stream.
 *
 * This function moves the input stream position back by one character.
 * If the character being backed up is a newline character ('\n'), 
 * it also decrements the line counter.
 *
 * @note This function assumes that the source stream supports the unget() operation.
 */
void Lexer::backupChar(){
    if(source && source->unget()){
        if(currentChar == '\n'){
            line--;
        }

    }
}

/**
 * @brief Extracts the next token from the input stream.
 * 
 * This function processes the input stream character by character to identify and return the next token.
 * It handles various types of tokens including identifiers, numbers, comments, operators, and delimiters.
 * 
 * @return Token The next token identified from the input stream.
 * 
 * The function performs the following steps:
 * - Skips any whitespace characters.
 * - Checks for end-of-file and returns an EOF token if reached.
 * - Handles identifiers and reserved words.
 * - Processes numeric literals, including integers and floating-point numbers.
 * - Identifies and processes single-line and multi-line comments.
 * - Matches single-character tokens for operators and delimiters.
 * - Handles compound operators like '==', '=>', '<=', '<>', and '>='.
 * - Returns an error token for any unrecognized characters.
 */
Token Lexer::nextToken(){
    
    while(isspace(currentChar)){
        currentChar = nextChar();
    }

    if(currentChar == EOF){
        std::string s{currentChar};
        Token eofToken = createToken(TokenType::ENDOFILE, s);
        return eofToken;
    }
    if(currentChar == '_'){
        std::string lex;
        lex += '_';
        currentChar = nextChar();
        Token errToken = errorLoopAlpha(lex);
        writeError(errToken);
        return errToken;
    }
    if(isalpha(currentChar)){
        std::string lex;
        
        while(true){
            if(isalnum(currentChar) || currentChar == '_'){
                lex += currentChar;
                currentChar = nextChar();
            }
            else if(isspace(currentChar)){
                break;
            }
            else{
                Token errToken = errorLoopAlpha(lex);
                writeError(errToken);
                return errToken;
            }
        }
    

        backupChar();
        if(reservedWords.find(lex) != reservedWords.end()){
            Token resWordToken = createToken(reservedWords[lex], lex);
            writeToken(resWordToken);
            return resWordToken;
            }
        Token idToken = createToken(TokenType::ID, lex);
        writeToken(idToken);
        return idToken;
    }
        

    if(isdigit(currentChar)){
        std::string lex;
        bool isFloat = false;

        while(true){
            if(isdigit(currentChar)){
                lex += currentChar;
                currentChar = nextChar();
            }
            else if(isspace(currentChar) || currentChar == 'e' || currentChar == '.'){
                break;
            }
            else{
                Token errToken = errorLoop(lex);
                writeError(errToken);
                return errToken;
            }
        }
        /*
        do{
            lex += currentChar;
            currentChar = nextChar();
        }while(isdigit(currentChar));
        
        if(currentChar != '.' || currentChar != 'e'){
            Token errToken = errorLoop(lex);
            writeError(errToken);
            return errToken;
        }*/
        if(lex[0] == '0' && lex.length() > 1){
            Token errToken = errorLoop(lex);
            writeError(errToken);
            return errToken;
        }

        if(currentChar == '.'){
            isFloat = true;
            lex += currentChar;
            currentChar = nextChar();

            if(!isdigit(currentChar)){
                Token errToken = errorLoop(lex);
                writeError(errToken);
                return errToken;
            }
            while(isdigit(currentChar)){
                lex += currentChar;
                currentChar = nextChar();
            }

            if(lex.back() == '0'){
                Token errToken = errorLoop(lex);
                writeError(errToken);
                return errToken;
            }


        }
        if(currentChar == 'e'){
            isFloat = true;
            lex += currentChar;
            currentChar = nextChar();

            if(isdigit(currentChar) && currentChar != '0' || currentChar == '-'){
                lex += currentChar;
                currentChar = nextChar();
            }
            else{
                Token errToken = errorLoop(lex);
                writeError(errToken);
                return errToken;
            }
            if(!isdigit(currentChar)){
                Token errToken = errorLoop(lex);
                writeError(errToken);
                return errToken;
            }
            while(isdigit(currentChar)){
                lex += currentChar;
                currentChar = nextChar();
            }
        }
        backupChar();
        Token nToken = createToken(isFloat? TokenType::FLOAT_VAL : TokenType::INTEGER_VAL, lex);
        writeToken(nToken);
        return nToken;
    }

    if(currentChar == '/'){

        char nextc = nextChar();
        std::string lex;
        lex+= currentChar;

        if(nextc == '/'){
            size_t curr_line = line;
            lex += nextc;
            currentChar = nextChar();
            while(currentChar != '\n' && currentChar != EOF){
                lex +=currentChar;
                currentChar = nextChar();
            }

            Token cmtToken = createCurrToken(TokenType::COMMENT, lex, curr_line);
            writeToken(cmtToken);
            currentChar = nextChar();
            return cmtToken;

        }
       else if (nextc == '*') { // Multi-line comment
            size_t curr_line = line;
            lex += nextc; // Add the '*'
            currentChar = nextChar();
            int blockCommentDepth = 1;

             while (currentChar != EOF) {
                if (currentChar == '*' && nextChar() == '/') { 
                lex += "*"; 
                lex += "/"; 
                blockCommentDepth--; // Close one level of block comment
                if (blockCommentDepth == 0) {
                    currentChar = nextChar(); // Move past the '/'
                    break; 
                }
            } else if (currentChar == '/' && nextChar() == '*') { 
                    lex += "/"; 
                    lex += "*"; 
                    blockCommentDepth++; 
            } else {
            lex += currentChar; 
            }

        currentChar = nextChar(); // Read next character
    }

    // Check if block comment was not terminated correctly
    if (blockCommentDepth > 0) {
        Token errorToken = createToken(TokenType::INVALID_NUM, lex);
        writeError(errorToken);
        writeToken(errorToken);
        return errorToken;
    }

    Token blockToken = createCurrToken(TokenType::BLOCK_COMMENT, lex, curr_line);
    writeToken(blockToken);
    return blockToken;
    }
        else{
            std::string divop = "/";
            Token divToken = createToken(TokenType::DIV, divop);
            writeToken(divToken);
            
            return divToken;
        }
    }

    if(currentChar == '+')return matchSingleCharToken(TokenType::ADD);
    if(currentChar == '-')return matchSingleCharToken(TokenType::SUBT);
    if(currentChar == '*')return matchSingleCharToken(TokenType::MULT);
    
    if(currentChar == '='){
        char nextc = nextChar();
        std::string lex;
        if(nextc == '='){
            
            lex = "==";
            Token eqToken = createToken(TokenType::EQ, lex);
            writeToken(eqToken);
            currentChar = nextChar();
            return eqToken;
        }
        else if(nextc == '>'){
            lex = "=>";
            Token arrToken = createToken(TokenType::ARROW, lex);
            writeToken(arrToken);
            currentChar = nextChar();
            return arrToken;
        }
        
    }


   if(currentChar == '{')return matchSingleCharToken(TokenType::OPENCURLY);
   else if(currentChar == '}')return matchSingleCharToken(TokenType::CLOSECURLY);
   else if(currentChar == '(')return matchSingleCharToken(TokenType::OPENPAR);
   else if(currentChar == ')')return matchSingleCharToken(TokenType::CLOSEPAR);
   else if(currentChar == '[')return matchSingleCharToken(TokenType::OPENSQUARE);
   else if(currentChar == ']')return matchSingleCharToken(TokenType::CLOSESQUARE);
   else if(currentChar == ';')return matchSingleCharToken(TokenType::SEMICOLON);
   else if(currentChar == '.')return matchSingleCharToken(TokenType::DOT);
   else if(currentChar == ',')return matchSingleCharToken(TokenType::COMMA);
   else if(currentChar == ':'){
        char nextc = nextChar();
        if(nextc == '='){
            std::string assignop = ":=";
            Token assToken = createToken(TokenType::ASSIGN, assignop);
            writeToken(assToken);
            currentChar = nextChar();
            return assToken;
        }
        else{
           return matchSingleCharToken(TokenType::COLON);
        }

   }

   if(currentChar == '<'){
        char nextc = nextChar();

        if(nextc == '='){
            std::string lessThanEq = "<=";
            Token leqToken = createToken(TokenType::LTEQ, lessThanEq);
            writeToken(leqToken);
            currentChar = nextChar();
            return leqToken;
        }
        else if(nextc == '>'){
            std::string neq = "<>";
            Token neqToken = createToken(TokenType::NOTEQ, neq);
            writeToken(neqToken);
            currentChar = nextChar();
            return neqToken;
        }
        else{
            std::string lt = "<";
            Token ltToken = createToken(TokenType::LT, lt);
            writeToken(ltToken);
            currentChar = nextChar();
            return ltToken;
        }

   }
   else if(currentChar == '>'){
        char nextc = nextChar();
        if(nextc == '='){
            std::string greaterThanEq = ">=";
            Token geqToken = createToken(TokenType::GTEQ, greaterThanEq);
            writeToken(geqToken);
            currentChar = nextChar();
            return geqToken;
        }
        
            std::string gt = ">";
            Token gtToken = createToken(TokenType::GT, gt);
            writeToken(gtToken);
            return gtToken;
   }
    std::string lex;
   lex += currentChar;
   currentChar = nextChar();
   Token unknToken = createToken(TokenType::INVALID_CHAR, lex);
   writeError(unknToken);
   writeToken(unknToken);
   return unknToken;
   
   
         
}
/**
 * @brief Creates a new token with the specified type, lexeme, and line number.
 * 
 * @param type The type of the token to be created.
 * @param lexeme The lexeme (string value) of the token.
 * @param curr_line The line number where the token was found.
 * @return Token The newly created token.
 */
Token Lexer::createCurrToken(TokenType type, std::string& lexeme, size_t curr_line){
    return Token(type, lexeme, curr_line);
}


/**
 * @brief Creates a new Token object.
 * 
 * @param type The type of the token.
 * @param lexeme The lexeme associated with the token.
 * @return Token The newly created token.
 */
Token Lexer::createToken(TokenType type,const std::string& lexeme){
    return Token(type, lexeme, line);
}

/**
 * @brief Writes a lexical error message to the output stream.
 * 
 * This function formats and writes a lexical error message to the output stream
 * specified by `outLexErrors`. The error message includes the type of the token,
 * the lexeme, and the line number where the error occurred.
 * 
 * @param errToken The token that caused the lexical error.
 */
void Lexer::writeError(const Token& errToken){
    if(outLexErrors){
        *outLexErrors<<"Lexecial Error: "<<errToken.getType()<<": "<<"\""<<errToken.getLexeme()<<"\""<<"at line: "<<errToken.getLine()<<"\n";
    }


}

/**
 * @brief Writes the token information to the standard output and an output stream.
 * 
 * This function outputs the token's type, lexeme, and line number to both the standard
 * output (console) and an output stream if the output stream is available.
 * 
 * @param token The token to be written. It contains the type, lexeme, and line number.
 */
void Lexer::writeToken(const Token& token){
    if(outLexTokens){
        std::cout<<"["<<token.getType()<<", "<<token.getLexeme()<<", "<<token.getLine()<<"]";
        *outLexTokens<<"["<<token.getType()<<", "<<token.getLexeme()<<", "<<token.getLine()<<"]\n";
    }

}