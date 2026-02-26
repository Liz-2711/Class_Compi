#include <iostream>
#include <fstream>
#include <unordered_map>  
#include "Lexer.hpp"
#include "Parser.hpp"
#include "tree.hpp"

// Variable externa definida en parser.y
extern std::unordered_map<std::string, int> vars; 
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "USAGE: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file " << argv[1] << "\n";
        return 1;
    }


    
    // Inicializar variables predefinidas
    vars["x"] = 10;
    vars["y"] = 20;
    vars["z"] = 5;
    std::cout << "Variables definidas:\n";
    for (const auto& pair : vars) {
        std::cout << "  " << pair.first << " = " << pair.second << "\n";
    }
    std::cout << "\n";
    
    SampleLexer lexer(inputFile);
    ExprParser::Parser parser(lexer);
    
    try {
        int result = parser.parse();
        if (result == 0) {
            std::cout << "\n Parsing successful\n";
        } else {
            std::cout << "\n Parsing failed\n";
        }
    } catch (const ExprParser::Parser::syntax_error& e) {
        std::cerr << "\n Syntax error: " << e.what() << "\n";
        return 1;
    }
    
    inputFile.close();
    return 0;
}
   