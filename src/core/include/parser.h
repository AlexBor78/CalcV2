#pragma once

#include <memory>
#include <string>
#include <lexer.h>
#include <ast.h>

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

private:
    Token curr();
    Token peak(int);
    Token next(int);

    std::unique_ptr<Expr> parse_prim();
    std::unique_ptr<Expr> parse_expr();
    std::unique_ptr<Expr> parse_term();

};
