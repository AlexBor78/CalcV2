#include <runtime/value.h>
#include <runtime/vtables.h>

namespace Calc::runtime
{
    Value ValueFactory::make_int(int v)
    {
        return std::move(Value(
            static_cast<void*>(new int(v)), 
            get_int_vtable())
        );
    }

    Value ValueFactory::make_double(double v)
    {
        return std::move(Value(
            static_cast<void*>(new double(v)), 
            get_double_vtable())
        );
    }

    Value::Value(void* v, const ValueVTable* vt):
        value(v),
        vtable(vt)
    {}

    Value::Value(Value& other):
        value(other.value),
        vtable(other.vtable){
        other.value = nullptr;
    }

    Value::Value(Value&& other):
        value(other.value),
        vtable(other.vtable){
        other.value = nullptr;
    }

    Value::~Value()
    {
        vtable->destroy(value);
    }

    const ValueVTable* Value::promote(const Value& v) const
    {
        return vtable->promote(v.get_vtable());
    }

    Value Value::cast(const ValueVTable* vt) const
    {
        return vtable->cast(*this, vt);
    }

    Value Value::copy() const
    {
        return vtable->copy(*this);
    }

    bool Value::equals(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->equals(*this, v);
        }
        auto nvt = promote(v);
        return nvt->equals(cast(nvt), v.cast(nvt));
    }
    bool Value::operator==(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->equals(*this, v);
        }
        auto nvt = promote(v);
        return nvt->equals(cast(nvt), v.cast(nvt));
    }

    bool Value::notequals(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->notequals(*this, v);
        }
        auto nvt = promote(v);
        return nvt->notequals(cast(nvt), v.cast(nvt));
    }
    bool Value::operator!=(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->notequals(*this, v);
        }
        auto nvt = promote(v);
        return nvt->notequals(cast(nvt), v.cast(nvt));
    }

    Value Value::add(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->add(*this, v);
        }
        auto nvt = promote(v);
        return nvt->add(cast(nvt), v.cast(nvt));
    }
    Value Value::operator+(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->add(*this, v);
        }
        auto nvt = promote(v);
        return nvt->add(cast(nvt), v.cast(nvt));
    }

    Value Value::sub(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->sub(*this, v);
        }
        auto nvt = promote(v);
        return nvt->sub(cast(nvt), v.cast(nvt));
    }
    Value Value::operator-(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->sub(*this, v);
        }
        auto nvt = promote(v);
        return nvt->sub(cast(nvt), v.cast(nvt));
    }

    Value Value::mul(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->mul(*this, v);
        }
        auto nvt = promote(v);
        return nvt->mul(cast(nvt), v.cast(nvt));
    }
    Value Value::operator*(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->mul(*this, v);
        }
        auto nvt = promote(v);
        return nvt->mul(cast(nvt), v.cast(nvt));
    }

    Value Value::div(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->div(*this, v);
        }
        auto nvt = promote(v);
        return nvt->div(cast(nvt), v.cast(nvt));
    }
    Value Value::operator/(const Value& v) const
    {
        if(vtable == v.get_vtable())
        {
            return vtable->div(*this, v);
        }
        auto nvt = promote(v);
        return nvt->div(cast(nvt), v.cast(nvt));
    }

    Value Value::inverse() const
    {
        return vtable->inverse(*this);
    }
    Value Value::operator-() const
    {
        return vtable->inverse(*this);
    }

    void Value::print() const
    {
        vtable->print(*this);
    }

    std::string_view Value::get_name() const noexcept
    {
        return vtable->name;
    }

    const ValueVTable* Value::get_vtable() const noexcept
    {
        return vtable;
    }
    
    void* Value::get_raw() noexcept
    {
        return value;
    }

    const void* Value::get_raw() const noexcept
    {
        return value;
    }
}
