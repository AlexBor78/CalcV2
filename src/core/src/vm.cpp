#include "defs.h"
#include <stdexcept>
#include <vm.h>

namespace Calc
{
    int VM::exec(const std::vector<types::Instruction>& instructs)
    {
        for(auto instruction : instructs)
        {
            switch (instruction.op)
            {
                case(types::OpCode::PUSH):
                    push(instruction.operand);
                    continue;

                case(types::OpCode::ADD):
                    add();
                    continue;

                case(types::OpCode::SUB):
                    sub();
                    continue;

                case(types::OpCode::MUL):
                    mul();
                    continue;

                case(types::OpCode::DIV):
                    div();
                    continue;
                case (types::OpCode::INVERSE):
                    inverse();
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
        push(op1 + op2);
    }

    void VM::sub()
    {
        if(stack.size() < 2)
        {
            throw std::runtime_error("not enough operands");
        }
        // change order because of stack
        int op2 = pop();
        int op1 = pop();
        push(op1 - op2);
    }

    void VM::mul()
    {
        if(stack.size() < 2)
        {
            throw std::runtime_error("not enough operands");
        }
        int op1 = pop();
        int op2 = pop();
        push(op1 * op2);
    }

    void VM::div()
    {
        if(stack.size() < 2)
        {
            throw std::runtime_error("not enough operands");
        }
        // change order because of stack
        int op2 = pop();
        int op1 = pop();
        if(op2 == 0)
        {
            std::runtime_error("Division by 0");
        }
        push(op1 / op2);
    }

    void VM::inverse()
    {
        if(stack.empty())
        {
            throw std::runtime_error("Stack is empty");
        }
        int op = pop();
        push(-op);
    }
}
