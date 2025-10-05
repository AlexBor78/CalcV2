#pragma once
#include <runtime/value.h>

namespace Calc::runtime
{
    const ValueVTable* get_int_vtable();
    const ValueVTable* get_double_vtable();
}
