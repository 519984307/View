#pragma once
#include "Utils/Array.h"

namespace Rt2::ViewModel
{
    enum ObserverDirection
    {
        INPUT = 0,
        OUTPUT,
        BOTH,
    };

    template <typename T>
    class Model
    {
    public:
        using ObserverType = std::function<void(const T&)>;
        using Observers    = SimpleArray<ObserverType>;

    private:
        Observers _inputs;
        Observers _outputs;
        bool      _callLock{false};
        T         _data{};

        void dispatchInput();

        void dispatchOutput();

    public:
        Model() = default;
        ~Model() { clear(); }

        void setValue(const T& val, ObserverDirection direction);

        const T& value() const;

        T& ref();

        void addInput(const ObserverType& ot);

        void addOutput(const ObserverType& ot);

        void clear();
    };

    template <typename T>
    void Model<T>::setValue(const T& val, const ObserverDirection direction)
    {
        _data = val;

        if (_callLock)
            return;

        switch (direction)
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
    void Model<T>::dispatchInput()
    {
        for (const auto& input : _inputs)
            input(_data);
    }

    template <typename T>
    void Model<T>::dispatchOutput()
    {
        for (const auto output : _outputs)
            output(_data);
    }

    template <typename T>
    const T& Model<T>::value() const
    {
        return _data;
    }

    template <typename T>
    T& Model<T>::ref()
    {
        return _data;
    }

    template <typename T>
    void Model<T>::addInput(const ObserverType& ot)
    {
        _inputs.push_back(ot);
    }

    template <typename T>
    void Model<T>::addOutput(const ObserverType& ot)
    {
        _outputs.push_back(ot);
    }

    template <typename T>
    void Model<T>::clear()
    {
        _inputs.clear();
        _outputs.clear();
    }

}  // namespace Rt2::ViewModel
