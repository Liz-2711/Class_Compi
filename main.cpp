#include <iostream>
#include <fstream>
#include <unordered_map>  
#include "Lexer.hpp"
#include "Parser.hpp"

// Variable externa definida en parser.y
extern std::unordered_map<std::string, int> vars; 

void testLexerOnly(const char* filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file " << filename << "\n";
        return;
    }

    std::cout << "=== Lexer Test Mode ===\n\n";
    
    SampleLexer lexer(inputFile);
    Expr::Parser::semantic_type yylval;
    int token = lexer.nextToken(&yylval);

    // while (token != 0) {
    //     std::cout << "Token detectado: ";
        
    //     switch (token) {
    //         case Expr::Parser::token::NUMBER:
    //             std::cout << "NUMBER";
    //             break;
    //         case Expr::Parser::token::IDENTIFIER:
    //             std::cout << "IDENTIFIER";
    //             break;
    //         case Expr::Parser::token::OP_PLUS:
    //             std::cout << "OP_PLUS (+)";
    //             break;
    //         case Expr::Parser::token::OP_MULT:
    //             std::cout << "OP_MULT (*)";
    //             break;
    //         case Expr::Parser::token::OPEN_PAR:
    //             std::cout << "OPEN_PAR (()";
    //             break;
    //         case Expr::Parser::token::CLOSE_PAR:
    //             std::cout << "CLOSE_PAR ())";
    //             break;
    //         default:
    //             std::cout << "UNKNOWN (" << token << ")";
    //             break;
    //     }
        
    //     std::cout << " | Text: \"" << lexer.str() << "\"\n";
    //     token = lexer.nextToken(&yylval);
    // }
    
    std::cout << "\n✓ Lexer finished\n";
    inputFile.close();
}

void testParser(const char* filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file " << filename << "\n";
        return;
    }

    std::cout << "=== Parser Mode ===\n\n";

    // Inicializar variables en el unordered_map
    vars["x"] = 10;
    vars["y"] = 20;
    vars["z"] = 5;

    
    std::cout << "Variables definidas:\n";
    for (const auto& pair : vars) {
        std::cout << "  " << pair.first << " = " << pair.second << "\n";
    }
    std::cout << "\n";

    SampleLexer lexer(inputFile);
    Expr::Parser parser(lexer);

    try {
        int result = parser.parse();
        
        if (result == 0) {
            std::cout << "\n✓ Parsing successful\n";
        } else {
            std::cout << "\n✗ Parsing failed with code: " << result << "\n";
        }
    } catch (const Expr::Parser::syntax_error& e) {
        std::cerr << "\n✗ Syntax error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "\n✗ Error: " << e.what() << "\n";
    }

    inputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "USAGE: " << argv[0] << " <input_file> [-l]\n";
        std::cerr << "  -l : Lexer only mode (show tokens)\n";
        return 1;
    }

    // Modo lexer solo
    if (argc == 3 && std::string(argv[2]) == "-l") {
        testLexerOnly(argv[1]);
        return 0;
    }

    // Modo parser normal
    testParser(argv[1]);
    return 0;
}