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

Token Parser::curr()
{
    if(pos < tokens.size())
    {
        return tokens[pos];
    }
    return {TokenType::END};
}
Token Parser::peak(int offset=1)
{
    if(pos + offset < tokens.size())
    {
        return tokens[pos + offset];
    }
    return {TokenType::END};
}
Token Parser::next(int offset=1)
{
    pos+=offset;
    if(pos < tokens.size())
    {
        return tokens[pos];
    }
    return {TokenType::END};
}

std::unique_ptr<Expr> Parser::parse_prim()
{
    if(curr().tt == TokenType::NUMBER)
    {
        auto tok = curr();
        next();
        return std::make_unique<Number>(std::stoi(tok.sym));
    }
    if(curr().tt == TokenType::LEFT_BRACKET)
    {
        next(); // skip bracket
        auto prim = parse_expr();
        if(curr().tt != TokenType::RIGHT_BRACKET)
        {
            std::cerr << "missing )" << std::endl;
            return std::move(prim);
        }
        next();
        return std::move(prim);
    }
    // unary
    if((curr().tt == TokenType::PLUS || curr().tt == TokenType::MINUS)
        && (peak().tt == TokenType::NUMBER || peak().tt == TokenType::LEFT_BRACKET)
    ) {
        if(curr().tt == TokenType::MINUS)
        {
            next();
            return std::make_unique<UnaryOp>(UnaryOp::Kind::MINUS, parse_prim());
        }
    }

    std::cerr << "bad prim" << std::endl;
    throw std::runtime_error("bad primary");
    return nullptr;
}

std::unique_ptr<Expr> Parser::parse_expr()
{
    auto left = parse_term();
    while(curr().tt != TokenType::END)
    {
        auto op = curr();
        switch (op.tt)
        {
            case(TokenType::PLUS):
                next();
                left = std::make_unique<BinOp>(
                    BinOp::Kind::PLUS, std::move(left), parse_term()
                ); break;

            case(TokenType::MINUS):
                next();
                left = std::make_unique<BinOp>(
                    BinOp::Kind::MINUS, std::move(left), parse_term()
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
    while(curr().tt != TokenType::END)
    {
        auto op = curr();
        switch (op.tt)
        {
            case(TokenType::MUL):
                next();
                left = std::make_unique<BinOp>(
                    BinOp::Kind::MUL, std::move(left), parse_prim()
                ); break;

            case(TokenType::DIV):
                next();
                left = std::make_unique<BinOp>(
                    BinOp::Kind::DIV, std::move(left), parse_prim()
                ); break;

            default:
                return std::move(left);
        }
    }
    return std::move(left);
}
