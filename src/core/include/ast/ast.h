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
        const Type* get_type() const noexcept {return type;}
        void set_type(const Type* _type) noexcept {type = _type;}
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

        Kind get_op() const noexcept;
        Expr* get_left() const noexcept;
        Expr* get_right() const noexcept;

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

        Kind get_kind() const noexcept;
        Expr* get_child() const noexcept;

        virtual void accept(ConstVisitor&) const noexcept override;
        virtual void accept(NodeVisitor&) noexcept override;
    };

    class IntNumber : public Expr
    {
    private:
        int num;
    public:
        IntNumber() = default;
        explicit IntNumber(int _num):
            num(_num)
        {}

        int get_num() const noexcept;

        virtual void accept(ConstVisitor&) const noexcept override;
        virtual void accept(NodeVisitor&) noexcept override;
    };

    class ConstVisitor
    {
    protected:
        ConstVisitor() = default;
        
    public:
        virtual void visit_binop(const BinOp&) noexcept = 0;
        virtual void visit_unaryop(const UnaryOp&) noexcept = 0;
        virtual void visit_num(const IntNumber&) noexcept = 0;
    };

    class NodeVisitor
    {
    protected:
        NodeVisitor() = default;
        
    public:
        virtual void visit_binop(BinOp&) noexcept = 0;
        virtual void visit_unaryop(UnaryOp&) noexcept = 0;
        virtual void visit_num(IntNumber&) noexcept = 0;
    };
}
