#include <ast.h>

// BinOp

void BinOp::accept(ConstVisitor& visitor) const noexcept
{
    visitor.visit_op(*this);
}

BinOp::BinOpKind BinOp::get_op() const
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

// Number

void Number::accept(ConstVisitor& visitor) const noexcept
{
    visitor.visit_num(*this);
}

int Number::get_num() const
{
    return num;
}
