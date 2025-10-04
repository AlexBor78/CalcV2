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

void Compiler::visit_unaryop(const UnaryOp& op)
{
    op.get_child()->accept(*this);
    if(op.get_kind() == UnaryOp::Kind::MINUS)
    {
        code.push_back({OpCode::INVERSE});
    }
}

void Compiler::visit_binop(const BinOp& op)
{
    op.get_left()->accept(*this);
    op.get_right()->accept(*this);
    switch (op.get_op())
    {
        case(BinOp::Kind::PLUS):
            code.push_back({OpCode::ADD});
            break;

        case(BinOp::Kind::MINUS):
            code.push_back({OpCode::SUB});
            break;

        case(BinOp::Kind::MUL):
            code.push_back({OpCode::MUL});
            break;

        case(BinOp::Kind::DIV):
            code.push_back({OpCode::DIV});
            break;
    }
}
