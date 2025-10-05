#pragma once

#include <string>
#include <iostream>
#include <string_view>

namespace Calc::runtime
{
    class Value;
    class ValueFactory
    {
    public:
        static Value make_int(int);
    };

    struct ValueVTable
    {
        std::string name;
        Value (*add)(const Value&, const Value&) = nullptr;
        Value (*sub)(const Value&, const Value&) = nullptr;
        Value (*mul)(const Value&, const Value&) = nullptr;
        Value (*div)(const Value&, const Value&) = nullptr;
        Value (*inverse)(const Value&) = nullptr;
        void (*print)(const Value&) = nullptr;
        void (*destroy)(void*) = nullptr;
    };

    class Value
    {
    private:
        void* value;
        const ValueVTable* vtable;

    public:
        Value(void* v, const ValueVTable* t);
        Value& operator=(const Value&) = delete;
        Value(const Value&) = delete;
        Value(Value&);
        Value(Value&&);
        ~Value();

        Value add(const Value&);
        Value sub(const Value&);
        Value mul(const Value&);
        Value div(const Value&);
        void print();
        Value inverse();

        std::string_view get_name() const noexcept;

        template<class T>
        const T& as() const;
    };

    static const ValueVTable INT_VTABLE
    {
        .name = "int",
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
            return ValueFactory::make_int(left.as<int>() / right.as<int>());
        },
        .inverse = [](const Value& value)
        {
            return ValueFactory::make_int(-value.as<int>());
        },
        .print = [](const Value& value)
        {
            std::cout << value.get_name() << "(" << value.as<int>() << ")" << std::endl;
        },
        .destroy = [](void* ptr)
        {
            if(ptr != nullptr)
            {
                delete static_cast<int*>(ptr);
            }
        }
    };
}
