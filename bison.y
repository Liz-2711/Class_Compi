
%language "c++"
%require "3.2"



%token OP_MULT
%token OP_PLUS
%token OPEN_PAR
%token CLOSE_PAR
%token NUMBER



%{
    
    #include <string>
    #include "Parser.hpp"

using token = yy::parser::token;
std::vector<int> tokens= 
token::NUMBER, token::OP_PLUS, token::NUMBER

    int yylex(int *val);


    namspace yy{

        void parser::error(const std::string& msg)
        {
            throw parser::syntax_error(msg)
        }
    }

    %}
%%

expr: expr  OP_PLUS term {}// al hacer un reduce, se hace lo de brackets//significa que estos estan en el stack
// si tiene simbolos asociados, se puede calcular el atributo en base al pop
//cada atributo va a tener bullpointer
//se sacan los 3 atributos 

    |term {/*c++ code */} //se ejecuta la acction 
    ;


    //cada accion retorna un nodo 
    term: term OP_MULT factor 
    |factor 
    ;

    factor: OPEN_PAR expr CLOSE_PAR
        |NUMBER
        ;

/*no se debe escribir el propio enum, hay que usar el enum de bision */
   


    

%%