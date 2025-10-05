#pragma once

#include <cstdint>
#include <memory>
#include <runtime/value.h>

namespace Calc::runtime
{
    enum class OpCode : uint8_t
    {
        PUSH,
        ADD,
        SUB,
        MUL,
        DIV,
        INVERSE
    };

    struct Instruction
    {
        OpCode op;
        std::unique_ptr<Value> operand{nullptr};
        
        Instruction(OpCode code, std::unique_ptr<Value> v):
            op(code), operand(std::move(v))
        {}
        explicit Instruction(OpCode code):
            op(code), operand(nullptr)
        {}
    };
}
