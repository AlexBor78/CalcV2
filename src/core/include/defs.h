#pragma once

#include <cstdint>

enum class TokenType : uint8_t
{
    PLUS,
    MINUS,
    MUL,
    DIV,
    NUMBER,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    END
};

struct Token
{
    TokenType tt;
    const char sym;
};
