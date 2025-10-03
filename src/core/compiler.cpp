#include "ast.h"
#include "defs.h"
#include <compiler.h>
#include <vector>

std::vector<Instruction> Compiler::compile(Expr* root)
{
    root->accept(*this);
    return std::move(code);
}

void Compiler::visit_num(const Number& num)
{
    code.push_back({OpCode::PUSH, num.get_num()});
}

void Compiler::visit_op(const BinOp& op)
{
    op.get_left()->accept(*this);
    op.get_right()->accept(*this);
    switch (op.get_op())
    {
        case(BinOp::BinOpKind::PLUS):
            code.push_back({OpCode::ADD});
            break;

        case(BinOp::BinOpKind::MINUS):
            code.push_back({OpCode::SUB});
            break;

        case(BinOp::BinOpKind::MUL):
            code.push_back({OpCode::MUL});
            break;

        case(BinOp::BinOpKind::DIV):
            code.push_back({OpCode::DIV});
            break;
    }
}
