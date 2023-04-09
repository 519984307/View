#pragma once
#include "Utils/Array.h"

namespace Rt2::ViewModel
{
    enum ObserverOption
    {
        INPUT = 0,
        OUTPUT,
        BOTH,
    };

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

        void dispatchInput()
        {
            for (const auto ofn : _inputs)
                ofn(_data);
        }

        void dispatchOutput()
        {
            for (const auto ofn : _outputs)
                ofn(_data);
        }

    public:
        Model() = default;
        ~Model() { clear(); }

        void setValue(int direction, const T& val);

        const T& value() const;

        void addInput(const ObserverType& ot);

        void addOutput(const ObserverType& ot);

        void clear();
    };

    template <typename T>
    void Model<T>::setValue(const int direction, const T& val)
    {
        if (_callLock)
            return;

        _data = val;
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
    const T& Model<T>::value() const
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

    template <typename T>
    class ViewModel
    {
    public:
        using ModelType    = Model<T>;
        using ObserverType = typename ModelType::ObserverType;

    protected:
        ModelType _model;

    public:
        ViewModel()
        {
        }

        virtual ~ViewModel()
        {
            _model.clear();
        }

        void setValue(int direction, const T& val)
        {
            _model.setValue(direction, val);
        }

        const T& value() const
        {
            return _model.value();
        }

        void addInput(const ObserverType& ot)
        {
            _model.addInput(ot);
        }

        void addOutput(const ObserverType& ot)
        {
            _model.addOutput(ot);
        }

        void setOption(const int op)
        {
            _model.setOption(op);
        }

        void clear()
        {
            _model.clear();
        }
    };

}  // namespace Rt2::ViewModel
