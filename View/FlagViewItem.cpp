#include "FlagViewItem.h"
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include "Colors.h"
#include "Metrics.h"
#include "Qu.h"

namespace Rt2::View
{
    FlagViewItem::FlagViewItem(const bool on, int index, QWidget* parent) :
        CustomView(parent),
        _index(index)
    {
        if (on)
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

    void FlagViewItem::setState(bool state)
    {
        if (state)
            _state |= ON;
        else
            _state &= ~ON;
        refresh();
    }

    void FlagViewItem::render(QPainter& paint, const QRectF& rect)
    {
        if (!isOn())
        {
            if (_state & ENTER)
            {
                paint.fillRect(rect, Colors::CtrlBackgroundLight.darker(Colors::Drk030));
                paint.setPen(QPen(Colors::Accent, 1));
                paint.drawRect(rect.adjusted(1, 1, -1, -1));
            }
            else
            {
                paint.fillRect(rect, Colors::CtrlBackgroundLight.lighter(Colors::Lgt020));
                paint.setPen(QPen(Colors::BorderLight, 1));
                paint.drawRect(rect.adjusted(1, 1, -1, -1));
            }
        }
        else
        {
            QLinearGradient g;
            g.setStart(rect.topLeft());
            g.setFinalStop(rect.bottomRight());

            g.setColorAt(0, Colors::CtrlBackground.darker(Colors::Drk070));
            g.setColorAt(1, Colors::CtrlBackground.darker(Colors::Drk010));
            paint.fillRect(rect, g);

            if (_state & ENTER)
            {
                paint.setPen(QPen(Colors::Accent, 1));
                paint.drawRect(rect.adjusted(1, 1, -1, -1));
            }
            else
            {
                paint.setPen(QPen(Colors::BorderLight, 1));
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
