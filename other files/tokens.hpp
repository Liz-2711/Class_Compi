#pragma once

enum class Tokens {
    OP_PLUS,
    OP_MULT,
    OPEN_PAR,
    CLOSE_PAR,

    ASCII_IDENTIFIER,
    CONST_NUMBER,
    CONST_STRING,

    END_OF_FILE
};
