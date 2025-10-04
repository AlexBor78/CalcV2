#include "ast.h"
#include <iostream>
#include <print_visitor.h>

namespace
{
    constexpr const char* binoptostr(BinOp::Kind op)
    {
        switch (op) 
        {
            case(BinOp::Kind::PLUS):
                return "PLUS";

            case(BinOp::Kind::MINUS):
                return "MINUS";

            case(BinOp::Kind::MUL):
                return "MUL";

            case(BinOp::Kind::DIV):
                return "DIV";
        }
        return "UNKNOWN OPERATOR";
    }

    constexpr const char* unaryoptostr(UnaryOp::Kind op)
    {
        switch (op)
        {
            case (UnaryOp::Kind::PLUS):
                return "PLUS";

            case (UnaryOp::Kind::MINUS):
                return "MINUS";
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

void PrintAST::visit_binop(const BinOp& op)
{
    std::cout << prefix << "BinOpNode: op:" << binoptostr(op.get_op()) << std::endl;
    prefix+='\t';
    // print left operand
    std::cout << prefix << "left Expr:" << std::endl;
    op.get_left()->accept(*this);
    // print right operant
    std::cout << prefix << "right Expr:" << std::endl;
    op.get_right()->accept(*this);
    prefix.pop_back();
}

void PrintAST::visit_unaryop(const UnaryOp& op)
{
    std::cout << prefix << "UnaryOpNode: op:" << unaryoptostr(op.get_kind()) << std::endl;
    prefix+='\t';
    // print left operand
    std::cout << prefix << "child Expr:" << std::endl;
    op.get_child()->accept(*this);
    prefix.pop_back();
}

