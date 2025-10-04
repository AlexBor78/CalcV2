#pragma once

#include <vector>

#include <defs.h>
#include <ast/ast.h>

namespace Calc
{
    class Compiler : public ast::ConstVisitor
    {
    private:
        std::vector<types::Instruction> code;

    public:
        Compiler() = default;
        ~Compiler() = default;

    public:
        std::vector<types::Instruction> compile(ast::Expr*);

    public:
        virtual void visit_binop(const ast::BinOp&) override;
        virtual void visit_num(const ast::Number&) override;
        virtual void visit_unaryop(const ast::UnaryOp&) override;

    };
}
