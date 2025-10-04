#include "ast.h"
#include "defs.h"
#include "lexer.h"
#include <memory>
#include <parser.h>
#include <stdexcept>
#include <string>
#include <iostream>

namespace Calc
{
    std::unique_ptr<ast::Expr> Parser::parse(const std::string& str)
    {
        tokens = lexer.tokenize(str);
        return parse_expr();
    }

    types::Token Parser::curr()
    {
        if(pos < tokens.size())
        {
            return tokens[pos];
        }
        return {types::TokenType::END};
    }
    types::Token Parser::peak(int offset=1)
    {
        if(pos + offset < tokens.size())
        {
            return tokens[pos + offset];
        }
        return {types::TokenType::END};
    }
    types::Token Parser::next(int offset=1)
    {
        pos+=offset;
        if(pos < tokens.size())
        {
            return tokens[pos];
        }
        return {types::TokenType::END};
    }

    std::unique_ptr<ast::Expr> Parser::parse_prim()
    {
        if(curr().tt == types::TokenType::NUMBER)
        {
            auto tok = curr();
            next();
            return std::make_unique<ast::Number>(std::stoi(tok.sym));
        }
        if(curr().tt == types::TokenType::LEFT_BRACKET)
        {
            next(); // skip bracket
            auto prim = parse_expr();
            if(curr().tt != types::TokenType::RIGHT_BRACKET)
            {
                std::cerr << "missing )" << std::endl;
                return std::move(prim);
            }
            next();
            return std::move(prim);
        }
        // unary
        if((curr().tt == types::TokenType::PLUS || curr().tt == types::TokenType::MINUS)
            && (peak().tt == types::TokenType::NUMBER || peak().tt == types::TokenType::LEFT_BRACKET)
        ){
            if(curr().tt == types::TokenType::MINUS)
            {
                next();
                return std::make_unique<ast::UnaryOp>(
                    ast::UnaryOp::Kind::MINUS, parse_prim()
                );
            }
        }

        std::cerr << "bad prim" << std::endl;
        throw std::runtime_error("bad primary");
        return nullptr;
    }

    std::unique_ptr<ast::Expr> Parser::parse_expr()
    {
        auto left = parse_term();
        while(curr().tt != types::TokenType::END)
        {
            auto op = curr();
            switch (op.tt)
            {
                case(types::TokenType::PLUS):
                    next();
                    left = std::make_unique<ast::BinOp>(
                        ast::BinOp::Kind::PLUS, std::move(left), parse_term()
                    ); break;

                case(types::TokenType::MINUS):
                    next();
                    left = std::make_unique<ast::BinOp>(
                        ast::BinOp::Kind::MINUS, std::move(left), parse_term()
                    ); break;

                default:
                    return std::move(left);
            }
        }
        return std::move(left);
    }

    std::unique_ptr<ast::Expr> Parser::parse_term()
    {
        auto left = parse_prim();
        while(curr().tt != types::TokenType::END)
        {
            auto op = curr();
            switch (op.tt)
            {
                case(types::TokenType::MUL):
                    next();
                    left = std::make_unique<ast::BinOp>(
                        ast::BinOp::Kind::MUL, std::move(left), parse_prim()
                    ); break;

                case(types::TokenType::DIV):
                    next();
                    left = std::make_unique<ast::BinOp>(
                        ast::BinOp::Kind::DIV, std::move(left), parse_prim()
                    ); break;

                default:
                    return std::move(left);
            }
        }
        return std::move(left);
    }
}
