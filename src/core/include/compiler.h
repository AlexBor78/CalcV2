#pragma once

#include <vector>

#include <defs.h>
#include <ast.h>

class Compiler : public ConstVisitor
{
private:
    std::vector<Instruction> code;

public:
    Compiler() = default;
    ~Compiler() = default;

public:
    std::vector<Instruction> compile(Expr*);

public:
    virtual void visit_op(const BinOp&) override;
    virtual void visit_num(const Number&) override;

};
