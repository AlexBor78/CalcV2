#include <runtime/value.h>

namespace Calc::runtime
{
    int IntValue::get_value() const noexcept
    {
        return value;
    }

    void IntValue::accept(ConstValueVisitor* visitor) const noexcept
    {
        visitor->visit_intvalue(*this);
    }

    void IntValue::accept(MutValueVisitor* visitor) noexcept
    {
        visitor->visit_intvalue(*this);
    }

    void Value::accept(ConstValueVisitor* visitor) const noexcept
    {
        value->accept(visitor);
    }

    void Value::accept(MutValueVisitor* visitor) noexcept
    {
        value->accept(visitor);
    }
}
