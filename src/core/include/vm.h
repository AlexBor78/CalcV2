#pragma once

#include <vector>
#include <stack>

#include <defs.h>


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

public:
    VM() = default;
    ~VM() = default;

public:
    int exec(const std::vector<Instruction>&);
};
