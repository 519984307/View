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
#include "View/FlagViewItem.h"
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include "States/Flag.h"
#include "View/Qu.h"

namespace Rt2::View
{
    FlagViewItem::FlagViewItem(const bool on, const int index, const QString& toolTip, QWidget* parent) :
        View(parent, new Visual::Flag(), VisualFlag::HoverState | VisualFlag::ApplyOnShow),
        _index(index)
    {
        setToolTip(toolTip);
        construct();
        setState(on);
    }

    void FlagViewItem::construct()
    {
        _box = Style::Widget::iconLabel(IconNone, Style::Icon::Normal, Style::Icon::Bounds);
        constructView(_box);

        setMinimumSize(Style::Icon::Bounds);
        setMaximumSize(Style::Icon::Bounds);
    }

    bool FlagViewItem::isOn() const
    {
        RT_GUARD_CHECK_RET(_viewStates, false)
        return _viewStates->isToggleOn();
    }

    void FlagViewItem::setState(const bool state) const
    {
        RT_GUARD_CHECK_VOID(_viewStates && _box)

        _viewStates->setAttribute(VisualAttribute::ToggleOn, state);
        if (state)
            _box->setText(QChar(IconFlagOn));
        else
            _box->setText(QChar(IconFlagOff));
    }

    void FlagViewItem::mousePressEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(_viewStates && event)

        if (event->button() == Qt::LeftButton)
            apply(VisualType::Pressed);
    }

    void FlagViewItem::mouseReleaseEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(_box && event)

        if (event->button() == Qt::LeftButton)
        {
            QRectF rect;
            rect.setTopLeft(mapFromParent(geometry().topLeft()));
            rect.setBottomRight(mapFromParent(geometry().bottomRight()));

            if (const QPointF pt = event->position();
                rect.contains(Qmc::point(pt)) ||
                _box->geometry().contains(Qmc::point(pt)))
            {
                setState(!isOn());
                apply(VisualType::Normal);

                emit stateChanged(isOn(), _index);
            }
        }
    }

}  // namespace Rt2::View
