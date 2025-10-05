#include <compile/compiler.h>
#include <memory>
#include <vector>

namespace Calc
{
    std::vector<runtime::Instruction> Compiler::compile(ast::Expr* root)
    {
        root->accept(*this);
        return std::move(code);
    }

    void Compiler::visit_num(const ast::IntNumber& num) noexcept
    {
        code.emplace_back(
            runtime::OpCode::PUSH, 
            std::make_unique<runtime::Value>(
                runtime::ValueFactory::make_int(num.get_num())
            )
        );
    }

    void Compiler::visit_unaryop(const ast::UnaryOp& op) noexcept
    {
        op.get_child()->accept(*this);
        if(op.get_kind() == ast::UnaryOp::Kind::MINUS)
        {
            code.emplace_back(runtime::OpCode::INVERSE);
        }
    }

    void Compiler::visit_binop(const ast::BinOp& op) noexcept
    {
        op.get_left()->accept(*this);
        op.get_right()->accept(*this);
        switch (op.get_op())
        {
            case(ast::BinOp::Kind::PLUS):
                code.emplace_back(runtime::OpCode::ADD);
                break;

            case(ast::BinOp::Kind::MINUS):
                code.emplace_back(runtime::OpCode::SUB);
                break;

            case(ast::BinOp::Kind::MUL):
                code.emplace_back(runtime::OpCode::MUL);
                break;

            case(ast::BinOp::Kind::DIV):
                code.emplace_back(runtime::OpCode::DIV);
                break;
        }
    }
}
