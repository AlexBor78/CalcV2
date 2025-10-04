#include "ast.h"
#include "defs.h"
#include <compiler.h>
#include <vector>

namespace Calc
{
    std::vector<types::Instruction> Compiler::compile(ast::Expr* root)
    {
        root->accept(*this);
        return std::move(code);
    }

    void Compiler::visit_num(const ast::Number& num)
    {
        code.push_back({types::OpCode::PUSH, num.get_num()});
    }

    void Compiler::visit_unaryop(const ast::UnaryOp& op)
    {
        op.get_child()->accept(*this);
        if(op.get_kind() == ast::UnaryOp::Kind::MINUS)
        {
            code.push_back({types::OpCode::INVERSE});
        }
    }

    void Compiler::visit_binop(const ast::BinOp& op)
    {
        op.get_left()->accept(*this);
        op.get_right()->accept(*this);
        switch (op.get_op())
        {
            case(ast::BinOp::Kind::PLUS):
                code.push_back({types::OpCode::ADD});
                break;

            case(ast::BinOp::Kind::MINUS):
                code.push_back({types::OpCode::SUB});
                break;

            case(ast::BinOp::Kind::MUL):
                code.push_back({types::OpCode::MUL});
                break;

            case(ast::BinOp::Kind::DIV):
                code.push_back({types::OpCode::DIV});
                break;
        }
    }
}
