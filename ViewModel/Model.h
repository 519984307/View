#pragma once

namespace Rt2::ViewModel
{
    enum Direction
    {
        INPUT = 0,
        OUTPUT,
        BOTH,
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

        void setValue(const T& val);

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
    void Model<T>::setValue(const T& val)
    {
        _data = val;
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
