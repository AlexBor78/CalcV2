#pragma once
#include <compile/defs.h>
#include <runtime/bytecode.h>

namespace Calc::utils
{
    void print_token(Calc::types::Token);
    void print_instruct(const Calc::runtime::Instruction&);
}
