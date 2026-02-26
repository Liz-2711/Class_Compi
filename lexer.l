%option lexer = "SampleLexer"
%option lex = "nextToken"
%option bison-cc
%option bison-cc-namespace = "ExprParser"
%option bison-cc-parser = "Parser"

%top{
#include <string>
#include <iostream>
#include "Parser.hpp"
}

%%

[0-9]+                  { 
    yylval.emplace<long>(std::stol(str()));
    std::cout << "Número detectado: " << str() << std::endl; 
    return ExprParser::Parser::token::NUMBER; 
}

[a-zA-Z_][a-zA-Z0-9_]*  { 
    yylval.emplace<std::string>(str());
    std::cout << "Identificador detectado: " << str() << std::endl; 
    return ExprParser::Parser::token::IDENTIFIER; 
}

"+"                     { return ExprParser::Parser::token::OP_PLUS; }
"-"                     { return ExprParser::Parser::token::OP_MINUS; }
"*"                     { return ExprParser::Parser::token::OP_MULT; }
"/"                     { return ExprParser::Parser::token::OP_DIV; }
"%"                     { return ExprParser::Parser::token::OP_MOD; }
"("                     { return ExprParser::Parser::token::OPEN_PAR; }
")"                     { return ExprParser::Parser::token::CLOSE_PAR; }
[ \t\n\r]+              { /* ignorar espacios */ }

.                       { 
    std::cerr << "Carácter no reconocido: " << str() << std::endl; 
    return -1; 
}

%%