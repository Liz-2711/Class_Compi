# cmake_minimum_required(VERSION 3.15)
# project(ExprAst)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# find_package(Reflex REQUIRED)
# find_package(BISON REQUIRED)
# find_package(TreeCC REQUIRED)

# message(STATUS "TreeCC found: ${TREECC_EXECUTABLE}")
# message(STATUS "TreeCC version: ${TREECC_VERSION}")

cmake_minimum_required(VERSION 3.15)
project(ExprAst)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Para encontrar FindTreeCC.cmake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})


#Dependencias

find_package(Reflex REQUIRED)
find_package(BISON REQUIRED)
find_package(TreeCC REQUIRED)

message(STATUS "TreeCC found: ${TREECC_EXECUTABLE}")
message(STATUS "TreeCC version: ${TREECC_VERSION}")
message(STATUS "Source Dir: ${CMAKE_SOURCE_DIR}")
message(STATUS "Binary Dir: ${CMAKE_BINARY_DIR}")


# Archivos de entrada

set(LEXER_INPUT ${CMAKE_SOURCE_DIR}/lexer.l)
set(PARSER_INPUT ${CMAKE_SOURCE_DIR}/parser.y)
set(TREE_INPUT   ${CMAKE_SOURCE_DIR}/ast.tree)


# Archivos generados (build)

set(LEXER_CPP    ${CMAKE_BINARY_DIR}/Lexer.cpp)
set(LEXER_HPP    ${CMAKE_BINARY_DIR}/Lexer.hpp)

set(PARSER_CPP   ${CMAKE_BINARY_DIR}/Parser.cpp)
set(PARSER_HPP   ${CMAKE_BINARY_DIR}/Parser.hpp)

set(TREECC_CPP   ${CMAKE_BINARY_DIR}/ast.cpp)
set(TREECC_HPP   ${CMAKE_BINARY_DIR}/ast.hpp)


# Reflex (lexer)

add_custom_command(
    OUTPUT ${LEXER_CPP} ${LEXER_HPP}
    COMMAND Reflex::Reflex
            -o ${LEXER_CPP}
            --header-file=${LEXER_HPP}
            ${LEXER_INPUT}
    DEPENDS ${LEXER_INPUT}
    COMMENT "Generating lexer with Reflex"
)


# Bison (parser)

add_custom_command(
    OUTPUT ${PARSER_CPP} ${PARSER_HPP}
    COMMAND BISON::Bison
            -d
            -o ${PARSER_CPP}
            ${PARSER_INPUT}
    DEPENDS ${PARSER_INPUT}
    COMMENT "Generating parser with Bison"
)


# TreeCC (AST)

add_custom_command(
    OUTPUT ${TREECC_CPP} ${TREECC_HPP}
    COMMAND ${TREECC_EXECUTABLE}
            -o ${TREECC_CPP}
            -h ${TREECC_HPP}
            ${TREE_INPUT}
    DEPENDS ${TREE_INPUT}
    COMMENT "Generating AST with TreeCC"
)


# Ejecutable final

add_executable(${PROJECT_NAME}
    main.cpp
    ${LEXER_CPP}
    ${PARSER_CPP}
    ${TREECC_CPP}
)

# Incluir headers generados
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# Librerías
target_link_libraries(${PROJECT_NAME} PRIVATE
    Reflex::ReflexLibStatic
)
