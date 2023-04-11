#pragma once

namespace Rt2::ViewModel
{
    template <typename T>
    class VoidMethod
    {
    public:
        using InstanceType = T;
        typedef void (InstanceType::*MethodType)();

    private:
        MethodType    _method{nullptr};
        InstanceType* _self{nullptr};

    public:
        VoidMethod() = default;

        void bind(InstanceType* self, MethodType ot)
        {
            _self   = self;
            _method = ot;
        }

        void operator()()
        {
            if (_self && _method)
                (_self->*_method)();
        }
    };

    template <typename T, typename Arg>
    class Method
    {
    public:
        using InstanceType = T;
        typedef void (InstanceType::*MethodType)(const Arg&);

    private:
        MethodType    _method{nullptr};
        InstanceType* _self{nullptr};

    public:
        Method() = default;

        void bind(InstanceType* self, MethodType ot)
        {
            _self   = self;
            _method = ot;
        }

        void operator()(const Arg& arg)
        {
            if (_self && _method)
                (_self->*_method)(arg);
        }
    };
}  // namespace Rt2::ViewModel
