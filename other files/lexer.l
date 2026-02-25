%option lexer = "SampleLexer"
%option lex = "nextToken"
%option token-type = "int"
%option outfile = "Lexer.cpp"

%top{
    #include "Parser.hpp"
}

%%
\+                      return Expr::Parser::token::OP_PLUS;
\*                      return Expr::Parser::token::OP_MULT;
\(                      return Expr::Parser::token::OPEN_PAR;
\)                      return Expr::Parser::token::CLOSE_PAR;
[a-zA-Z_][a-zA-Z0-9_]*  return Expr::Parser::token::ASCII_IDENTIFIER;
[0-9]+                  return Expr::Parser::token::CONST_NUMBER;
\"([^\\"]|\\.)*\"       return Expr::Parser::token::CONST_STRING;
[ \t\r\n]+              /* ignore whitespace */

<<EOF>>                 return Expr::Parser::token::END_OF_FILE;

.                       { 
                            std::cerr << "Unexpected character: " << text() << "\n"; 
                            return -1; 
                        }
%%