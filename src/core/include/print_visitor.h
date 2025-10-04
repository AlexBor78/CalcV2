#pragma once

#include <ast.h>
#include <string>

class PrintAST : public ConstVisitor
{
private:
    std::string prefix{""};

public:
    PrintAST() = default;
    ~PrintAST() = default;

public:
    void print(Expr*) noexcept;

public:
    virtual void visit_binop(const BinOp&) override;
    virtual void visit_unaryop(const UnaryOp&) override;
    virtual void visit_num(const Number&) override;
    
};
