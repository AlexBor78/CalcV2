#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

#include <ast/types.h>

namespace Calc::ast
{
    class TypeTable
    {
    private:
        std::unordered_map<std::string_view, std::unique_ptr<Type>> table;
        void init_builtin();

    public:
        TypeTable();

        const Type* get_int() const noexcept;
        const Type* get_double() const noexcept;

        const Type* get_type(std::string_view) const noexcept;
        bool has_type(std::string_view) const noexcept;
    };
}
