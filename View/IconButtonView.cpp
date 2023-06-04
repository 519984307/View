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
#include "View/IconButtonView.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"
#include "View/StyleSheetWriter.h"

namespace Rt2::View
{

    class IconButtonStates
    {
    private:
        QString _active;
        QString _inactive;
        QString _pressed;
        QColor  _accent;

        void makeActive();
        void makeInactive();
        void makePressed();

        void update();

    public:
        IconButtonStates();

        void active(QLabel* label) const;
        void inactive(QLabel* label) const;
        void pressed(QLabel* label) const;

        void setAccent(const QColor& col);
    };

    IconButtonView::IconButtonView(const IconMap icon, QWidget* parent) :
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
        setMinimumSize(Metrics::iconPadding);
        setMaximumSize(Metrics::iconPadding);

        _button->setFont(Qu::iconFont());
        _button->setFrameShape(QFrame::Shape::NoFrame);
        _button->setText(QChar(icon));
        _button->setAlignment(Qt::AlignCenter);
        _button->setMinimumSize(Metrics::iconMin);
        _button->setAttribute(Qt::WA_TransparentForMouseEvents);

        _states->inactive(_button);
    }

    void IconButtonView::setAccent(const QColor& col) const
    {
        if (!_states) return;

        _states->setAccent(col);
    }

    void IconButtonView::addOutput(const BoolModel::Observer& ot)
    {
        _model.addOutput(ot);
    }


    void IconButtonView::mousePressEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event && _button && _states)

        _state |= PRESSED;
        _states->pressed(_button);

        event->accept();
    }

    void IconButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event && _button && _states)

        _state &= ~PRESSED;
        _states->inactive(_button);

        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                _button->geometry().contains(pt))
                _model.dispatch(ViewModel::OUTPUT);
        }
        event->accept();
    }

    void IconButtonView::enterEvent(QEnterEvent* event)
    {
        RT_GUARD_CHECK_VOID(event && _button && _states)

        _states->active(_button);
        event->accept();
    }

    void IconButtonView::leaveEvent(QEvent* event)
    {
        RT_GUARD_CHECK_VOID(event && _button && _states)

        if (!isPressed())
            _states->inactive(_button);
        event->accept();
    }

    bool IconButtonView::isPressed() const
    {
        return (_state & PRESSED) != 0;
    }

    IconButtonStates::IconButtonStates() :
        _accent(Colors::Accent)
    {
        update();
    }

    void IconButtonStates::active(QLabel* label) const
    {
        RT_GUARD_CHECK_VOID(label)
        label->setStyleSheet(_active);
    }

    void IconButtonStates::inactive(QLabel* label) const
    {
        RT_GUARD_CHECK_VOID(label)
        label->setStyleSheet(_inactive);
    }

    void IconButtonStates::pressed(QLabel* label) const
    {
        RT_GUARD_CHECK_VOID(label)
        label->setStyleSheet(_pressed);
    }

    void IconButtonStates::setAccent(const QColor& col)
    {
        _accent = col;
        update();
    }

    void IconButtonStates::makeActive()
    {
        StyleSheetWriter w;
        w.backgroundColor(Colors::CtrlBackgroundLight);
        w.border(Colors::Accent, 1);
        w.color(Colors::ForegroundLight);
        _active = w.toString();
    }

    void IconButtonStates::makeInactive()
    {
        StyleSheetWriter w;
        w.backgroundColor(Colors::CtrlBackground);
        w.border(Colors::down(Colors::CtrlBackground), 1);
        w.color(Colors::Foreground);
        _inactive = w.toString();
    }

    void IconButtonStates::makePressed()
    {
        StyleSheetWriter w;
        w.backgroundColor(Colors::shadow(Colors::CtrlBackground));
        w.border(Colors::up(Colors::CtrlBackground), 1);
        w.color(Colors::highlight(_accent));
        _pressed = w.toString();
    }

    void IconButtonStates::update()
    {
        makeActive();
        makeInactive();
        makePressed();
    }
}  // namespace Rt2::View
