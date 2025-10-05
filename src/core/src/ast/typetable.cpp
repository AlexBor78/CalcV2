#include <ast/typetable.h>

namespace Calc::ast
{
    void TypeTable::init_builtin()
    {
        table["int"] = std::make_unique<IntType>();
    }

    TypeTable::TypeTable()
    {
        init_builtin();
    }

    const Type* TypeTable::get_int() const noexcept
    {
        return table.at("int").get();
    }

    const Type* TypeTable::get_type(std::string_view name) const noexcept
    {
        auto type = table.find(name);
        if(type != table.end())
        {
            return type->second.get();
        }
        return nullptr;
    }

    bool TypeTable::has_type(std::string_view name) const noexcept
    {
        return get_type(name) != nullptr;
    }    
}
