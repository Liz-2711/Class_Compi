#include "Parser.hpp"
#include <iostream>

int main(){

    yy::parser my_parser;


    try{

        my_parser();
    }catch (const yy::parser::syntax_error& err){
        std::cerr<<err.what();
    }
    return 0;


}