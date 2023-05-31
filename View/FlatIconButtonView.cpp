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
#include "View/FlatIconButtonView.h"
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
    class FlatIconButtonStates
    {
    private:
        QString _active;
        QString _inactive;
        QString _pressed;
        QColor  _color;

    public:
        explicit FlatIconButtonStates(const QColor& col = Colors::Foreground);

        void updateColor(const QColor& col);

        void active(QLabel* label) const;
        void inactive(QLabel* label) const;
        void pressed(QLabel* label) const;

    private:
        void makeActive();
        void makeInactive();
        void makePressed();
    };

    FlatIconButtonView::FlatIconButtonView(const IconMap icon, QWidget* parent) :
        View(parent),
        _states(new FlatIconButtonStates())
    {
        construct(icon);
    }

    FlatIconButtonView::~FlatIconButtonView()
    {
        delete _states;
        _states = nullptr;
    }

    void FlatIconButtonView::setFlatColor(const QColor& col) const
    {
        if (_states)
        {
            _states->updateColor(col);
            _states->inactive(_button);
        }
    }

    void FlatIconButtonView::addOutput(const BoolModel::Observer& ot)
    {
        _model.addOutput(ot);
    }

    void FlatIconButtonView::construct(const IconMap icon)
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

    void FlatIconButtonView::mousePressEvent(QMouseEvent* event)
    {
        _state |= PRESSED;
        refresh();
        _states->pressed(_button);
    }

    void FlatIconButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        if (!event) return;

        _state &= ~PRESSED;
        refresh();

        _states->inactive(_button);

        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _button->geometry().contains(pt))
                _model.setValue(!_model.value(), ViewModel::OUTPUT);
        }
    }

    void FlatIconButtonView::enterEvent(QEnterEvent* event)
    {
        _state |= ENTER;
        refresh();
        _states->active(_button);
    }

    void FlatIconButtonView::leaveEvent(QEvent* event)
    {
        _state &= ~ENTER;
        refresh();
        if (!((_state & PRESSED) != 0))
            _states->inactive(_button);
    }

    FlatIconButtonStates::FlatIconButtonStates(const QColor& col)
    {
        updateColor(col);
    }

    void FlatIconButtonStates::updateColor(const QColor& col)
    {
        _color = col;
        _active.clear();
        _inactive.clear();
        _pressed.clear();
        makeActive();
        makeInactive();
        makePressed();
    }

    void FlatIconButtonStates::active(QLabel* label) const
    {
        if (!label) return;
        label->setStyleSheet(_active);
    }

    void FlatIconButtonStates::inactive(QLabel* label) const
    {
        if (!label) return;
        label->setStyleSheet(_inactive);
    }

    void FlatIconButtonStates::pressed(QLabel* label) const
    {
        if (!label) return;

        label->setStyleSheet(_pressed);
    }

    void FlatIconButtonStates::makeActive()
    {
        if (!_active.isEmpty())
            return;

        StyleSheetWriter w;
        w.color(_color.lighter(Colors::Lgt050));
        _active = w.toString();
    }

    void FlatIconButtonStates::makeInactive()
    {
        if (!_inactive.isEmpty())
            return;

        StyleSheetWriter w;
        w.noBackground();
        w.color(_color);
        _inactive = w.toString();
    }

    void FlatIconButtonStates::makePressed()
    {
        if (!_pressed.isEmpty())
            return;
        StyleSheetWriter w;
        w.color(_color.darker(Colors::Drk020));
        _pressed = w.toString();
    }

}  // namespace Rt2::View
