#include "ast.h"
#include "defs.h"
#include "lexer.h"
#include <memory>
#include <parser.h>
#include <stdexcept>
#include <string>
#include <iostream>

std::unique_ptr<Expr> Parser::parse(const std::string& str)
{
    tokens = lexer.tokenize(str);
    return parse_expr();
}

std::unique_ptr<Expr> Parser::parse_prim()
{
    auto tok = peak();
    if(tok.tt == TokenType::NUMBER)
    {
        return std::make_unique<Number>(std::stoi(std::string(1, next().sym)));
    }
    std::cerr << "bad prim" << std::endl;
    throw std::runtime_error("bad primary");
    return nullptr;
}

std::unique_ptr<Expr> Parser::parse_expr()
{
    auto left = parse_term();
    while(peak().tt != TokenType::END)
    {
        auto op = peak();
        switch (op.tt)
        {
            case(TokenType::PLUS):
                next();
                left = std::make_unique<BinOp>(
                    BinOp::BinOpKind::PLUS, std::move(left), parse_term()
                ); break;

            case(TokenType::MINUS):
                next();
                return std::make_unique<BinOp>(
                    BinOp::BinOpKind::MINUS, std::move(left), parse_term()
                ); break;

            default:
                return std::move(left);
        }
    }
    return std::move(left);
}

std::unique_ptr<Expr> Parser::parse_term()
{
    auto left = parse_prim();
    while(peak().tt != TokenType::END)
    {
        auto op = peak();
        switch (op.tt)
        {
            case(TokenType::MUL):
                next();
                left = std::make_unique<BinOp>(
                    BinOp::BinOpKind::MUL, std::move(left), parse_prim()
                ); break;

            case(TokenType::DIV):
                next();
                left = std::make_unique<BinOp>(
                    BinOp::BinOpKind::DIV, std::move(left), parse_prim()
                ); break;

            default:
                return std::move(left);
        }
    }
    return std::move(left);
}
