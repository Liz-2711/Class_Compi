%language "C++"
%require "3.2"

%token OP_PLUS "+"
%token OP_MULT "*"
%token OP_MINUS "-"
%token OP_DIV "/"
%token OP_MOD "%"
%token OPEN_PAR "("
%token CLOSE_PAR ")"
%token<long> NUMBER "number"

%token<std::string> IDENTIFIER "identifier"

%define parse.error verbose
//Cambiar el nombre de namespace porque luego en treeCC 
//Se usa Expr 
//define api.namespace {Expr}
%define api.namespace {ExprParser}

%define api.parser.class {Parser}
%define api.value.type variant



//Se cambia el type
%nterm <AstNode*>  input expr term factor


%parse-param {SampleLexer& lexer}

%code requires{
    #include <string>
    #include <unordered_map>  
    #include "tree.h"
    class SampleLexer;
}

%code {
    #include "Lexer.hpp"
    #include <iostream>
    
    // Tabla de variables global usando unordered_map
    std::unordered_map<std::string, int> vars;  
    
    namespace ExprParser {
        int yylex(Parser::semantic_type* yylval, SampleLexer& lexer) {
            return lexer.nextToken(yylval);
        }
        
        void Parser::error(const std::string& msg) {
            std::cerr << "Error de parsing: " << msg << std::endl;
        }
    }
    
    #define yylex(yylval) ExprParser::yylex(yylval, lexer)
}

%%

input: expr { 
    std::cout << "Resultado: " << $1 << std::endl; 
    $$ = $1; 
}
;
expr
  : expr OP_PLUS term { $$ = new AddExpr($1, $3); }
  | term              { $$ = $1; }
  ;

term
  : term OP_MULT factor { $$ = new MulExpr($1, $3); }
  | factor              { $$ = $1; }
  ;

factor
  : NUMBER      { $$ = new NumberExpr($1); }
  | IDENTIFIER  { $$ = new IdentifierExpr($1); }
  | OPEN_PAR expr CLOSE_PAR { $$ = $2; }
  ;
  

%%