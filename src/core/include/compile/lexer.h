#pragma once

#include <string>
#include <vector>
#include <defs.h>

namespace Calc
{
    class Lexer
    {
    private:
        std::string input;
        std::vector<types::Token> tokens;
        size_t pos{0};

    private:
        char curr();
        char peak(int);
        char next(int);

        bool is_punct();

        void skip_spaces();
        void tokenize_number();
        void tokenize_punct();

        void add_token(types::Token);
        void add_token(types::TokenType);
        void add_token(types::TokenType, const char);
        void add_token(types::TokenType, const char*);


    public:
        std::vector<types::Token> tokenize(const std::string&);

    public:
        Lexer() = default;
        ~Lexer() = default;
    };
}
