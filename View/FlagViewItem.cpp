#include "FlagViewItem.h"
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include "Colors.h"
#include "Metrics.h"
#include "Qu.h"

namespace Rt2::View
{
    FlagViewItem::FlagViewItem(bool state, QWidget* parent) :
        CustomView(parent)
    {
        if (state)
            _state |= ON;
        construct();
    }

    void FlagViewItem::construct()
    {
        constructView();
        setMargin(0);
        setPadding(0);
        setFlags(CvFullView);
        setMinimumSize(Metrics::iconPadding);
        update();
    }

    void FlagViewItem::render(QPainter& paint, const QRectF& rect)
    {
        if (!isOn())
        {
            QLinearGradient g;
            g.setStart(rect.topLeft());
            g.setFinalStop(rect.bottomLeft());

            g.setColorAt(0, Colors::CtrlBackground.darker(Colors::Drk030));
            g.setColorAt(1, Colors::CtrlBackground.darker(Colors::Drk010));

            if (_state & ENTER)
            {
                paint.fillRect(rect, g);
                paint.setPen(QPen(Colors::Accent, 1));
                paint.drawRect(rect.adjusted(1, 1, -1, -1));
            }
            else
                paint.fillRect(rect, Colors::CtrlBackgroundLight);
        }
        else
        {
            QLinearGradient g;
            g.setStart(rect.topLeft());
            g.setFinalStop(rect.bottomLeft());

            g.setColorAt(0, Colors::Accent.darker(Colors::Drk040));
            g.setColorAt(1, Colors::Accent.darker(Colors::Drk010));

            if (_state & ENTER)
            {
                paint.setPen(QPen(Colors::Accent, 1));
                paint.drawRect(rect.adjusted(1, 1, -1, -1));
            }
            else
                paint.fillRect(rect, g);
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
