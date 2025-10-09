#pragma once

#include <vector>

#include <ast/ast.h>
#include <runtime/bytecode.h>

namespace Calc
{
    class CodeGenerator : public ast::ConstVisitor
    {
    private:
        std::vector<runtime::Instruction> code;

    public:
        std::vector<runtime::Instruction> generate(ast::Expr*);

        virtual void visit_binop(const ast::BinOp&) noexcept override;
        virtual void visit_unaryop(const ast::UnaryOp&) noexcept override;
        virtual void visit_intnum(const ast::IntNumber&) noexcept override;
        virtual void visit_doublenum(const ast::DoubleNumber&) noexcept override;
    };
}
