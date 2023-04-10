#pragma once

namespace Rt2::ViewModel
{
    template <typename T, typename D>
    class Method
    {
    public:
        using InstanceType = T;
        using DataType     = D;
        typedef void (InstanceType::*ObserverType)(const DataType&);

    private:
        ObserverType _method{nullptr};

    public:
        Method() = default;

        void bind(ObserverType ot)
        {
            _method = ot;
        }

        void operator()(InstanceType* self, const DataType& type)
        {
            if (self)
                (self->*_method)(type);
        }
    };

}  // namespace Rt2::ViewModel
