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

    BinOp::Kind BinOp::get_op() const noexcept
    {
        return op;
    }

    Expr* BinOp::get_left() const noexcept
    {
        return left.get();
    }

    Expr* BinOp::get_right() const noexcept
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

    UnaryOp::Kind UnaryOp::get_kind() const noexcept
    {
        return kind;
    }

    Expr* UnaryOp::get_child() const noexcept
    {
        return child.get();
    }

    // IntNumber

    void IntNumber::accept(ConstVisitor& visitor) const noexcept
    {
        visitor.visit_intnum(*this);
    }

    void IntNumber::accept(NodeVisitor& visitor) noexcept
    {
        visitor.visit_intnum(*this);
    }

    int IntNumber::get_num() const noexcept
    {
        return num;
    }

    // DoubleNumber

    void DoubleNumber::accept(ConstVisitor& visitor) const noexcept
    {
        visitor.visit_doublenum(*this);
    }

    void DoubleNumber::accept(NodeVisitor& visitor) noexcept
    {
        visitor.visit_doublenum(*this);
    }

    double DoubleNumber::get_num() const noexcept
    {
        return num;
    }
}
