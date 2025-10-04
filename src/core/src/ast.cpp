#include <ast.h>

namespace Calc::ast
{
    // BinOp

    void BinOp::accept(ConstVisitor& visitor) const noexcept
    {
        visitor.visit_binop(*this);
    }

    BinOp::Kind BinOp::get_op() const
    {
        return op;
    }

    Expr* BinOp::get_left() const
    {
        return left.get();
    }

    Expr* BinOp::get_right() const
    {
        return right.get();
    }

    // UnaryOp

    void UnaryOp::accept(ConstVisitor& visitor) const noexcept
    {
        visitor.visit_unaryop(*this);
    }

    UnaryOp::Kind UnaryOp::get_kind() const
    {
        return kind;
    }

    Expr* UnaryOp::get_child() const
    {
        return child.get();
    }

    // Number

    void Number::accept(ConstVisitor& visitor) const noexcept
    {
        visitor.visit_num(*this);
    }

    int Number::get_num() const
    {
        return num;
    }
}
