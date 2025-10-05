#pragma once

#include <string>
#include <string_view>

namespace Calc::runtime
{
    class Value;
    class ValueFactory
    {
    public:
        static Value make_int(int);
        static Value make_double(double);
    };

    struct ValueVTable
    {
        std::string name;
        // void* (*build)() = nullptr;
        Value (*copy)(const Value&) = nullptr;
        void (*destroy)(void*) = nullptr;

        const ValueVTable* (*promote)(const ValueVTable*) = nullptr;
        Value (*cast)(const Value&, const ValueVTable*) = nullptr;

        void (*print)(const Value&) = nullptr;

        // logical operators
        bool (*equals)(const Value&, const Value&) = nullptr;
        bool (*notequals)(const Value&, const Value&) = nullptr;

        // math operators
        Value (*add)(const Value&, const Value&) = nullptr;
        Value (*sub)(const Value&, const Value&) = nullptr;
        Value (*mul)(const Value&, const Value&) = nullptr;
        Value (*div)(const Value&, const Value&) = nullptr;
        Value (*inverse)(const Value&) = nullptr;
    };

    class Value
    {
    private:
        void* value;
        const ValueVTable* vtable;

        const ValueVTable* promote(const Value&) const;

    public:
        Value(void* v, const ValueVTable* t);
        Value& operator=(const Value&) = delete;
        Value(const Value&) = delete;
        Value(Value&);
        Value(Value&&);
        ~Value();

        Value cast(const ValueVTable*) const;
        Value copy() const;

        void print() const;

        bool equals(const Value&) const;
        bool notequals(const Value&) const;

        Value add(const Value&) const;
        Value sub(const Value&) const;
        Value mul(const Value&) const;
        Value div(const Value&) const;
        Value inverse() const;

        std::string_view get_name() const noexcept;
        const ValueVTable* get_vtable() const noexcept;

        void* get_raw() noexcept;
        const void* get_raw() const noexcept;
        template<class T> const T& as() const noexcept
        {
            return *static_cast<T*>(value);
        }
        template<class T> T& as() noexcept
        {
            return *static_cast<T*>(value);
        }
        
        bool operator==(const Value&) const;
        bool operator!=(const Value&) const;
        Value operator+(const Value&) const;
        Value operator-(const Value&) const;
        Value operator*(const Value&) const;
        Value operator/(const Value&) const;
        Value operator-() const;
    };
}
