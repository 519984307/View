#pragma once
#include "Utils/Array.h"
#include "ViewModel/Model.h"

namespace Rt2::ViewModel
{
    template <typename T>
    class ViewModel
    {
    public:
        using ModelType    = Model<T>;
        using ObserverType = typename ModelType::ObserverType;

    protected:
        ModelType _model{};

    public:
        ViewModel() = default;

        virtual ~ViewModel();

        void setValue(const T& val, ObserverDirection direction = INPUT);

        const T& value() const;

        T& ref();

        void addInput(const ObserverType& ot);

        void addOutput(const ObserverType& ot);
        
        void clear();
    };

    template <typename T>
    ViewModel<T>::~ViewModel()
    {
        _model.clear();
    }

    template <typename T>
    void ViewModel<T>::setValue(const T& val, ObserverDirection direction)
    {
        _model.setValue(val, direction);
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
    void ViewModel<T>::addInput(const ObserverType& ot)
    {
        _model.addInput(ot);
    }

    template <typename T>
    void ViewModel<T>::addOutput(const ObserverType& ot)
    {
        _model.addOutput(ot);
    }

    template <typename T>
    void ViewModel<T>::clear()
    {
        _model.clear();
    }

}  // namespace Rt2::ViewModel
