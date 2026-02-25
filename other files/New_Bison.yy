%language "C++"
%require "3.2"

%token OP_PLUS "+"
%token OP_MULT "*"
%token OPEN_PAR "("
%token CLOSE_PAR ")"
%token<int> NUMBER "number"
%token<std::string> IDENTIFIER "identifier"

%define parse.error verbose
%define api.namespace {Expr}
%define api.parser.class {Parser}
%define api.value.type variant
%type<int> input expr term factor

%parse-param {SampleLexer& lexer}
%parse-param {Parser& parser}

%{
    #include <string>
    #include "Parser.hpp"
    #include "Lexer.hpp"
    int yylex(int *val);
    namespace Expr
    {
        void Parser::error(const std::string& msg)
        {
            throw syntax_error(msg);
        }
    }

    #define yylex(p) lexer.nextToken(p)
%} //PARA ARCHIVO cpp del parser

%code requires{
    #include <string>
    class SampleLexer;
} //Para mandar al hpp del Parser

%%

input: expr { std::cout << "Value: "<< $1 <<'\n'; }

expr: expr OP_PLUS term { $$ = $1 + $3; }
	| term { $$ = $1; }
;

term: term OP_MULT factor { $$ = $1 * $3; }
	| factor { $$ = $1; }
;

factor: OPEN_PAR expr CLOSE_PAR { $$ = $2; }
	| NUMBER { $$ = $1; } //Hace referencia al semantic-value del simbolo
    | IDENTIFIER {
        std::string var = $1;
        auto it = vars.find(var);
        if(it == vars.end()){
            throw std::runtime_error("No se encontro la variable");
        };
        $$ = it->second;
        }
;

%%