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

        static Token end_token() {return Token(TokenType::END);}
        Token(TokenType _tt, std::string _sym):
            tt(_tt), sym(_sym)
        {}
        explicit Token(TokenType _tt):
            tt(_tt), sym("")
        {}
    };
}
