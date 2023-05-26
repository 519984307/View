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

        void makeInactive();

        void makeActive();

        void makeHover();

        void makePressed();

    public:
        PushButtonStates();

        void pressed(QLabel* widget) const;
        void hover(QLabel* widget) const;
        void active(QLabel* widget) const;
        void inactive(QLabel* widget) const;
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

    void PushButtonView::setLabel(const String& label) const
    {
        if (!_text) return;
        _text->setText(Qsu::to(label));
    }

    String PushButtonView::label() const
    {
        if (!_text) return "";
        return Qsu::from(_text->text());
    }

    void PushButtonView::addOutput(const BoolModel::Observer& ob)
    {
        _observers.addOutput(ob);
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

    void PushButtonView::mousePressEvent(QMouseEvent* event)
    {
        _states->pressed(_text);
        refresh();
    }

    void PushButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        if (!event) return;

        bool inside = false;

        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _text->geometry().contains(pt))
            {
                _observers.setValue(true, ViewModel::OUTPUT);
                inside = true;
            }
        }

        if (inside)
            _states->hover(_text);
        else
            _states->inactive(_text);

        refresh();
    }

    void PushButtonView::enterEvent(QEnterEvent* event)
    {
        _states->hover(_text);
        refresh();
    }

    void PushButtonView::leaveEvent(QEvent* event)
    {
        _states->inactive(_text);
        refresh();
    }

    PushButtonStates::PushButtonStates()
    {
        makeActive();
        makeInactive();
        makeHover();
        makePressed();
    }

    void PushButtonStates::makeInactive()
    {
        const QColor c = Colors::CtrlBackground;

        StyleSheetWriter w;
        w.padding(5);
        w.backgroundColor(c.lighter(Colors::Lgt060));
        w.color(Colors::Foreground);
        _inactive = w.toString();
    }

    void PushButtonStates::makeActive()
    {
        const QColor c = Colors::CtrlBackground;

        StyleSheetWriter w;
        w.backgroundColor(c.lighter(Colors::Lgt020));
        w.color(Colors::Foreground);
        _active = w.toString();
    }

    void PushButtonStates::makeHover()
    {
        const QColor c = Colors::Accent;

        StyleSheetWriter w;
        w.backgroundColor(Colors::CtrlBackgroundLight);
        w.color(Colors::ForegroundLight);
        w.border(Colors::CtrlBackground.lighter(Colors::Lgt020), 1);
        _hover = w.toString();
    }

    void PushButtonStates::makePressed()
    {
        const QColor c = Colors::CtrlBackground;

        StyleSheetWriter w;
        w.backgroundColor(c.darker(Colors::Drk020));
        w.border(Colors::BorderLight, 1);
        w.color(Colors::Foreground);

        _pressed = w.toString();
    }

    void PushButtonStates::pressed(QLabel* widget) const
    {
        if (!widget) return;
        widget->setStyleSheet(_pressed);
    }

    void PushButtonStates::hover(QLabel* widget) const
    {
        if (!widget) return;
        widget->setStyleSheet(_hover);
    }

    void PushButtonStates::active(QLabel* widget) const
    {
        if (!widget) return;
        widget->setStyleSheet(_active);
    }

    void PushButtonStates::inactive(QLabel* widget) const
    {
        if (!widget) return;
        widget->setStyleSheet(_inactive);
    }

}  // namespace Rt2::View
