#include "ast/ast.h"
#include <compile/typechecker.h>

namespace Calc::compile
{
    void TypeChecker::check(ast::Expr* root)
    {
        root->accept(*this);
    }

    void TypeChecker::visit_binop(ast::BinOp& op) noexcept
    {
        op.get_left()->accept(*this);
        op.get_right()->accept(*this);

        // if(op.get_left()->get_type() == table.get_double()
        // ||  op.get_right()->get_type() == table.get_double())
        // {
        //     op.set_type(table.get_double());
        // }
    }

    void TypeChecker::visit_unaryop(ast::UnaryOp& op) noexcept
    {
        op.get_child()->accept(*this);

        // if(op.get_child()->get_type() == table.get_double())
        // {
        //     op.set_type(table.get_double());
        // }
    }

    void TypeChecker::visit_intnum(ast::IntNumber& num) noexcept
    {
        // intnum is alright :)
    }

    void TypeChecker::visit_doublenum(ast::DoubleNumber& num) noexcept
    {
        // doublenum is alright :)
    }
}
