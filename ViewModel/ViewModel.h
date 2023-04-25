#pragma once
#include "Utils/Array.h"
#include "ViewModel/Model.h"

namespace Rt2::ViewModel
{
    template <typename T>
    class ViewModel
    {
    public:
        using Observer  = std::function<void(const T&)>;
        using Observers = SimpleArray<Observer>;
        using ModelType = Model<T>;
        using SelfType  = ViewModel<T>;

    protected:
        Observers _inputs;
        Observers _outputs;
        ModelType _model{};
        bool      _callLock{false};

        void dispatchInput();

        void dispatchOutput();

        T& ref();

        void invoke(Direction dir);

    private:
        ViewModel(const SelfType& rhs) :
            _inputs(rhs._inputs),
            _outputs(rhs._outputs),
            _model(rhs._model)
        {
            // For now, don't allow explicit copy
        }

        SelfType& operator=(const SelfType& rhs)
        {
            // For now, don't allow explicit assignment

            if (&rhs != this)
            {
                _inputs  = rhs._inputs;
                _outputs = rhs._outputs;
                _model   = rhs._model;
            }
            return *this;
        }

    public:
        ViewModel() = default;
        explicit ViewModel(const T& v);
        virtual  ~ViewModel();

        void setValue(const T&  val,
                      Direction dir = INPUT);

        const T& value() const;

        void addInput(const Observer& ot);

        void addOutput(const Observer& ot);

        void clear();
    };

    template <typename T>
    ViewModel<T>::ViewModel(const T& v)
    {
        _model.setValue(v);
    }

    template <typename T>
    ViewModel<T>::~ViewModel()
    {
        clear();
    }

    template <typename T>
    void ViewModel<T>::dispatchInput()
    {
        for (const auto& input : _inputs)
            input(_model.value());
    }

    template <typename T>
    void ViewModel<T>::dispatchOutput()
    {
        for (const auto &output : _outputs)
            output(_model.value());
    }

    template <typename T>
    void ViewModel<T>::setValue(const T& val, const Direction dir)
    {
        _model.setValue(val);
        invoke(dir);
    }

    template <typename T>
    const T& ViewModel<T>::value() const
    {
        return _model.value();
    }

    template <typename T>
    T& ViewModel<T>::ref()
    {
        return _model.ref();
    }

    template <typename T>
    void ViewModel<T>::invoke(const Direction dir)
    {
        if (_callLock)
            return;

        switch (dir)
        {
        case INPUT:  // src to data
            _callLock = true;
            dispatchInput();
            break;
        case OUTPUT:  // data to src
            _callLock = true;
            dispatchOutput();
            break;
        case BOTH:
            _callLock = true;
            dispatchInput();
            dispatchOutput();
            break;
        default:  // nadda
            break;
        }
        _callLock = false;
    }

    template <typename T>
    void ViewModel<T>::addInput(const Observer& ot)
    {
        _inputs.push_back(ot);
    }

    template <typename T>
    void ViewModel<T>::addOutput(const Observer& ot)
    {
        _outputs.push_back(ot);
    }

    template <typename T>
    void ViewModel<T>::clear()
    {
        _inputs.clear();
        _outputs.clear();
    }

    template <typename  T>
    using TFunction = std::function<void(const T&)>;


    template <typename T>
    class FunctionViewModel final : public ViewModel<TFunction<T>>
    {
    public:
        void dispatch(const T& v, Direction dir = INPUT)
        {
            if (const TFunction<T>& function = this->value())
            {
                function(v);
                this->invoke(dir);
            }
        }
    };

    using VoidFunction = std::function<void()>;

    class VoidFunctionViewModel final : public ViewModel<VoidFunction>
    {
    public:
        void dispatch(const Direction dir = INPUT)
        {
            if (const VoidFunction& function = this->value())
            {
                function();
                invoke(dir);
            }
        }
    };
}  // namespace Rt2::ViewModel
