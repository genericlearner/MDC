#include <iostream>
#include <fstream>
#include "Lexer/lexer.h"
#include "Parser/parser.h"
#include "Lexer/Token.h"
#include "SymbolTableVisitor.h"
#include "AST.h"
#include "TypeCheckingVisitor.h"
#include "CreateTempVariablesVisitor.h"
#include "MoonAssemblyVisitor.h"

#include "AST.h"

std::string changeExtension(const std::string& filename, const std::string& newExtension){
    size_t pos = filename.rfind('.');
    if(pos != std::string::npos){
        return filename.substr(0, pos) + newExtension;
    }
    return filename + newExtension;
}

void writeToDot(AST* ast, std::string path) {
    std::ofstream file(path);
    if (file.fail() || !ast)return;

   

    file << "digraph ASTTree {\n";
    file << ast->dotConvert();
    file << "}\n";

    file.close();
}

void writeSymbolTable(AST* tree, std::string path) {
    AST* ast_node = tree->getChild(0);

    std::ofstream file(path);

    if (file.fail() || !ast_node) { return; };

    file << "strict digraph structs {\n";
    file << "\tnode [shape=plaintext]";
    file << ast_node->getSymbolTable()->toDot();
    file << "}\n";

    file.close();
}

void writeSemanticError(std::vector<std::string>errors, std::string path) {
    std::ofstream file(path);

    if (file.is_open()) {
        for (std::string s : errors) {
            file << s << std::endl;;
        }
        file.close();
    }
    else {
        std::cout << "couldnt open semantic error file" << std::endl;
    }
}

void writeOutMoon(std::vector<std::string>output, std::string path) {
    std::ofstream file(path);

    if (file.fail()) { return; }

    for (std::string str : output) {
        file << str << std::endl;
    }

    file.close();
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
    const std::string outASTFile = changeExtension(sourceFile, ".outast");
    const std::string outSymbolFile = changeExtension(sourceFile, ".outsymbol");

    const std::string outSemanticErrorFile = changeExtension(sourceFile, ".outsemanticerrors");
    const std::string outMoonPath = changeExtension(sourceFile, ".moon");

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
    SymbolTableVisitor* symbolTableVisitor = new SymbolTableVisitor();
    TypeCheckingVisitor* typeCheckerVisitor = new TypeCheckingVisitor();
    CreateTempVariablesVisitor* tempVariableVisitor = new CreateTempVariablesVisitor();
    MoonAssemblyVisitor* moonAssemblyVisitor = new MoonAssemblyVisitor();

    bool parseSuccess = p->startParse();
    
    if (!parseSuccess) {
        std::cout << "Parsing Unsuccessful" << std::endl;
    }
    else {
        std::cout << "Parsing Successful, generating AST tree" << std::endl;
    }
   
    if (parseSuccess) {
        writeToDot(p->getast(), outASTFile);
        std::cout << "Generated AST tree, visit the classes for generating Symbol table and type checking" << std::endl;
        //p->getast()->accept(symbolTableVisitor);
        //p->getast()->accept(typeCheckerVisitor);
        //p->getast()->accept(tempVariableVisitor);
        //writeSymbolTable(p->getast(), outSymbolFile);
        std::vector<std::string> allErrors = symbolTableVisitor->getError();
        std::vector<std::string> typeErrors = typeCheckerVisitor->getError();

        // Append type errors to allErrors
        //allErrors.insert(allErrors.end(), typeErrors.begin(), typeErrors.end());

        // Write once, ensuring no double append
        
        //writeSemanticError(allErrors, outSemanticErrorFile);
        /*
        try {
            p->getast()->accept(moonAssemblyVisitor, false);
        }
        catch (...) {
            std::cout << "Failed to get moon code" << std::endl;
        }
        writeOutMoon(moonAssemblyVisitor->getCode(), outMoonPath);

        std::cout << "Moon Code generation Successful!" << std::endl;
        */
        
    } 
    delete p;
    delete symbolTableVisitor;
    delete typeCheckerVisitor;
    delete tempVariableVisitor;
    delete moonAssemblyVisitor;
    p = nullptr;

    symbolTableVisitor = nullptr;
    typeCheckerVisitor = nullptr;
    tempVariableVisitor = nullptr;
    moonAssemblyVisitor = nullptr;
    

}
