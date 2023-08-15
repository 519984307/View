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

    enum ViewConstructorSubCode
    {
        ViewConstructorStart,    // High 
        ViewConstructorRestart,  // 
        ViewConstructorData,     // Medium
        ViewConstructorStop,     // Low, => [H, M...M, L]
    };

    class ViewConstructorEvent final : public QEvent
    {
    private:
        ConstructorObject* _object{nullptr};  // is owner
        int                _subCode{ViewConstructorStart};

    public:
        explicit ViewConstructorEvent(const int subCode = ViewConstructorStart) :
            QEvent((Type)ViewConstructorEventCode),
            _subCode{subCode}
        {
        }

        explicit ViewConstructorEvent(ConstructorObject* obj, const int subCode = ViewConstructorData) :  // passes ownership
            QEvent((Type)ViewConstructorEventCode),
            _object(obj),
            _subCode{subCode}
        {
        }

        ~ViewConstructorEvent() override
        {
            delete _object;
            _object = nullptr;
        }

        int subCode() const { return _subCode; }

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

        void dispatch(int code) const;

    public:
        explicit ViewConstructor(QObject* receiver);
        ~ViewConstructor() override = default;

        virtual ConstructorObject* construct() = 0;

        static void dispatch(QObject* receiver, int code);
    };

}  // namespace Rt2::View
