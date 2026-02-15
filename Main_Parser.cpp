#include <iostream>
#include <fstream>
#include "Parser.hpp"
#include "Lexer.hpp"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "USAGE: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file " << argv[1] << "\n";
        return 1; 
    }

    std::cout << "Starting parser...\n";
    
    SampleLexer lexer(inputFile);
    Expr::Parser parser(lexer);
    
    try {
        int result = parser.parse();
        if (result == 0) {
            std::cout << "Parsing successful!\n";
        } else {
            std::cout << "Parsing failed with code: " << result << "\n";
        }
    } catch (const Expr::Parser::syntax_error& e) {
        std::cerr << "Syntax error: " << e.what() << "\n";
        return 1;
    }
    
    inputFile.close();
    return 0;
}