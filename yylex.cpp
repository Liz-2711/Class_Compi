#include "Parser.hpp"
#include <vector>


using token = yy::parser::token;
std::vector<int> tokens = {
    token::NUMBER, token::OP_PLUS , token::NUMBER
};
auto it = tokens.begin();

int yylex(int *value){
    if(it != tokens.end()){
        return *it++;
        if (it == token::NUMBER) {
            *value = 42; // Give every NUMBER the value 42 for this test
        }
    }
    return 0;
}