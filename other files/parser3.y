%language “C++” // para mencionar 
%require “3.2” //hacer que sea compatible con 3.2 en adelante. 
%token OP_PLUS “ ‘+’ ” //esto es para que al momento que de errores diga el pequeño texto 
%token OP_MULT “*”
%token OPEN_PAR CLOSE_PAR 
%token NUMBER “number”

%define parse.error verbose //describe los errores de sintaxis

%define api.namespace {Expr} //cambia nombre de namespace
%define api.parser.class {Parser} //cambia nombre de clase

%parse-param {Lexer& lexer}// para cambiar el constructor, mas específicamente los parámetros pero también los almacena como debería

%code requires {
//namespace 
class Lexer;

}
%{
#include <string>
#include “Parser.hpp”
#inlcude “Lexer.hpp”

int yylex (int *val);

namespace Expr
{
	void Parser::error (const std::string & msg)
{
throw syntax_error(msg);
}
}

#define yylex(p) lexer.nextToken(p)
%}


%% 
expr: expr OP_PLUS term {/*acción al hacer reduce */} / “+” // otra opción a poner OP_PLUS
expr: term {/*c++ code */} // otra forma es:  | term {/**/}
; 

term: term OP_MULT factor
	| factor 
;
factor : OPEN_PAR expr CLOSE_PAR
	| NUMBER

%%