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

    class IconButtonStates
    {
    private:
        QString _active;
        QString _inactive;
        QString _pressed;

    public:
        IconButtonStates();

        void active(QLabel* label) const;
        void inactive(QLabel* label) const;
        void pressed(QLabel* label) const;

    private:
        void makeActive();
        void makeInactive();
        void makePressed();
    };

    IconButtonView::IconButtonView(IconMap icon, QWidget* parent) :
        View(parent),
        _states(new IconButtonStates())
    {
        construct(icon);
    }

    IconButtonView::~IconButtonView()
    {
        delete _states;
        _states = nullptr;
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
        _button->setFrameShape(QFrame::Shape::NoFrame);
        _button->setText(QChar(icon));
        _button->setAlignment(Qt::AlignCenter);
        _button->setMinimumSize(Metrics::iconMin);
        _states->inactive(_button);
    }

    void IconButtonView::mousePressEvent(QMouseEvent* event)
    {
        _state |= PRESSED;
        _state &= ~RELEASED;
        refresh();
        _states->pressed(_button);
    }

    void IconButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        _state &= ~PRESSED;
        _state |= RELEASED;
        refresh();

        _states->inactive(_button);
        if (event->button() == Qt::LeftButton)
        {
            if (QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _button->geometry().contains(pt))
                emit clicked();
        }
    }

    void IconButtonView::enterEvent(QEnterEvent* event)
    {
        _state |= ENTER;
        refresh();

        _states->active(_button);
    }

    void IconButtonView::leaveEvent(QEvent* event)
    {
        _state &= ~ENTER;
        refresh();

        if (!((_state & PRESSED) != 0))
            _states->inactive(_button);
    }

    IconButtonStates::IconButtonStates()
    {
        makeActive();
        makeInactive();
        makePressed();
    }

    void IconButtonStates::active(QLabel* label) const
    {
        label->setStyleSheet(_active);
    }

    void IconButtonStates::inactive(QLabel* label) const
    {
        label->setStyleSheet(_inactive);
    }

    void IconButtonStates::pressed(QLabel* label) const
    {
        label->setStyleSheet(_pressed);
    }

    void IconButtonStates::makeActive()
    {
        if (!_active.isEmpty())
            return;

        StyleSheetWriter w;
        w.backgroundColor(Colors::CtrlBackgroundLight);
        w.border(Colors::Accent, 1);
        w.color(Colors::ForegroundLight);
        _active = w.toString();
    }

    void IconButtonStates::makeInactive()
    {
        if (!_inactive.isEmpty())
            return;
        

        StyleSheetWriter w;
        w.backgroundColor(Colors::CtrlBackgroundLight);
        w.border(Colors::BorderLight, 1);
        w.color(Colors::Foreground);
        _inactive = w.toString();
    }

    void IconButtonStates::makePressed()
    {
        if (!_pressed.isEmpty())
            return;
        StyleSheetWriter w;
        w.backgroundColor(
            // clang-format off
            {0.0, 0.0, 0.0, 1.0},
            {
                {0.0, Colors::Accent.darker(Colors::Drk070)},
                {1.0, Colors::Accent},
            }
            // clang-format on
        );
        w.border(Colors::BorderLight, 1);
        w.color(Colors::Accent.lighter(Colors::Lgt090));
        _pressed = w.toString();
    }

}  // namespace Rt2::View
