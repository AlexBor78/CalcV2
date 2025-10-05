#pragma once

#include <memory>

#include <ast/types.h>

namespace Calc::ast
{
    class ConstVisitor;
    class NodeVisitor;

    class Expr
    {
    protected:
        const Type* type;
        Expr() = default;
        explicit Expr(const Type* _type): type(_type) {}
    public:
        virtual void accept(ConstVisitor&) const noexcept = 0;
        virtual void accept(NodeVisitor&) noexcept = 0;
        const Type* get_type() const {return type;}
    };

    class BinOp : public Expr
    {
    public:
        enum class Kind
        {
            PLUS,
            MINUS,
            MUL,
            DIV
        };
    private:
        Kind op;
        std::unique_ptr<Expr> left;
        std::unique_ptr<Expr> right;
        
    public:
        BinOp() = default;
        BinOp(
            Kind _op,
            std::unique_ptr<Expr> _left,
            std::unique_ptr<Expr> _right
        );

        Kind get_op() const;
        Expr* get_left() const;
        Expr* get_right() const;

        virtual void accept(ConstVisitor&) const noexcept override;
        virtual void accept(NodeVisitor&) noexcept override;
    };

    class UnaryOp : public Expr
    {
    public:
        enum class Kind
        {
            PLUS,
            MINUS
        };
    private:
        std::unique_ptr<Expr> child;
        Kind kind;

    public:
        UnaryOp() = default;
        UnaryOp(
            Kind _kind,
            std::unique_ptr<Expr> _child
        );

        Kind get_kind() const;
        Expr* get_child() const;

        virtual void accept(ConstVisitor&) const noexcept override;
        virtual void accept(NodeVisitor&) noexcept override;
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
        virtual void accept(NodeVisitor&) noexcept override;
    };

    class IntNumber : public Expr
    {
    private:
        int num;
    public:
        IntNumber() = default;
        IntNumber(int _num):
            num(_num)
        {}

        int get_num() const;

        virtual void accept(ConstVisitor&) const noexcept override;
        virtual void accept(NodeVisitor&) noexcept override;
    };

    class ConstVisitor
    {
    protected:
        ConstVisitor() = default;
        
    public:
        virtual void visit_binop(const BinOp&) = 0;
        virtual void visit_unaryop(const UnaryOp&) = 0;
        virtual void visit_num(const Number&) = 0;
    };

    class NodeVisitor
    {
    protected:
        NodeVisitor() = default;
        
    public:
        virtual void visit_binop(const BinOp&) = 0;
        virtual void visit_unaryop(const UnaryOp&) = 0;
        virtual void visit_num(const Number&) = 0;
    };
}
