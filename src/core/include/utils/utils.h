#pragma once
#include <compile/defs.h>
#include <runtime/bytecode.h>
#include <runtime/value.h>

namespace Calc::utils
{
    void print_token(Calc::types::Token);
    void print_instruct(const Calc::runtime::Instruction&);
    void print_value(const runtime::Value&);
}
