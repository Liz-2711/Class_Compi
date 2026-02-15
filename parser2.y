%language "C++"
%require "3.2"

/* Definir tokens */
%token OP_PLUS "+"
%token OP_MULT "*"
%token OPEN_PAR "("
%token CLOSE_PAR ")"
%token ASCII_IDENTIFIER "identifier"
%token CONST_NUMBER "number"
%token CONST_STRING "string"
%token END_OF_FILE 0 "end of file"

%define parse.error verbose
%define api.namespace {Expr}
%define api.parser.class {Parser}
//%define api.token.prefix {TOK_}

/* Parámetro para el lexer */
%parse-param {SampleLexer& lexer}

%code requires {
    // Forward declaration solamente
    class SampleLexer;
}

%code {
    #include "Lexer.hpp"
    #include <iostream>
    
    namespace Expr {
        int yylex(Expr::Parser::semantic_type* yylval, SampleLexer& lexer) {
            return lexer.nextToken();
        }
    }
    
    #define yylex(yylval) yylex(yylval, lexer)
}

%%

start: expr END_OF_FILE { std::cout << "Parsing completed successfully!\n"; }
;

expr: expr OP_PLUS term { std::cout << "expr + term\n"; }
    | term { std::cout << "term\n"; }
;

term: term OP_MULT factor { std::cout << "term * factor\n"; }
    | factor { std::cout << "factor\n"; }
;

factor: OPEN_PAR expr CLOSE_PAR { std::cout << "(expr)\n"; }
      | CONST_NUMBER { std::cout << "number: " << lexer.text() << "\n"; }
      | ASCII_IDENTIFIER { std::cout << "identifier: " << lexer.text() << "\n"; }
      | CONST_STRING { std::cout << "string: " << lexer.text() << "\n"; }
;

%%

namespace Expr {
    void Parser::error(const std::string& msg) {
        std::cerr << "Parse error: " << msg << "\n";
    }
}