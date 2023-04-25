#include "View/IconButtonView.h"
#include <qevent.h>
#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QWidget>
#include "StyleSheetWriter.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::View
{

    IconButtonView::IconButtonView(IconMap icon, QWidget* parent) :
        View(parent)
    {
        construct(icon);
    }

    void IconButtonView::construct(const IconMap icon)
    {
        _button = new QLabel(this);
        constructView(_button);
        setPadding(0);
        setBorder(0);
        setBackgroundColor(Colors::Transparent);
        setMinimumSize(Metrics::iconPadding);
        setMaximumSize(Metrics::iconPadding);

        _button->setFont(Qu::iconFont());

        StyleSheetWriter ssw;
        ssw.backgroundColor(Colors::CtrlBackground);
        _button->setStyleSheet(ssw.toString());

        _button->setFrameShape(QFrame::Shape::NoFrame);

        _button->setText(QChar(icon));
        _button->setAlignment(Qt::AlignCenter);
        _button->setMinimumSize(Metrics::iconMin);
    }

    void IconButtonView::mousePressEvent(QMouseEvent* event)
    {
        _state |= PRESSED;
        _state &= ~RELEASED;
        refresh();

        StyleSheetWriter ssw;
        ssw.noBackground();
        ssw.noBorder();
        ssw.color(Colors::ForegroundLight.lighter(200));
        _button->setStyleSheet(ssw.toString());
    }

    void IconButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        _state &= ~PRESSED;
        _state |= RELEASED;
        refresh();

        if (event->button() == Qt::LeftButton)
        {
            QPoint pt = Qmc::point(event->position());

            if (geometry().contains(pt) || _button->geometry().contains(pt))
                emit clicked();
        }
    }

    void IconButtonView::enterEvent(QEnterEvent* event)
    {
        _state |= ENTER;
        refresh();

        StyleSheetWriter ssw;
        ssw.noBackground();
        ssw.border(_highlight.darker(), 1);
        ssw.color(_highlight.lighter(200));
        _button->setStyleSheet(ssw.toString());
    }

    void IconButtonView::leaveEvent(QEvent* event)
    {
        _state &= ~ENTER;
        refresh();
        StyleSheetWriter ssw;
        ssw.backgroundColor(Colors::CtrlBackground);
        _button->setStyleSheet(ssw.toString());
    }
    
}  // namespace Rt2::View
