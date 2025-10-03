#include "defs.h"
#include <stdexcept>
#include <vm.h>

int VM::exec(const std::vector<Instruction>& instructs)
{
    for(auto instruction : instructs)
    {
        switch (instruction.op)
        {
            case(OpCode::PUSH):
                push(instruction.operand);
                continue;

            case(OpCode::ADD):
                add();
                continue;

            case(OpCode::SUB):
                sub();
                continue;

            case(OpCode::MUL):
                mul();
                continue;

            case(OpCode::DIV):
                div();
                continue;
        }
    }
    
    return pop();
}

int VM::pop()
{
    if(stack.empty())
    {
        throw std::runtime_error("Stack is empty");
    }
    int op = stack.top();
    stack.pop();
    return op;
}

void VM::push(int op)
{
    stack.push(op);
}

void VM::add()
{
    if(stack.size() < 2)
    {
        throw std::runtime_error("not enough operands");
    }
    int op1 = pop();
    int op2 = pop();
    stack.push(op1 + op2);
}

void VM::sub()
{
    if(stack.size() < 2)
    {
        throw std::runtime_error("not enough operands");
    }
    int op1 = pop();
    int op2 = pop();
    stack.push(op1 - op2);
}

void VM::mul()
{
    if(stack.size() < 2)
    {
        throw std::runtime_error("not enough operands");
    }
    int op1 = pop();
    int op2 = pop();
    stack.push(op1 * op2);
}

void VM::div()
{
    if(stack.size() < 2)
    {
        throw std::runtime_error("not enough operands");
    }
    int op1 = pop();
    int op2 = pop();
    if(op2 == 0)
    {
        std::runtime_error("Division by 0");
    }
    stack.push(op1 / op2);
}
