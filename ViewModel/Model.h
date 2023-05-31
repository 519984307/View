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

namespace Rt2::ViewModel
{
    enum Direction
    {
        INPUT = 0,
        OUTPUT,
        BOTH,
        NONE,
    };

    template <typename T>
    class ViewModel;

    template <typename T>
    class Model
    {
    public:
        using SelfType = Model<T>;

    private:
        T _data{};

        friend class ViewModel<T>;

        bool setValue(const T& val);

        T& ref();

        Model(const SelfType& rhs) :
            _data{rhs._data}
        {
            // For now, don't allow explicit copy
        }

        SelfType& operator=(const SelfType& rhs)
        {
            // For now, don't allow explicit assignment
            if (&rhs != this)
                _data = rhs._data;
            return *this;
        }

    public:
        Model() = default;

        const T& value() const;
    };

    template <typename T>
    [[nodiscard]] bool Model<T>::setValue(const T& val)
    {
        if (_data != val)  // may require an operator
        {
            _data = val;
            return true;
        }
        return false;
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

}  // namespace Rt2::ViewModel
