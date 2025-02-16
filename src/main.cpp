#include <iostream>
#include <fstream>
#include "Lexer/lexer.h"
#include "Parser/parser.h"
#include "Lexer/Token.h"

std::string changeExtension(const std::string& filename, const std::string& newExtension){
    size_t pos = filename.rfind('.');
    if(pos != std::string::npos){
        return filename.substr(0, pos) + newExtension;
    }
    return filename + newExtension;
}

int main(int argc, char* argv []){
    if(argc < 2){
        std::cerr << "Usage: "<<argv[0]<<" sourcefile"<<std::endl;
        return 1;
    }
    const std::string sourceFile = argv[1];

     // Check if the input file has the correct .src extension
    if (sourceFile.substr(sourceFile.find_last_of(".") + 1) != "src") {
        std::cout << argv[1] << std::endl;
        std::cerr << "Input file must have a .src extension" << std::endl;

        return 1;
    }

    const std::string outDerivationFile = changeExtension(sourceFile, ".outderivation");
    const std::string syntaxErrorsFile = changeExtension(sourceFile, ".syntaxerrors");
    const std::string outputTokenFile = changeExtension(sourceFile, ".outlextokens");
    const std::string outputErrorFile = changeExtension(sourceFile, ".outlexerrors");

    std::ifstream inputStream(sourceFile);
    std::ofstream outDerivation(outDerivationFile);
    std::ofstream syntaxErrors(syntaxErrorsFile);
    std::ofstream outputToken(outputTokenFile);
    std::ofstream outputError(outputErrorFile);

    if(!inputStream.is_open()){
        std::cout << argv[1] << std::endl;
        std::cerr<<"Unable to open input file \n";
        return 1;
    }
    if(!outDerivation.is_open()){
        std::cerr<<"Unable to open outderivation file \n";
        return 1;
    }
    if(!syntaxErrors.is_open()){
        std::cerr<<"Unable to open syntax error file \n";
        return 1;
    }
     if(!outputToken.is_open()){
        std::cerr<<"Unable to open token output file\n";
        return 1;
    }
    if(!outputError.is_open()){
        std::cerr<<"Unable to Error token output file\n";
        return 1;
    }
    Lexer lexicalAnaylzer;
    lexicalAnaylzer.setSource(&inputStream);
    lexicalAnaylzer.setOutputFile(&outputToken);
    lexicalAnaylzer.setErrorFile(&outputError);

    Parser *p = new Parser(inputStream, outDerivation, syntaxErrors, lexicalAnaylzer);
    std::cout<<"starting the parser "<<std::endl;
    p->startParse();
    
    

}
