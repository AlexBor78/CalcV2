#pragma once

#include <memory>
#include <string>

#include <compile/lexer.h>
#include <ast/ast.h>

namespace Calc
{
    class Parser
    {
    private:
        Lexer lexer;
        std::vector<types::Token> tokens;
        size_t pos{0};
        
    public:
        Parser() = default;
        ~Parser() = default;

    public:

        std::unique_ptr<ast::Expr> parse(const std::string&);

    private:
        types::Token curr();
        types::Token peak(int);
        types::Token next(int);

        std::unique_ptr<ast::Expr> parse_prim();
        std::unique_ptr<ast::Expr> parse_expr();
        std::unique_ptr<ast::Expr> parse_term();
    };
}
