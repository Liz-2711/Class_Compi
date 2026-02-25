#include <iostream>
#include "Lexer.hpp"
#include "tokens.hpp"
#include <fstream>

int main(int argc,char* argv[]){

   if(argc!=2 ){
      std::cerr <<"USAGE: "<< argv[0]<< "<input_file>\n";
      return 1;
   }

   std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file " << argv[1] << "\n";
        return 1; 
    }

    std::cout<<"start\n";
   SampleLexer lexer(inputFile);

   
    Tokens token = lexer.nextToken();
   // agregar while 
   
 while (token != Tokens::END_OF_FILE) {

    std::cout<< "Token detectado: ";
   switch (token){
   case  Tokens::ASCII_IDENTIFIER: std::cout << "asci_odentifier\n"; break;
    case Tokens::CONST_NUMBER: std::cout << "const_NUMBER \n" ;break;
    case Tokens::CONST_STRING: std::cout << "const_STRING\n" ;break;
   

    default: std::cout << "DESCONOCIDO\n"; break;
}

std::cout << "Text: " << lexer.text() << "\n";
token = lexer.nextToken(); 
}
   
   return 0;


}
//mientras este como input de terminal se tiene que colocar ctrl+D para fin de linea 