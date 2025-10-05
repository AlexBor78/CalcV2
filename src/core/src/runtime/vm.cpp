#include "runtime/value.h"
#include <stdexcept>
#include <runtime/vm.h>
#include <runtime/vtables.h>

namespace Calc
{
    runtime::Value VM::exec(const std::vector<runtime::Instruction>& instructs)
    {
        for(auto& instruction : instructs)
        {
            switch (instruction.op)
            {
                case(runtime::OpCode::PUSH):
                    push(std::move(*instruction.operand.get()));
                    continue;

                case(runtime::OpCode::ADD):
                    add();
                    continue;

                case(runtime::OpCode::SUB):
                    sub();
                    continue;

                case(runtime::OpCode::MUL):
                    mul();
                    continue;

                case(runtime::OpCode::DIV):
                    div();
                    continue;
                case (runtime::OpCode::INVERSE):
                    inverse();
                    continue;
            }
        }
        // auto res = pop();
        // auto dres = res.cast(runtime::get_double_vtable());
        // std::cout << "Double res: " << dres.as<double>() << std::endl;
        // return res.as<int>();
        // bad!
        return pop();
    }

    runtime::Value VM::pop()
    {
        if(stack.empty())
        {
            throw std::runtime_error("Stack is empty");
        }
        runtime::Value op = stack.top();
        stack.pop();
        return std::move(op);
    }

    void VM::push(runtime::Value op)
    {
        stack.push(std::move(op));
    }

    void VM::add()
    {
        if(stack.size() < 2)
        {
            throw std::runtime_error("not enough operands");
        }
        runtime::Value op1 = pop();
        runtime::Value op2 = pop();
        push(op1 + op2);
    }

    void VM::sub()
    {
        if(stack.size() < 2)
        {
            throw std::runtime_error("not enough operands");
        }
        // change order because of stack
        runtime::Value op2 = pop();
        runtime::Value op1 = pop();
        push(op1 - op2);
    }

    void VM::mul()
    {
        if(stack.size() < 2)
        {
            throw std::runtime_error("not enough operands");
        }
        runtime::Value op1 = pop();
        runtime::Value op2 = pop();
        push(op1 * op2);
    }

    void VM::div()
    {
        if(stack.size() < 2)
        {
            throw std::runtime_error("not enough operands");
        }
        // change order because of stack
        runtime::Value op2 = pop();
        runtime::Value op1 = pop();
        push(op1 / op2);
    }

    void VM::inverse()
    {
        if(stack.empty())
        {
            throw std::runtime_error("Stack is empty");
        }
        runtime::Value op = pop();
        push(-op);
    }
}
