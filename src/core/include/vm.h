#pragma once

#include <vector>
#include <stack>

#include <defs.h>

namespace Calc
{
    class VM
    {
    private:
    std::stack<int> stack;

    private:
    int pop();

    private:
    void push(int);
    void add();
    void sub();
    void mul();
    void div();
    void inverse();

    public:
    VM() = default;
    ~VM() = default;

    public:
    int exec(const std::vector<types::Instruction>&);
    };
}
