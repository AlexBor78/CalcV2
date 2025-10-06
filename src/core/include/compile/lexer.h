#pragma once

#include <string>
#include <vector>
#include <compile/defs.h>

namespace Calc
{
    class Lexer
    {
    private:
        std::string input;
        std::vector<types::Token> tokens;
        size_t pos{0};

    private:
        char curr() const noexcept;
        char peak(int) const noexcept;
        char next(int) noexcept;

        bool is_punct() noexcept;
        bool is_num() noexcept;

        void skip_spaces() noexcept;
        void tokenize_number();
        void tokenize_punct() noexcept;

        void add_token(types::Token) noexcept;
        void add_token(types::TokenType) noexcept;
        void add_token(types::TokenType, const char) noexcept;
        void add_token(types::TokenType, const char*) noexcept;

    public:
        std::vector<types::Token> tokenize(const std::string&);
    };
}
