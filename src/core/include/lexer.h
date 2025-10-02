#pragma once

#include <string>
#include <vector>
#include <defs.h>

class Lexer
{
private:
    std::string input;
    std::vector<Token> tokens;

public:
    std::vector<Token> tokenize(const std::string&);

public:
    Lexer() = default;
    ~Lexer() = default;
};
