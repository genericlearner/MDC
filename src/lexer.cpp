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
std::string Lexer::errorLoop(std::string &lex){
    while(!isspace(currentChar) || currentChar != '\n' || currentChar != EOF){
        lex += currentChar;
        currentChar = nextChar();
    }
    
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

    if(isalpha(currentChar)){
        std::string lex;
        do{
            lex +=currentChar;
            currentChar = nextChar();
        } while(isalnum(currentChar) || currentChar == '_');
    

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
        bool isValid = true;
        do{
            lex += currentChar;
            currentChar = nextChar();
        }while(isdigit(currentChar));

        if(lex[0] == '0' && lex.length() > 1){
            isValid = false;
            Token errToken = createToken(TokenType::INVALID_NUM, lex);
            writeError(errToken);
            writeToken(errToken);
            return errToken;
        }

        if(currentChar == '.'){
            isFloat = true;
            lex += currentChar;
            currentChar = nextChar();

            if(!isdigit(currentChar)){
                Token errorToken = createToken(TokenType::INVALID_NUM, lex);
                writeError(errorToken);
                writeToken(errorToken);
                return errorToken;
            }
            while(isdigit(currentChar)){
                lex += currentChar;
                currentChar = nextChar();
            }

            if(lex.back() == '0'){
                Token errorToken = createToken(TokenType::INVALID_NUM, lex);
                writeError(errorToken);
                writeToken(errorToken);
                return errorToken;
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
                Token errorToken = createToken(TokenType::INVALID_NUM, lex);
                writeError(errorToken);
                writeToken(errorToken);
                return errorToken;
            }
            if(!isdigit(currentChar)){
                Token errorToken = createToken(TokenType::INVALID_NUM, lex);
                writeError(errorToken);
                writeToken(errorToken);
                return errorToken;
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

    if(currentChar == '+'){
            std::string addOp = "+";
            Token addToken = createToken(TokenType::ADD, addOp);
            writeToken(addToken);
            currentChar = nextChar();
            return addToken;
    }
    else if(currentChar == '-'){
            std::string subOp = "-";
            Token subToken = createToken(TokenType::SUBT, subOp);
            writeToken(subToken);
            currentChar = nextChar();
            return subToken;
    }
    else if(currentChar == '*'){
            std::string multiOp = "*";
            Token multiToken = createToken(TokenType::MULT, multiOp);
            writeToken(multiToken);
            currentChar = nextChar();
            return multiToken;
    }

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
        else {
            Token errorToken = createToken(TokenType::INTEGER_VAL, lex);
            writeError(errorToken);
            writeToken(errorToken);
            currentChar = nextChar();
            return errorToken;
        }
    }


   if(currentChar == '{'){
        std::string curlybr = "{";
        Token lCurToken = createToken(TokenType::OPENCURLY, curlybr);
        writeToken(lCurToken);
        currentChar = nextChar();
        return lCurToken;
   }
   else if(currentChar == '}'){
        std::string closecurlybr = "}";
        Token rCurToken = createToken(TokenType::CLOSECURLY, closecurlybr);
        writeToken(rCurToken);
        currentChar = nextChar();
        return rCurToken;
   }
   else if(currentChar == '('){
        std::string openpar = "(";
        Token lParToken = createToken(TokenType::OPENPAR, openpar);
        writeToken(lParToken);
        currentChar = nextChar();
        return lParToken;
   }
   else if(currentChar == ')'){
        std::string closepar = ")";
        Token rParToken = createToken(TokenType::CLOSEPAR, closepar);
        writeToken(rParToken);
        currentChar = nextChar();
        return rParToken;
   }
   else if(currentChar == '['){
        std::string opensq = "[";
        Token lSqrToken = createToken(TokenType::OPENSQUARE, opensq);
        writeToken(lSqrToken);
        currentChar = nextChar();
        return lSqrToken;
   }
   else if(currentChar == ']'){
        std::string closesq = "]";
        Token rSqrToken = createToken(TokenType::CLOSESQUARE, closesq);
        writeToken(rSqrToken);
        currentChar = nextChar();
        return rSqrToken;
   }
   else if(currentChar == ';'){
        std::string semicolon = ";";
        Token semiColonToken = createToken(TokenType::SEMICOLON, semicolon);
        writeToken(semiColonToken);
        currentChar = nextChar();
        return semiColonToken;
   }
   else if(currentChar == '.'){
        std::string dot = ".";
        Token dotToken = createToken(TokenType::DOT, dot);
        writeToken(dotToken);
        currentChar = nextChar();
        return dotToken;
   }
   else if(currentChar == ','){
        std::string comma = ",";
        Token commaToken = createToken(TokenType::COMMA, comma);
        writeToken(commaToken);
        currentChar = nextChar();
        return commaToken;
   }
   else if(currentChar == ':'){
        char nextc = nextChar();
        if(nextc == '='){
            std::string assignop = ":=";
            Token assToken = createToken(TokenType::ASSIGN, assignop);
            writeToken(assToken);
            return assToken;
        }
        else{
            std::string colon = ":";
            Token colonToken = createToken(TokenType::COLON, colon);
            writeToken(colonToken);
            return colonToken;
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
Token Lexer::createToken(TokenType type, std::string& lexeme){
    return Token(type, lexeme, line);
}

void Lexer::writeError(const Token& errToken){
    if(outLexErrors){
        *outLexErrors<<"Lexecial Error: "<<errToken.getLine()<<":"<<errToken.getType()<<"\n";
    }


}

void Lexer::writeToken(const Token& token){
    if(outLexTokens){
        std::cout<<"["<<token.getType()<<", "<<token.getLexeme()<<", "<<token.getLine()<<"]";
        *outLexTokens<<"["<<token.getType()<<", "<<token.getLexeme()<<", "<<token.getLine()<<"]\n";
    }

}