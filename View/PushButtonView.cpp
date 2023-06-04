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
#include "View/PushButtonView.h"
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include "Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"
#include "View/StyleSheetWriter.h"
#include "View/View.h"

class QLabel;
class QPushButton;

namespace Rt2::View
{
    class PushButtonStates
    {
    private:
        QString _inactive;
        QString _active;
        QString _hover;
        QString _pressed;
        QColor  _accent;

        void makeInactive();
        void makeActive();
        void makeHover();
        void makePressed();
        void update();

    public:
        PushButtonStates();

        void pressed(QLabel* widget) const;
        void hover(QLabel* widget) const;
        void active(QLabel* widget) const;
        void inactive(QLabel* widget) const;

        void setAccent(const QColor& col);
    };

    PushButtonView::PushButtonView(QWidget* parent) :
        View(parent),
        _states(new PushButtonStates())
    {
        construct();
    }

    PushButtonView::PushButtonView(const String& text, QWidget* parent) :
        View(parent),
        _states(new PushButtonStates())
    {
        construct();
        setLabel(text);
    }

    PushButtonView::~PushButtonView()
    {
        delete _states;
    }

    void PushButtonView::construct()
    {
        _text = new QLabel(this);
        constructView(_text);
        setPadding(0);
        setBorder(Metrics::borderSizeThick);
        setMinimumSize(Metrics::buttonSize);
        setMaximumHeight(Metrics::buttonSize.height());

        _text->setAlignment(Qt::AlignCenter);
        _states->inactive(_text);
    }

    void PushButtonView::setLabel(const String& label) const
    {
        RT_GUARD_CHECK_VOID(_text)

        _text->setText(Qsu::to(label));
    }

    void PushButtonView::setAccent(const QColor& col) const
    {
        RT_GUARD_CHECK_VOID(_states)

        _states->setAccent(col);
    }

    String PushButtonView::label() const
    {
        RT_GUARD_CHECK_RET(_text, "")

        return Qsu::from(_text->text());
    }

    void PushButtonView::addOutput(const BoolModel::Observer& ob)
    {
        _state.addOutput(ob);
    }

    void PushButtonView::mousePressEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event && _states)

        _states->pressed(_text);
        event->accept();
    }

    void PushButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event && _states && _text)

        bool inside = false;
        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _text->geometry().contains(pt))
            {
                _state.dispatch(ViewModel::OUTPUT);
                inside = true;
            }
        }

        if (inside)
            _states->hover(_text);
        else
            _states->inactive(_text);

        event->accept();
    }

    void PushButtonView::enterEvent(QEnterEvent* event)
    {
        RT_GUARD_CHECK_VOID(event && _states && _text)

        _states->hover(_text);
        event->accept();
    }

    void PushButtonView::leaveEvent(QEvent* event)
    {
        RT_GUARD_CHECK_VOID(event && _states && _text)

        _states->inactive(_text);
        event->accept();
    }

    PushButtonStates::PushButtonStates() :
        _accent(Colors::Accent)
    {
        update();
    }

    void PushButtonStates::pressed(QLabel* widget) const
    {
        RT_GUARD_CHECK_VOID(widget)

        widget->setStyleSheet(_pressed);
    }

    void PushButtonStates::hover(QLabel* widget) const
    {
        RT_GUARD_CHECK_VOID(widget)

        widget->setStyleSheet(_hover);
    }

    void PushButtonStates::active(QLabel* widget) const
    {
        RT_GUARD_CHECK_VOID(widget)

        widget->setStyleSheet(_active);
    }

    void PushButtonStates::inactive(QLabel* widget) const
    {
        RT_GUARD_CHECK_VOID(widget)

        widget->setStyleSheet(_inactive);
    }

    void PushButtonStates::setAccent(const QColor& col)
    {
        _accent = col;
        update();
    }

    void PushButtonStates::makeInactive()
    {
        StyleSheetWriter w;
        w.backgroundColor(Colors::up(Colors::CtrlBackground));
        w.color(Colors::ForegroundLight);
        w.border(Colors::down(Colors::CtrlBackground), 1);
        _inactive = w.toString();
    }

    void PushButtonStates::makeActive()
    {
        StyleSheetWriter w;

        w.backgroundColor(Colors::up(Colors::CtrlBackground));
        w.color(Colors::up(Colors::ForegroundLight));
        w.border(Colors::CtrlBackground, 1);

        _active = w.toString();
    }

    void PushButtonStates::makeHover()
    {
        StyleSheetWriter w;

        w.backgroundColor(Colors::up(Colors::CtrlBackground));
        w.color(Colors::up(Colors::ForegroundLight));
        w.border(Colors::highlight(Colors::CtrlBackground), 1);

        _hover = w.toString();
    }

    void PushButtonStates::makePressed()
    {
        StyleSheetWriter w;
        w.backgroundColor(Colors::shadow(_accent));
        w.color(Colors::highlight(Colors::Emphasis[4]));
        w.border(Colors::down(_accent), 1);
        _pressed = w.toString();
    }

    void PushButtonStates::update()
    {
        makeActive();
        makeInactive();
        makeHover();
        makePressed();
    }

}  // namespace Rt2::View
