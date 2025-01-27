#include <iostream>
#include <fstream>
#include "lexer.h"

std::string changeExtension(const std::string& filename, const std::string& newExtension) {
    size_t pos = filename.rfind('.');
    if (pos != std::string::npos) {
        return filename.substr(0, pos) + newExtension;
    }
    return filename + newExtension;  // Default to adding the new extension if no dot is found
}

int main(int argc, char* argv[]){
    
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " sourcefile" << std::endl;
        return 1;
    }
    
    const std::string sourceFile = argv[1];

    // Check if the input file has the correct .src extension
    if (sourceFile.substr(sourceFile.find_last_of(".") + 1) != "src") {
        std::cerr << "Input file must have a .src extension" << std::endl;
        return 1;
    }

    // Construct output file names based on the input file name
    const std::string outputTokenFile = changeExtension(sourceFile, ".outlextokens");
    const std::string outputErrorFile = changeExtension(sourceFile, ".outlexerrors");

    std::ifstream inputStream(sourceFile);
    std::ofstream outputToken(outputTokenFile);
    std::ofstream outputError(outputErrorFile);

    if(!inputStream.is_open()){
        std::cerr<<"Unable to open input file\n";
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
    Lexer lexicalAnalyzer;
    lexicalAnalyzer.setSource(&inputStream);
    lexicalAnalyzer.setOutputFile(&outputToken);
    lexicalAnalyzer.setErrorFile(&outputError);

    Token token = lexicalAnalyzer.nextToken();

    while(token.getType() != TokenType::ENDOFILE){
        // Get the next token
        token = lexicalAnalyzer.nextToken();
    }

    inputStream.close();
    outputError.close();
    outputToken.close();

    return 0;
    
}



