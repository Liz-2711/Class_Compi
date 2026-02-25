%option lexer = "SampleLexer"
%option lex = "nextToken"
%option bison-cc
%option bison-cc-namespace = "Expr"
%option bison-cc-parser = "Parser"

%top{
#include <string>
#include <iostream>
#include "Parser.hpp"
}

%%

[0-9]+                  { 
    std::cout << "Número detectado: " << str() << std::endl; 
    return Expr::Parser::token::NUMBER; 
}

[a-zA-Z_][a-zA-Z0-9_]*  { 
    std::cout << "Identificador detectado: " << str() << std::endl; 
    return Expr::Parser::token::IDENTIFIER; 
}

"+"                     { return Expr::Parser::token::OP_PLUS; }
"*"                     { return Expr::Parser::token::OP_MULT; }
"("                     { return Expr::Parser::token::OPEN_PAR; }
")"                     { return Expr::Parser::token::CLOSE_PAR; }

[ \t\n\r]+              { /* ignorar espacios */ }

.                       { 
    std::cerr << "Carácter no reconocido: " << str() << std::endl; 
    return -1; 
}

%%