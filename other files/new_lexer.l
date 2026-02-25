%option lexer = "SampleLexer"
%option lex = "nextToken"
%option bison-cc
%option bison-cc-namespace = "Expr"
%option bison-cc-parser = "Parser"

%{
#include <string>
#include "Parser.hpp"
%}

%top{
#include <string>
#include "Parser.hpp"
namespace Expr { class Parser; }
}



%%

[0-9]+                  {std::cout << "Numero: " << str() << std::endl; yylval = std::stoi(str()); return Expr::Parser::token::NUMBER;};
"+"                     {str(); return Expr::Parser::token::OP_PLUS;}
"*"                     { return Expr::Parser::token::OP_MULT;}
"("                     { return Expr::Parser::token::OPEN_PAR;}
")"                     { return Expr::Parser::token::CLOSE_PAR;}
%%
