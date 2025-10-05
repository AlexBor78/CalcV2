#pragma once

#include <string>
#include <ast/ast.h>

namespace Calc::utils
{
    class PrintAST : public ast::ConstVisitor
    {
    private:
        std::string prefix{""};

    public:
        void print(ast::Expr*) noexcept;

        virtual void visit_binop(const ast::BinOp&) noexcept override;
        virtual void visit_unaryop(const ast::UnaryOp&) noexcept override;
        virtual void visit_intnum(const ast::IntNumber&) noexcept override;
        virtual void visit_doublenum(const ast::DoubleNumber&) noexcept override;
    };
}
