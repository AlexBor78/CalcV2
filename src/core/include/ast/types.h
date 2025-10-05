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
        virtual Kind get_kind() const = 0;
        virtual std::string_view get_name() const = 0;
        bool operator==(const Type& other) const
        {
            return this == &other;
        }
    };

    class Builtin : public Type
    {
    protected:
        Builtin() = default;

    public:
        virtual Kind get_kind() const override {return Kind::BUILTIN;}
        virtual std::string_view get_name() const override = 0;
    };

    class IntType : public Builtin
    {
    public:
        IntType() = default;
        virtual std::string_view get_name() const override {return "int";}
    };

// in future:
/*
    class DoubleType : public Builtin
    {

    };

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
