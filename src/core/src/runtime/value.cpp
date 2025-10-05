#include <runtime/value.h>

namespace Calc::runtime
{
    Value ValueFactory::make_int(int v)
    {
        int *buf = new int(v);
        return std::move(Value(static_cast<void*>(buf), &INT_VTABLE));
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

    Value Value::add(const Value& v)
    {
        return vtable->add(*this, v);
    }

    Value Value::sub(const Value& v)
    {
        return vtable->sub(*this, v);
    }

    Value Value::mul(const Value& v)
    {
        return vtable->mul(*this, v);
    }

    Value Value::div(const Value& v)
    {
        return vtable->div(*this, v);
    }

    Value Value::inverse()
    {
        return vtable->inverse(*this);
    }

    void Value::print()
    {
        vtable->print(*this);
    }

    template <class T>
    const T& Value::as() const
    {
        return *static_cast<T*>(value);
    }

    std::string_view Value::get_name() const noexcept
    {
        return vtable->name;
    }
}
