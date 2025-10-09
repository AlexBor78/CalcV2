#pragma once

#include "compile/defs.h"
#include <memory>
#include <vector>

#include <compile/lexer.h>
#include <ast/ast.h>
#include <ast/typetable.h>

namespace Calc
{
    class Parser
    {
    private:
        Lexer lexer;
        const std::vector<types::Token>* tokens;
        size_t pos{0};
        ast::TypeTable typetable;

    private:
        types::Token curr() const noexcept;
        types::Token peak(int offset = 1) const noexcept;
        types::Token next(int offset = 1) noexcept;

        std::unique_ptr<ast::Expr> parse_prim();
        std::unique_ptr<ast::Expr> parse_expr();
        std::unique_ptr<ast::Expr> parse_term();

    public:
        std::unique_ptr<ast::Expr> parse(const std::vector<types::Token>&);
        const ast::TypeTable& get_typetable() const noexcept;
    };
}
