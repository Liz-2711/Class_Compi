%language "C++" // para mencionar 
%require "3.2" //hacer que sea compatible con 3.2 en adelante. 
%token OP_PLUS OP_MULT 
%token OPEN_PAR CLOSE_PAR 
%token NUMBER

%{
#include <string>
#include "Parser.hpp"

int yylex (int *val);

namespace yy
{
	void parser::error (const std::string & msg)
{
throw parser::syntax_error(msg);
}
}
%}

%% 
expr: expr OP_PLUS term {/*acción al hacer reduce */}
| term {/*c++ code */} // otra forma es:  | term {/*/}
; 

term: term OP_MULT factor
	| factor 
;
factor : OPEN_PAR expr CLOSE_PAR
	| NUMBER

%%