cmake_minimum_required(VERSION 3.15)
project(ExprAst)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# 2. Buscar herramientas
# ------------------------------

# Bison
find_package(BISON REQUIRED)

# TreeCC
find_program(TREECC_EXECUTABLE treecc)
if(NOT TREECC_EXECUTABLE)
    message(FATAL_ERROR "No se encontró el ejecutable 'treecc'. Asegúrate de que está instalado y en el PATH.")
endif()
message(STATUS "TreeCC found: ${TREECC_EXECUTABLE}")

# Re/flex
find_program(REFLEX_EXECUTABLE reflex)
if(NOT REFLEX_EXECUTABLE)
    message(FATAL_ERROR "No se encontró el ejecutable 'reflex'. Asegúrate de que está instalado y en el PATH.")
endif()
message(STATUS "Re/flex found: ${REFLEX_EXECUTABLE}")

# Librería de Re/flex
find_library(REFLEX_LIBRARY
    NAMES reflex libreflex
    PATHS /usr/local/lib /usr/lib
)
if(NOT REFLEX_LIBRARY)
    message(FATAL_ERROR "No se encontró la librería de Re/flex")
endif()
message(STATUS "Re/flex library: ${REFLEX_LIBRARY}")

# ------------------------------
# 3. Archivos de entrada y salida
# ------------------------------
set(LEXER_INPUT   ${CMAKE_SOURCE_DIR}/lexer.l)
set(PARSER_INPUT  ${CMAKE_SOURCE_DIR}/bison.y)
set(TREE_INPUT    ${CMAKE_SOURCE_DIR}/tree.tc)

set(LEXER_CPP     ${CMAKE_BINARY_DIR}/Lexer.cpp)
set(LEXER_HPP     ${CMAKE_BINARY_DIR}/Lexer.hpp)

set(PARSER_CPP    ${CMAKE_BINARY_DIR}/Parser.cpp)
set(PARSER_HPP    ${CMAKE_BINARY_DIR}/Parser.hpp)

set(TREECC_CPP    ${CMAKE_BINARY_DIR}/tree.cpp)
set(TREECC_HPP    ${CMAKE_BINARY_DIR}/tree.hpp)

# ------------------------------
# 4. Generación de código
# ------------------------------

# --- Lexer (Re/flex) ---
add_custom_command(
    OUTPUT ${LEXER_CPP} ${LEXER_HPP}
    COMMAND ${REFLEX_EXECUTABLE}
            --bison
            --header-file=${LEXER_HPP}
            --outfile=${LEXER_CPP}
            ${LEXER_INPUT}
    DEPENDS ${LEXER_INPUT}
    COMMENT "Generating Lexer with Re/flex for Bison"
)

# --- Parser (Bison) ---
add_custom_command(
    OUTPUT ${PARSER_CPP} ${PARSER_HPP}
    COMMAND ${BISON_EXECUTABLE}
            -d
            -o ${PARSER_CPP}
            ${PARSER_INPUT}
    DEPENDS ${PARSER_INPUT}
    COMMENT "Generating Parser with Bison"
)

# --- TreeCC (AST) ---
add_custom_command(
    OUTPUT ${TREECC_CPP} ${TREECC_HPP}
    COMMAND ${TREECC_EXECUTABLE}
            -o ${TREECC_CPP}
            -h ${TREECC_HPP}
            ${TREE_INPUT}
    DEPENDS ${TREE_INPUT}
    COMMENT "Generating AST with TreeCC"
)

# ------------------------------
# 5. Crear ejecutable
# ------------------------------
add_executable(${PROJECT_NAME}
    main.cpp
    ${LEXER_CPP}
    ${PARSER_CPP}
    ${TREECC_CPP}
)

# ------------------------------
# 6. Incluir directorios
# ------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}   # tus headers originales
    ${CMAKE_BINARY_DIR}   # headers generados por Re/flex, Bison y TreeCC
)

# ------------------------------
# 7. Link con librerías
# ------------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE ${REFLEX_LIBRARY})