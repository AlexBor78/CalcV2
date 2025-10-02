#include "ast.h"
#include <iostream>
#include <print_visitor.h>

namespace
{
    constexpr const char* optostr(BinOp::BinOpKind op)
    {
        switch (op) 
        {
            case(BinOp::BinOpKind::PLUS):
                return "PLUS";

            case(BinOp::BinOpKind::MINUS):
                return "MINUS";

            case(BinOp::BinOpKind::MUL):
                return "MUL";

            case(BinOp::BinOpKind::DIV):
                return "DIV";
        }
        return "UNKNOWN OPERATOR";
    }
}

void PrintAST::print(Expr* root) noexcept
{
    root->accept(*this);
}

void PrintAST::visit_num(const Number& num)
{
    std::cout << prefix << "NumberNode: " << num.get_num() << std::endl;
}

void PrintAST::visit_op(const BinOp& op)
{
    std::cout << prefix << "BinOpNode: op:" << optostr(op.get_op()) << std::endl;
    prefix+='\t';
    // print left operand
    std::cout << prefix << "left Expr:" << std::endl;
    op.get_left()->accept(*this);
    // print right operant
    std::cout << prefix << "right Expr:" << std::endl;
    op.get_right()->accept(*this);
    prefix.pop_back();
}
