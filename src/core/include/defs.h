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

enum class OpCode : uint8_t
{
    PUSH,
    ADD,
    SUB,
    MUL,
    DIV
};

struct Instruction
{
    OpCode op;
    int operand;
};
