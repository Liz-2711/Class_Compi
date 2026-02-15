%option lexer = "SampleLexer"
%option lex = "nextToken"
%option token-type = "Tokens"

%top{
    `
}

%class {
public:
    // aquí puedes agregar métodos públicos si lo necesitas
}

%%
\+                      return Tokens::OP_PLUS;
\*                      return Tokens::OP_MULT;

\(                      return Tokens::OPEN_PAR;
\)                      return Tokens::CLOSE_PAR;

[a-zA-Z_][a-zA-Z0-9_]*  return Tokens::ASCII_IDENTIFIER;
[0-9]+                 return Tokens::CONST_NUMBER;
\"([^\\"]|\\\")*\"     return Tokens::CONST_STRING;

[ \t\r\n]+             /* ignore whitespace */

<<EOF>>                return Tokens::END_OF_FILE;
%%
