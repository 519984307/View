#include "View/IconButtonView.h"
#include <qevent.h>
#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QWidget>
#include "Palette.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::View
{

    IconButtonView::IconButtonView(IconMap icon, QWidget* parent) :
        View(parent)
    {
        setUpdatesEnabled(true);
        setMouseTracking(true);

        _button = new QLabel(this);
        construct(icon);
    }

    void IconButtonView::construct(const IconMap icon)
    {
        constructView(_button);
        setBackgroundColor(Colors::Transparent);
        setBorderColor(Colors::Transparent);
        setMinimumSize(Metrics::iconMin);

        _button->setUpdatesEnabled(true);
        _button->setFont(Qu::iconFont());
        _button->setText(QChar(icon));
        _button->setAlignment(Qt::AlignCenter);
        _button->setMinimumSize(Metrics::iconMin);
    }

    void IconButtonView::mousePressEvent(QMouseEvent* event)
    {
        _state |= PRESSED;
        _state &= ~RELEASED;
        refresh();
    }

    void IconButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        _state &= ~PRESSED;
        _state |= RELEASED;
        refresh();

        if (event->button() == Qt::LeftButton)
        {
            if (geometry().contains(QPoint(event->x(), event->y())))
                emit clicked();
        }
    }

    void IconButtonView::enterEvent(QEnterEvent* event)
    {
        _state |= ENTER;
        refresh();
    }

    void IconButtonView::leaveEvent(QEvent* event)
    {
        _state &= ~ENTER;
        refresh();
    }

    void IconButtonView::paintEvent(QPaintEvent* event)
    {
        QPainter paint(this);
        paint.setRenderHint(QPainter::Antialiasing);

        QRectF ctx = {0, 0, (qreal)width(), (qreal)height()};

        ctx = ctx.marginsRemoved(contentsMargins());

        QLinearGradient gradient(ctx.topLeft(), ctx.bottomLeft());
        if (_state & PRESSED)
        {
            gradient.setColorAt(0.0, Colors::G00);
            gradient.setColorAt(0.8, Colors::CtrlBackgroundLight);
            gradient.setColorAt(1.0, Colors::Ac11);
        }
        else
        {
            gradient.setColorAt(0.0, Colors::Border);
            gradient.setColorAt(1.0, Colors::CtrlBackgroundLight);
        }

        paint.fillRect(ctx, gradient);

        if (_state & ENTER)
        {
            paint.setPen(QPen(Colors::BorderLight, 1));
            paint.drawRect(ctx);
        }
        else
        {
            paint.setPen(QPen(Colors::Border, 1));
            paint.drawRect(ctx);
        }
    }
}  // namespace Rt2::View
