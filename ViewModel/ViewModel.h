/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
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

        void dispatchInput()
        {
            for (const auto& input : _inputs)
                input(_model.value());
        }

        void dispatchOutput()
        {
            for (const auto& output : _outputs)
                output(_model.value());
        }

        void invoke(const Direction dir)
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
            case NONE:
            default:  // nadda
                break;
            }
            _callLock = false;
        }

    private:
        ViewModel(const SelfType& rhs) :
            _inputs(rhs._inputs),
            _outputs(rhs._outputs),
            _model(rhs._model)
        {
        }

        SelfType& operator=(const SelfType& rhs)
        {
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

        explicit ViewModel(const T& v)
        {
            _model.setValue(v);
        }

        virtual ~ViewModel()
        {
            clear();
        }

        void setValue(const T& val, Direction dir = INPUT)
        {
            if (_model.setValue(val))
                invoke(dir);
        }

        const T& value() const
        {
            return _model.value();
        }

        T& ref()
        {
            return _model.ref();
        }

        void addInput(const Observer& ot)
        {
            _inputs.push_back(ot);
        }

        void addOutput(const Observer& ot)
        {
            _outputs.push_back(ot);
        }

        void clear()
        {
            _inputs.clear();
            _outputs.clear();
        }

        void dispatch(const Direction& dir)
        {
            invoke(dir);
        }
    };

    template <>
    class ViewModel<void>
    {
    public:
        using Observer  = std::function<void()>;
        using Observers = SimpleArray<Observer>;
        using SelfType  = ViewModel<void>;

    protected:
        Observers _inputs;
        Observers _outputs;
        bool      _callLock{false};

        void dispatchInput()
        {
            for (const auto& input : _inputs)
                input();
        }

        void dispatchOutput()
        {
            for (const auto& output : _outputs)
                output();
        }

        void invoke(const Direction dir)
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
            case NONE:
            default:  // nadda
                break;
            }
            _callLock = false;
        }

    private:
        ViewModel(const SelfType& rhs) :
            _inputs(rhs._inputs),
            _outputs(rhs._outputs)
        {
        }

        SelfType& operator=(const SelfType& rhs)
        {
            if (&rhs != this)
            {
                _inputs  = rhs._inputs;
                _outputs = rhs._outputs;
            }
            return *this;
        }

    public:
        ViewModel() = default;
        virtual ~ViewModel()
        {
            clear();
        }

        void setValue(const Direction dir = INPUT)
        {
            invoke(dir);
        }

        void addInput(const Observer& ot)
        {
            _inputs.push_back(ot);
        }

        void addOutput(const Observer& ot)
        {
            _outputs.push_back(ot);
        }

        void clear()
        {
            _inputs.clear();
            _outputs.clear();
        }

        void dispatch(const Direction& dir)
        {
            invoke(dir);
        }
    };

    template <typename T>
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
