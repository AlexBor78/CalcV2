#pragma once

#include <vector>
#include <stack>

#include <runtime/value.h>
#include <runtime/bytecode.h>

namespace Calc
{
    class VM
    {
    private:
        std::stack<runtime::Value> stack;

    private:
        runtime::Value pop();

        void push(runtime::Value);
        void add();
        void sub();
        void mul();
        void div();
        void inverse();

    public:
        int exec(const std::vector<runtime::Instruction>&);
    };
}
