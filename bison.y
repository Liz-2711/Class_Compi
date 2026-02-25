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

%code requires{
    #include <string>
    #include <unordered_map>  
    class SampleLexer;
}

%code {
    #include "Lexer.hpp"
    #include <iostream>
    
    // Tabla de variables global usando unordered_map
    std::unordered_map<std::string, int> vars;  
    
    namespace Expr {
        int yylex(Parser::semantic_type* yylval, SampleLexer& lexer) {
            return lexer.nextToken(yylval);
        }
        
        void Parser::error(const std::string& msg) {
            std::cerr << "Error de parsing: " << msg << std::endl;
        }
    }
    
    #define yylex(yylval) Expr::yylex(yylval, lexer)
}

%%

input: expr { 
    std::cout << "Resultado: " << $1 << std::endl; 
    $$ = $1; 
}
;

expr: expr OP_PLUS term { 
    std::cout << "Evaluando: " << $1 << " + " << $3 << std::endl;
    $$ = $1 + $3; 
}
| term { 
    $$ = $1; 
}
;

term: term OP_MULT factor { 
    std::cout << "Evaluando: " << $1 << " * " << $3 << std::endl;
    $$ = $1 * $3; 
}
| factor { 
    $$ = $1; 
}
;

factor: OPEN_PAR expr CLOSE_PAR { 
    $$ = $2; 
}
| NUMBER { 
    $$ = std::stoi(lexer.str()); 
}
| IDENTIFIER {
    std::string var = lexer.str();
    auto it = vars.find(var);
    if(it == vars.end()){
        std::cerr << "Error: Variable '" << var << "' no definida" << std::endl;
        throw std::runtime_error("Variable no encontrada: " + var);
    }
    std::cout << "Usando variable '" << var << "' = " << it->second << std::endl;
    $$ = it->second;
}
;

%%