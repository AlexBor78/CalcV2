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

    const Type* TypeTable::get_int() const
    {
        return table.at("int").get();
    }

    const Type* TypeTable::get_type(std::string_view name) const
    {
        auto type = table.find(name);
        if(type != table.end())
        {
            return type->second.get();
        }
        return nullptr;
    }

    bool TypeTable::has_type(std::string_view name) const
    {
        return get_type(name) != nullptr;
    }
    
}
