#pragma once

#include <memory>

namespace Calc::runtime
{
    class ConstValueVisitor;
    class MutValueVisitor;

    class IValue
    {
    protected:
        IValue() = default;
    public:
        virtual void accept(ConstValueVisitor*) const noexcept = 0;
        virtual void accept(MutValueVisitor*) noexcept = 0;
    };

    class IntValue : IValue
    {
    private:
        int value;
    public:
        IntValue() = delete;
        explicit IntValue(int v): value(v) {}
        virtual void accept(ConstValueVisitor*) const noexcept override;
        virtual void accept(MutValueVisitor*) noexcept override;

        int get_value() const noexcept;
    };

    class Value
    {
    private:
        std::unique_ptr<IValue> value;
    public:
        void accept(ConstValueVisitor*) const noexcept;
        void accept(MutValueVisitor*) noexcept;
    };

    class ConstValueVisitor
    {
    protected:
        ConstValueVisitor() = default;
    public:
        virtual void visit_intvalue(const IntValue&) = 0;
    };

    class MutValueVisitor
    {
    protected:
        MutValueVisitor() = default;
    public:
        virtual void visit_intvalue(IntValue&) = 0;
    };
}
