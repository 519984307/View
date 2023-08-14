#include "View/ViewConstructor.h"
#include <QApplication>

namespace Rt2::View
{
    ViewConstructor::ViewConstructor(QObject* receiver) :
        _receiver(receiver)
    {
    }

    void ViewConstructor::update()
    {
        RT_GUARD_VOID(_receiver)

        while (isRunning())
        {
            if (sync()) break;

            if (const auto obj = construct())
                dispatch(obj);
            else
                break;
        }
    }

    void ViewConstructor::dispatch(ConstructorObject* obj) const
    {
        RT_GUARD_VOID(_receiver)
        QApplication::postEvent(_receiver, new ViewConstructorEvent(obj));
    }

    bool ViewConstructor::sync()
    {
        if (isRunning())
        {
            Thread::Thread::yield();
            return false;
        }
        return true;
    }

}  // namespace Rt2::View
