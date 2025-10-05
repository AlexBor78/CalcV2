#pragma once

#include <ast/ast.h>
#include <ast/types.h>
#include <ast/typetable.h>

namespace Calc::compile
{
    class TypeChecker : public ast::NodeVisitor
    {
    private:
        const ast::TypeTable& table;
        
    public:
        TypeChecker() = delete;
        explicit TypeChecker(const ast::TypeTable& _table):
            table(_table)
        {}

        void check(ast::Expr*);
        
    public:
        virtual void visit_binop(ast::BinOp&) noexcept;
        virtual void visit_unaryop(ast::UnaryOp&) noexcept;
        virtual void visit_num(ast::IntNumber&) noexcept;
    };
}
