#pragma once

#include <string>
#include <vector>
#include <defs.h>

class Lexer
{
private:
    std::string input;
    std::vector<Token> tokens;
    size_t pos{0};

private:
    char curr();
    char peak(int);
    char next(int);

    bool is_punct();

    void skip_spaces();
    void tokenize_number();
    void tokenize_punct();

    void add_token(Token);
    void add_token(TokenType);
    void add_token(TokenType, const char);
    void add_token(TokenType, const char*);


public:
    std::vector<Token> tokenize(const std::string&);

public:
    Lexer() = default;
    ~Lexer() = default;
};
