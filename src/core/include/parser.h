#pragma once

#include "defs.h"
#include <cstddef>
#include <lexer.h>
#include <ast.h>
#include <memory>
#include <pthread.h>
#include <string>

class Parser
{
private:
    Lexer lexer;
    std::vector<Token> tokens;
    size_t pos{0};
    
public:
    Parser() = default;
    ~Parser() = default;

public:

    std::unique_ptr<Expr> parse(const std::string&);

public:
    inline Token next()
    {
        if(pos < tokens.size())
        {
            pos++;
            return tokens[pos-1];
        }
        return {TokenType::END};
    }
    inline Token peak()
    {
        if(pos < tokens.size())
        {
            return tokens[pos];
        }
        return {TokenType::END};
    }

private:

    std::unique_ptr<Expr> parse_prim();
    std::unique_ptr<Expr> parse_expr();
    std::unique_ptr<Expr> parse_term();



};