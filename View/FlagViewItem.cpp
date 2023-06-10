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
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::View
{
    FlagViewItem::FlagViewItem(const bool on, const int index, const QString& toolTip, QWidget* parent) :
        CustomView(parent),
        _index(index)
    {
        if (on) _state |= ON;
        setToolTip(toolTip);
        construct();
    }

    void FlagViewItem::construct()
    {
        constructView();
        setMargin(0);
        setPadding(0);
        setFlags(CvFullView);
        setMinimumSize(Metrics::iconMin);
        _background = Colors::CtrlBackground;
        _accent = Colors::Accent;
    }

    void FlagViewItem::setState(const bool state)
    {
        if (state)
            _state |= ON;
        else
            _state &= ~ON;
        refresh();
    }

    void FlagViewItem::setAccentColor(const QColor& col)
    {
        _accent = col;
        refresh();
    }

    void FlagViewItem::setBackgroundColor(const QColor& col)
    {
        _background = col;
        refresh();
    }

    void FlagViewItem::render(QPainter& paint, const QRectF& rect)
    {
        if (!isOn())
        {
            if (_state & ENTER)
            {
                paint.fillRect(rect, Colors::up(_background));
                paint.setPen(QPen(_accent, 1));
                paint.drawRect(rect.adjusted(1, 1, -1, -1));
            }
            else
            {
                paint.fillRect(rect, Colors::down(_background));
            }
        }
        else
        {
            QLinearGradient g;
            g.setStart(rect.topLeft());
            g.setFinalStop(rect.bottomRight());

            g.setColorAt(0, Colors::shadow(_accent));
            g.setColorAt(1, Colors::highlight(_accent));
            paint.fillRect(rect, g);

            if (_state & ENTER)
            {
                paint.setPen(QPen(_accent, 1));
                paint.drawRect(rect.adjusted(1, 1, -1, -1));
            }
            else
            {
                paint.setPen(QPen(Colors::up(_background), 1));
                paint.drawRect(rect.adjusted(1, 1, -1, -1));
            }
        }
    }

    void FlagViewItem::mousePressEvent(QMouseEvent* event)
    {
        _state |= PRESSED;
        _state &= ~RELEASED;
    }

    void FlagViewItem::mouseReleaseEvent(QMouseEvent* event)
    {
        _state &= ~PRESSED;
        _state |= RELEASED;
        refresh();

        if (event->button() == Qt::LeftButton)
        {
            QRectF rect;
            rect.setTopLeft(mapFromParent(geometry().topLeft()));
            rect.setBottomRight(mapFromParent(geometry().bottomRight()));

            if (const QPointF pt = event->position();
                rect.contains(Qmc::point(pt)))
            {
                if (isOn())
                    _state &= ~ON;
                else
                    _state |= ON;

                emit stateChanged(isOn(), _index);
            }
        }
    }

    void FlagViewItem::enterEvent(QEnterEvent* event)
    {
        _state |= ENTER;
        update();
    }

    void FlagViewItem::leaveEvent(QEvent* event)
    {
        _state &= ~ENTER;
        update();
    }

}  // namespace Rt2::View
