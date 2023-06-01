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
#include "View/CheckBoxView.h"
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include "Colors.h"
#include "View/IconButtonView.h"
#include "View/Metrics.h"
#include "View/Qu.h"
#include "View/StyleSheetWriter.h"
#include "View/View.h"

class QLabel;
class QPushButton;

namespace Rt2::View
{
    class CheckBoxStates
    {
    private:
        QString _inactive;
        QString _active;
        QString _inactiveCheck;
        QString _activeCheck;

        void makeInactive();

        void makeInactiveChecked();

        void makeActive();

        void makeActiveChecked();

    public:
        CheckBoxStates();

        static void unchecked(QLabel* widget);

        static void checked(QLabel* widget);

        void active(QLabel* widget) const;

        void inactive(QLabel* widget) const;
    };

    CheckBoxView::CheckBoxView(QWidget* parent) :
        View(parent),
        _states(new CheckBoxStates())
    {
        construct();
    }

    CheckBoxView::~CheckBoxView()
    {
        delete _states;
    }

    void CheckBoxView::setChecked(const bool v)
    {
        if (v)
            _state |= ON;
        else
            _state &= ~ON;

        _check.setValue(v, ViewModel::NONE);
        _check.dispatch(ViewModel::BOTH); // regardless of change
        _states->inactive(_icon);
    }

    void CheckBoxView::addInput(const BoolModel::Observer& ob)
    {
        _check.addInput(ob);
    }

    void CheckBoxView::addOutput(const BoolModel::Observer& ob)
    {
        _check.addOutput(ob);
    }

    void CheckBoxView::construct()
    {
        _icon = new QLabel(this);
        constructView(_icon);
        setPadding(0);
        setBorder(Metrics::borderSizeThick);
        setMinimumSize(Metrics::iconPadding);
        setMaximumSize(Metrics::iconPadding);

        _icon->setFont(Qu::iconFont());
        _icon->setAlignment(Qt::AlignCenter);
        _icon->setMinimumSize(Metrics::iconMin);

        CheckBoxStates::unchecked(_icon);
        _states->inactive(_icon);

        _check.addInput(
            [this](const bool& v)
            {
                if (v)
                    CheckBoxStates::checked(_icon);
                else
                    CheckBoxStates::unchecked(_icon);
                refresh();
            });
    }

    void CheckBoxView::mousePressEvent(QMouseEvent* event)
    {
        _state |= PRESSED;
        refresh();
    }

    void CheckBoxView::mouseReleaseEvent(QMouseEvent* event)
    {
        if (!event) return;

        _state &= ~PRESSED;

        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _icon->geometry().contains(pt))
                setChecked(!isChecked());
        }
    }

    void CheckBoxView::enterEvent(QEnterEvent* event)
    {
        if (!event) return;

        _state |= ENTER;
        refresh();
        _states->active(_icon);
    }

    void CheckBoxView::leaveEvent(QEvent* event)
    {
        if (!event) return;

        _state &= ~ENTER;
        refresh();
        _states->inactive(_icon);
    }

    CheckBoxStates::CheckBoxStates()
    {
        makeActive();
        makeActiveChecked();
        makeInactive();
        makeInactiveChecked();
    }

    void CheckBoxStates::makeInactive()
    {
        const QColor c = Colors::CtrlBackground;

        StyleSheetWriter w;
        w.padding(5);
        w.backgroundColor(c.darker(Colors::Drk020));
        w.color(c.lighter(Colors::Lgt090));
        _inactive = w.toString();
    }

    void CheckBoxStates::makeInactiveChecked()
    {
        const QColor c = Colors::CtrlBackgroundLight;

        StyleSheetWriter w;
        w.backgroundColor(Colors::Accent.darker(Colors::Drk010));
        w.color(Colors::Accent.lighter(Colors::Lgt090));

        _inactiveCheck = w.toString();
    }

    void CheckBoxStates::makeActive()
    {
        const QColor c = Colors::Accent;

        StyleSheetWriter w;
        w.backgroundColor(c.darker(Colors::Drk020));
        w.color(c.lighter(Colors::Lgt090));
        _active = w.toString();
    }

    void CheckBoxStates::makeActiveChecked()
    {
        const QColor c = Colors::Accent;

        StyleSheetWriter w;
        w.backgroundColor(c.darker(Colors::Drk040));
        w.color(c.lighter(Colors::Lgt090));
        _activeCheck = w.toString();
    }

    void CheckBoxStates::unchecked(QLabel* widget)
    {
        if (!widget) return;
        widget->setText("");
    }

    void CheckBoxStates::checked(QLabel* widget)
    {
        if (!widget) return;
        widget->setText(QChar(IconCheck2));
    }

    void CheckBoxStates::active(QLabel* widget) const
    {
        if (!widget) return;

        if (widget->text().isEmpty())
            widget->setStyleSheet(_active);
        else
            widget->setStyleSheet(_activeCheck);
    }

    void CheckBoxStates::inactive(QLabel* widget) const
    {
        if (!widget) return;

        if (widget->text().isEmpty())
            widget->setStyleSheet(_inactive);
        else
            widget->setStyleSheet(_inactiveCheck);
    }

}  // namespace Rt2::View
