#include "View/ViewConstructor.h"
#include <QApplication>

namespace Rt2::View
{
    ViewConstructor::ViewConstructor(QObject* receiver) :
        _receiver(receiver)
    {
    }

    void ViewConstructor::dispatch(QObject* receiver, const int code)
    {
        if (code < ViewConstructorStart || code > ViewConstructorStop) return;

        RT_GUARD_VOID(receiver)
        QApplication::postEvent(
            receiver,
            new ViewConstructorEvent(code),
            code == ViewConstructorStop ? Qt::LowEventPriority : Qt::HighEventPriority);
    }

    void ViewConstructor::update()
    {
        RT_GUARD_VOID(_receiver)

        dispatch(ViewConstructorStart);
        while (isRunning())
        {
            if (sync()) break;

            if (const auto obj = construct())
                dispatch(obj);
            else
                break;
        }
        dispatch(ViewConstructorStop);
    }

    void ViewConstructor::dispatch(ConstructorObject* obj) const
    {
        RT_GUARD_VOID(_receiver)
        QApplication::postEvent(
            _receiver, 
            new ViewConstructorEvent(obj), 
            Qt::NormalEventPriority);
    }

    void ViewConstructor::dispatch(const int code) const
    {
        dispatch(_receiver, code);
    }

    bool ViewConstructor::sync()
    {
        return !isRunningUnlocked();
    }
}  // namespace Rt2::View
