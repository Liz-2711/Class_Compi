
cmake_minimum_required(VERSION 3.10)
project(lexer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Reflex REQUIRED)

message(STATUS "Source Dir:${CMAKE_SOURCE_DIR}")
message(STATUS "Source Dir:${CMAKE_BINARY_DIR}")
set(LEXER_INPUT_SOURCE ${CMAKE_SOURCE_DIR}/lexer.l)
set(LEXER_CPP_SOURCE ${CMAKE_BINARY_DIR}/Lexer.cpp)
set(LEXER_CPP_HEADER ${CMAKE_BINARY_DIR}/Lexer.hpp)

add_custom_command (
    OUTPUT ${LEXER_CPP_HEADER} ${LEXER_CPP_SOURCE}
    COMMAND Reflex::Reflex
            -o ${LEXER_CPP_SOURCE}
            --header-file=${LEXER_CPP_HEADER}
            ${LEXER_INPUT_SOURCE}
    DEPENDS ${LEXER_INPUT_SOURCE}
    #DEPENDS ${LEXER_SOURCE_FILE} #ES PARA UN FILEmientra que input es para stdin
    
    )
    
   add_executable(${PROJECT_NAME} main.cpp ${LEXER_CPP_SOURCE})
   target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})
  target_link_libraries(${PROJECT_NAME} PRIVATE Reflex::ReflexLibStatic)
