#pragma once

#include <ast.h>
#include <string>

namespace Calc::utils
{
    class PrintAST : public ast::ConstVisitor
    {
    private:
        std::string prefix{""};

    public:
        PrintAST() = default;
        ~PrintAST() = default;

    public:
        void print(ast::Expr*) noexcept;

    public:
        virtual void visit_binop(const ast::BinOp&) override;
        virtual void visit_unaryop(const ast::UnaryOp&) override;
        virtual void visit_num(const ast::Number&) override;
        
    };
}
