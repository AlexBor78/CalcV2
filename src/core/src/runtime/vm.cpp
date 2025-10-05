#include <stdexcept>
#include <runtime/vm.h>

namespace Calc
{
    int VM::exec(const std::vector<runtime::Instruction>& instructs)
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
        // bad!
        return pop().as<int>();
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
        push(op1.add(op2));
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
        push(op1.sub(op2));
    }

    void VM::mul()
    {
        if(stack.size() < 2)
        {
            throw std::runtime_error("not enough operands");
        }
        runtime::Value op1 = pop();
        runtime::Value op2 = pop();
        push(op1.mul(op2));
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
        if(op2.as<int>() == 0)
        {
            std::runtime_error("Division by 0");
        }
        push(op1.div(op2));
    }

    void VM::inverse()
    {
        if(stack.empty())
        {
            throw std::runtime_error("Stack is empty");
        }
        runtime::Value op = pop();
        push(op.inverse());
    }
}
