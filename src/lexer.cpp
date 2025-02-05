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
Token Lexer::errorLoop(std::string &lex){
    while(!isspace(currentChar) && currentChar != '\n' && currentChar != EOF){
        lex += currentChar;
        currentChar = nextChar();
    }
    Token errorToken = createToken(TokenType::INVALID_NUM, lex);
    return errorToken ;
    
}

Token Lexer::errorLoopAlpha(std::string &lex){
    while(!isspace(currentChar) && currentChar != '\n' && currentChar != EOF){
        lex += currentChar;
        currentChar = nextChar();
    }
    Token errorToken = createToken(TokenType::INVALID_ID, lex);
    return errorToken ;
    
}

Token Lexer::matchSingleCharToken(TokenType type){
    std::string lex(1, currentChar);
    Token token = createToken(type, lex);
    writeToken(token);
    currentChar = nextChar();
    return token;
}
void Lexer::backupChar(){
    if(source && source->unget()){
        if(currentChar == '\n'){
            line--;
        }

    }
}

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
Token Lexer::createCurrToken(TokenType type, std::string& lexeme, size_t curr_line){
    return Token(type, lexeme, curr_line);
}
Token Lexer::createToken(TokenType type,const std::string& lexeme){
    return Token(type, lexeme, line);
}

void Lexer::writeError(const Token& errToken){
    if(outLexErrors){
        *outLexErrors<<"Lexecial Error: "<<errToken.getType()<<": "<<"\""<<errToken.getLexeme()<<"\""<<"at line: "<<errToken.getLine()<<"\n";
    }


}

void Lexer::writeToken(const Token& token){
    if(outLexTokens){
        std::cout<<"["<<token.getType()<<", "<<token.getLexeme()<<", "<<token.getLine()<<"]";
        *outLexTokens<<"["<<token.getType()<<", "<<token.getLexeme()<<", "<<token.getLine()<<"]\n";
    }

}