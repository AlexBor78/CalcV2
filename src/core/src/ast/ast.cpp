#include <ast/ast.h>

namespace Calc::ast
{
    // BinOp

    BinOp::BinOp(
        Kind _op,
        std::unique_ptr<Expr> _left,
        std::unique_ptr<Expr> _right
    ):  Expr(_left->get_type())
    ,   op(_op)
    ,   left(std::move(_left))
    ,   right(std::move(_right))
    {}

    void BinOp::accept(ConstVisitor& visitor) const noexcept
    {
        visitor.visit_binop(*this);
    }

    void BinOp::accept(NodeVisitor& visitor) noexcept
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

    UnaryOp::UnaryOp(
        Kind _kind,
        std::unique_ptr<Expr> _child
    ):  Expr(_child->get_type())
    ,   kind(_kind)
    ,   child(std::move(_child))
    {}

    void UnaryOp::accept(ConstVisitor& visitor) const noexcept
    {
        visitor.visit_unaryop(*this);
    }

    void UnaryOp::accept(NodeVisitor& visitor) noexcept
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

    void Number::accept(NodeVisitor& visitor) noexcept
    {
        visitor.visit_num(*this);
    }

    int Number::get_num() const
    {
        return num;
    }
}
