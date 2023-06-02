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
        QColor  _accent;
        QColor  _highlight;

        void makeActive();
        void makeInactive();
        void makePressed();

        void update();

    public:
        explicit FlatIconButtonStates();

        void setAccent(const QColor& col);

        void setHighlight(const QColor& col);

        void active(QLabel* label) const;
        void inactive(QLabel* label) const;
        void pressed(QLabel* label) const;
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

    void FlatIconButtonView::setFlatColor(const QColor& col) const
    {
        if (!_states) return;

        _states->setAccent(col);
        _states->inactive(_button);
    }

    void FlatIconButtonView::setHighlightColor(const QColor& col) const
    {
        if (!_states) return;

        _states->setHighlight(col);
        _states->inactive(_button);
    }

    void FlatIconButtonView::setIconSize(int size) const
    {
        if (!_button) return;

        QFont fnt = Qu::iconFont();
        fnt.setPointSize(size);
        _button->setFont(fnt);
    }

    void FlatIconButtonView::addOutput(const BoolModel::Observer& ot)
    {
        _model.addOutput(ot);
    }

    void FlatIconButtonView::mousePressEvent(QMouseEvent* event)
    {
        if (!event || !_states) return;

        _state |= PRESSED;
        _states->pressed(_button);
        event->accept();
    }

    void FlatIconButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        if (!event || !_states) return;

        _state &= ~PRESSED;
        _states->inactive(_button);

        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _button->geometry().contains(pt))
                _model.dispatch(ViewModel::OUTPUT);
        }

        event->accept();
    }

    void FlatIconButtonView::enterEvent(QEnterEvent* event)
    {
        if (!event || !_states) return;

        _state |= ENTER;
        _states->active(_button);
        event->accept();
    }

    void FlatIconButtonView::leaveEvent(QEvent* event)
    {
        if (!event || !_states) return;

        _state &= ~ENTER;
        if (!((_state & PRESSED) != 0))
            _states->inactive(_button);
        event->accept();
    }

    FlatIconButtonStates::FlatIconButtonStates() :
        _accent(Colors::Foreground),
        _highlight(Colors::Accent)
    {
        update();
    }

    void FlatIconButtonStates::setAccent(const QColor& col)
    {
        _accent = col;
        update();
    }

    void FlatIconButtonStates::setHighlight(const QColor& col)
    {
        _highlight = col;
        update();
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
        StyleSheetWriter w;
        w.color(Colors::up(_accent));
        w.noBackground();
        w.noBorder();
        _active = w.toString();
    }

    void FlatIconButtonStates::makeInactive()
    {
        StyleSheetWriter w;
        w.color(_accent);
        w.noBackground();
        w.noBorder();
        _inactive = w.toString();
    }

    void FlatIconButtonStates::makePressed()
    {
        StyleSheetWriter w;
        w.color(Colors::highlight(_highlight));
        w.noBackground();
        w.noBorder();
        _pressed = w.toString();
    }

    void FlatIconButtonStates::update()
    {
        makeActive();
        makeInactive();
        makePressed();
    }
}  // namespace Rt2::View
