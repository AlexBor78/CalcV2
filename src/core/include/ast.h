#pragma once

#include <memory>

class ConstVisitor;

class Expr 
{
protected:
    Expr() = default;
public:
    virtual void accept(ConstVisitor&) const noexcept = 0;
    // virtual void accept(NodeVisitor&) noexcept = 0;
};

class BinOp : public Expr
{
public:
    enum class BinOpKind
    {
        PLUS,
        MINUS,
        MUL,
        DIV
    };
private:
    BinOpKind op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    
public:
    BinOp() = default;
    BinOp(
        BinOpKind _op,
        std::unique_ptr<Expr>&& _left,
        std::unique_ptr<Expr>&& _right
    ):  op(_op)
    ,   left(std::move(_left))
    ,   right(std::move(_right))
    {}

    BinOpKind get_op() const;
    Expr* get_left() const;
    Expr* get_right() const;


    virtual void accept(ConstVisitor&) const noexcept override;
};

class Number : public Expr
{
private:
    int num;
public:
    Number() = default;
    Number(int _num):
        num(_num)
    {}

    int get_num() const;

    virtual void accept(ConstVisitor&) const noexcept override;
};

class ConstVisitor
{
protected:
    ConstVisitor() = default;
    
public:
    virtual void visit_op(const BinOp&) = 0;
    virtual void visit_num(const Number&) = 0;
};
