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

    void IconButtonView::addOutput(const BoolModel::Observer& ot)
    {
        _model.addOutput(ot);
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
        if (!event) return;

        _state &= ~PRESSED;
        _state |= RELEASED;
        refresh();

        _states->inactive(_button);
        if (event->button() == Qt::LeftButton)
        {
            if (QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _button->geometry().contains(pt))
            {
                _model.setValue(true, ViewModel::OUTPUT);
                emit clicked();
            }
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
        if (!label) return;
        label->setStyleSheet(_active);
    }

    void IconButtonStates::inactive(QLabel* label) const
    {
        if (!label) return;
        label->setStyleSheet(_inactive);
    }

    void IconButtonStates::pressed(QLabel* label) const
    {
        if (!label) return;
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
        w.border(Colors::CtrlBackgroundLight.darker(Colors::Drk020), 1);
        w.color(Colors::Foreground);
        _inactive = w.toString();
    }

    void IconButtonStates::makePressed()
    {
        if (!_pressed.isEmpty())
            return;
        StyleSheetWriter w;
        w.backgroundColor(Colors::CtrlBackground.darker(Colors::Drk010));
        w.border(Colors::CtrlBackgroundLight.lighter(Colors::Lgt020), 1);
        w.color(Colors::Accent.lighter(Colors::Lgt050));
        _pressed = w.toString();
    }

}  // namespace Rt2::View
