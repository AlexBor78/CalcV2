#pragma once

#include <string_view>

namespace Calc::ast
{
    class Type
    {
    public:
        enum class Kind
        {
            BUILTIN
            // ENUM,
            // CLASS
        };
    protected:
        Type() = default;

    public:
        virtual Kind get_kind() const noexcept = 0;
        virtual std::string_view get_name() const noexcept = 0;
        bool operator==(const Type& other) const noexcept
        {
            return this == &other;
        }
    };

    class Builtin : public Type
    {
    protected:
        Builtin() = default;

    public:
        virtual Kind get_kind() const noexcept override {return Kind::BUILTIN;}
        virtual std::string_view get_name() const noexcept override = 0;
    };

    class IntType : public Builtin
    {
    public:
        IntType() = default;
        virtual std::string_view get_name() const noexcept override {return "int";}
    };

    class DoubleType : public Builtin
    {
    public:
        DoubleType() = default;
        virtual std::string_view get_name() const noexcept override {return "double";}
    };

// in future:
/*
    class UserType : public Type
    {

    };

    class EnumClass : public UserType
    {

    };

    class ClassType : public UserType
    {

    };
*/
}
