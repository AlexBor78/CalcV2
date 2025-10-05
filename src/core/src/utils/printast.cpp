#include "ast/ast.h"
#include <iostream>
#include <utils/printast.h>

namespace Calc::utils
{
    constexpr const char* binoptostr(ast::BinOp::Kind op)
    {
        switch (op) 
        {
            case(ast::BinOp::Kind::PLUS):
                return "PLUS";

            case(ast::BinOp::Kind::MINUS):
                return "MINUS";

            case(ast::BinOp::Kind::MUL):
                return "MUL";

            case(ast::BinOp::Kind::DIV):
                return "DIV";
        }
        return "UNKNOWN OPERATOR";
    }

    constexpr const char* unaryoptostr(ast::UnaryOp::Kind op)
    {
        switch (op)
        {
            case (ast::UnaryOp::Kind::PLUS):
                return "PLUS";

            case (ast::UnaryOp::Kind::MINUS):
                return "MINUS";
        }
        return "UNKNOWN OPERATOR";
    }

    void PrintAST::print(ast::Expr* root) noexcept
    {
        root->accept(*this);
    }

    void PrintAST::visit_intnum(const ast::IntNumber& num) noexcept
    {
        std::cout << prefix << "IntNumber: " << num.get_num() << std::endl;
    }

    void PrintAST::visit_doublenum(const ast::DoubleNumber& num) noexcept
    {
        std::cout << prefix << "DoubleNumber: " << num.get_num() << std::endl;
    }

    void PrintAST::visit_binop(const ast::BinOp& op) noexcept
    {
        std::cout << prefix << "BinOpNode: op:" << binoptostr(op.get_op()) << std::endl;
        prefix+='\t';
        // print left operand
        std::cout << prefix << "left ast::Expr:" << std::endl;
        op.get_left()->accept(*this);
        // print right operant
        std::cout << prefix << "right ast::Expr:" << std::endl;
        op.get_right()->accept(*this);
        prefix.pop_back();
    }

    void PrintAST::visit_unaryop(const ast::UnaryOp& op) noexcept
    {
        std::cout << prefix << "UnaryOpNode: op:" << unaryoptostr(op.get_kind()) << std::endl;
        prefix+='\t';
        // print left operand
        std::cout << prefix << "child ast::Expr:" << std::endl;
        op.get_child()->accept(*this);
        prefix.pop_back();
    }
}
