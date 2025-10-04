#pragma once

#include <cstdint>
#include <string>

namespace Calc::types
{
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
        std::string sym;
    };

    enum class OpCode : uint8_t
    {
        PUSH,
        ADD,
        SUB,
        MUL,
        DIV,
        INVERSE
    };

    struct Instruction
    {
        OpCode op;
        int operand;
    };
}
