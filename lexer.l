// para llamar a la clase SampleLexer en ves de Lexer 
%option lexer = "SampleLexer"
//metodo nextToken envez de lex()
%option lex = "nextToken"
// sirve para que se pueda usar definir el tipo de retorno como Tokens con un enum class
%option token-type = "Tokens"

//esto va al cpp
/*%{
#include "tokens.hpp"
%}*/
 // esto aparce en el hpp
%top{
    #include "tokens.hpp"
}

%class {
    // aqui podemos agregarle mas metodos a lexer, por defecto son private 
public:
  //  std::string tokenText; // este es un ejemplo, no hace nada 
}
%%
[a-zA-Z_][a-zA-Z0-9_]*  return Tokens::ASCII_IDENTIFIER;
[0-9]+                  return Tokens::CONST_NUMBER;
\"([^\\"]|\\\")*\"      return Tokens::CONST_STRING;
[ \t\r\n]+ /* no action: ignore all white space */
<<EOF>>                 return Tokens::END_OF_FILE;// cuando usemos bison si se definira como 0 
%%