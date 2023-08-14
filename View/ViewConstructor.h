#pragma once
#include "EventHelpers.h"
#include "Thread/Runner.h"

namespace Rt2::View
{
    class ConstructorObject
    {
    private:
        int _id{-1};

    public:
        virtual ~ConstructorObject() = default;

        explicit ConstructorObject(const int id) :
            _id{id}
        {
        }

        int id() const { return _id; }

        virtual ConstructorObject* clone() = 0;
    };

    constexpr int ViewConstructorEventCode = EC_006;

    class ViewConstructorEvent final : public QEvent
    {
    private:
        ConstructorObject* _object{nullptr};  // is owner

    public:
        ViewConstructorEvent() :
            QEvent((Type)ViewConstructorEventCode)
        {
        }

        explicit ViewConstructorEvent(ConstructorObject* obj) :  // passes ownership
            QEvent((Type)ViewConstructorEventCode),
            _object(obj)
        {
        }

        ~ViewConstructorEvent() override
        {
            delete _object;
            _object = nullptr;
        }

        ConstructorObject* object() const
        {
            return _object;
        }

        template <typename T>
        T* cast() const
        {
            return (T*)_object;
        }
    };

    class ViewConstructor : public Thread::Runner
    {
    private:
        QObject* _receiver{nullptr};

    protected:
        bool sync();

    private:
        void update() override;

        void dispatch(ConstructorObject*) const;

    public:
        explicit ViewConstructor(QObject* receiver);
        ~ViewConstructor() override = default;

        virtual ConstructorObject* construct() = 0;
    };

}  // namespace Rt2::View
