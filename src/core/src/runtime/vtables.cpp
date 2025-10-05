#include "runtime/value.h"
#include <iostream>
#include <stdexcept>
#include <runtime/vtables.h>

namespace Calc::runtime
{
    const ValueVTable* get_int_vtable()
    {
        static const ValueVTable INT_VTABLE
        {
            .name = "int",
            .copy = [](const Value& value)
            {
                return ValueFactory::make_int(value.as<int>());
            },
            .destroy = [](void* ptr)
            {
                if(ptr != nullptr)
                {
                    delete static_cast<int*>(ptr);
                }
            },
            .promote = [](const ValueVTable* other)
            {
                if(other == get_double_vtable())
                {
                    return get_double_vtable();
                }
                return get_int_vtable();
            },
            .cast = [](const Value& value, const ValueVTable* vtable)
            {
                if(vtable == get_int_vtable())
                {
                    return ValueFactory::make_int(value.as<int>());
                }
                if(vtable == get_double_vtable())
                {
                    return ValueFactory::make_double(value.as<int>());
                }
                return value.copy(); // todo:
            },
            .print = [](const Value& value)
            {
                std::cout << value.get_name() << "(" << value.as<int>() << ")" << std::endl;
            },
            // logical
            .equals = [](const Value& left, const Value& right)
            {
                return left.as<int>() == right.as<int>();
            },
            .notequals = [](const Value& left, const Value& right)
            {
                return left.as<int>() != right.as<int>();
            },
            // math
            .add = [](const Value& left, const Value& right)
            {
                return ValueFactory::make_int(left.as<int>() + right.as<int>());
            },
            .sub = [](const Value& left, const Value& right)
            {
                return ValueFactory::make_int(left.as<int>() - right.as<int>());
            },
            .mul = [](const Value& left, const Value& right)
            {
                return ValueFactory::make_int(left.as<int>() * right.as<int>());
            },
            .div = [](const Value& left, const Value& right)
            {
                if(right.as<int>() == 0)
                {
                    std::runtime_error("Division by 0");
                }
                if(left.as<int>() % right.as<int>() == 0)
                {
                    return ValueFactory::make_int(left.as<int>() / right.as<int>());
                }
                return ValueFactory::make_double(
                    left.cast(get_double_vtable()).as<double>() / right.as<int>()
                );
            },
            .inverse = [](const Value& value)
            {
                return ValueFactory::make_int(-value.as<int>());
            }
        };
        return &INT_VTABLE;
    }

    const ValueVTable* get_double_vtable()
    {
        static const ValueVTable DOUBLE_VTABLE
        {
            .name = "double",
            .copy = [](const Value& value)
            {
                return ValueFactory::make_double(value.as<double>());
            },
            .destroy = [](void* ptr)
            {
                if(ptr != nullptr)
                {
                    delete static_cast<double*>(ptr);
                }
            },
            .promote = [](const ValueVTable* other)
            {
                return get_double_vtable();
            },
            .cast = [](const Value& value, const ValueVTable* vtable)
            {
                if(vtable == get_int_vtable())
                {
                    return ValueFactory::make_int(value.as<double>());
                }
                if(vtable == get_double_vtable())
                {
                    return ValueFactory::make_double(value.as<double>());
                }
                return value.copy();
            },
            .print = [](const Value& value)
            {
                std::cout << value.get_name() << "(" << value.as<double>() << ")" << std::endl;
            },
            // logical
            .equals = [](const Value& left, const Value& right)
            {
                return left.as<double>() == right.as<double>();
            },
            .notequals = [](const Value& left, const Value& right)
            {
                return left.as<double>() != right.as<double>();
            },
            // math
            .add = [](const Value& left, const Value& right)
            {
                return ValueFactory::make_double(left.as<double>() + right.as<double>());
            },
            .sub = [](const Value& left, const Value& right)
            {
                return ValueFactory::make_double(left.as<double>() - right.as<double>());
            },
            .mul = [](const Value& left, const Value& right)
            {
                return ValueFactory::make_double(left.as<double>() * right.as<double>());
            },
            .div = [](const Value& left, const Value& right)
            {
                if(right.as<double>() == 0)
                {
                    std::runtime_error("Division by 0");
                }
                return ValueFactory::make_double(left.as<double>() / right.as<double>());
            },
            .inverse = [](const Value& value)
            {
                return ValueFactory::make_double(-value.as<double>());
            }
        };
        return &DOUBLE_VTABLE;
    }
}
