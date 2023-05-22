#include "View/CheckBoxView.h"
#include <QMouseEvent>
#include <QLabel>
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
        _check.setValue(v, ViewModel::BOTH);
        _states->inactive(_button);
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
        _button = new QLabel(this);
        constructView(_button);
        setPadding(0);
        setBorder(Metrics::borderSizeThick);
        setMinimumSize(Metrics::iconPadding);
        setMaximumSize(Metrics::iconPadding);

        _button->setFont(Qu::iconFont());
        _button->setAlignment(Qt::AlignCenter);
        _button->setMinimumSize(Metrics::iconMin);

        CheckBoxStates::unchecked(_button);
        _states->inactive(_button);

        _check.addInput(
            [this](const bool& v)
            {
                if (v)
                    CheckBoxStates::checked(_button);
                else
                    CheckBoxStates::unchecked(_button);
                refresh();
            });
    }

    void CheckBoxView::mousePressEvent(QMouseEvent* event)
    {
        _state |= PRESSED;
        _state &= ~RELEASED;
        refresh();
    }

    void CheckBoxView::mouseReleaseEvent(QMouseEvent* event)
    {
        _state &= ~PRESSED;
        _state |= RELEASED;

        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _button->geometry().contains(pt))
                setChecked(!isChecked());
        }
    }

    void CheckBoxView::enterEvent(QEnterEvent* event)
    {
        _state |= ENTER;
        refresh();
        _states->active(_button);
    }

    void CheckBoxView::leaveEvent(QEvent* event)
    {
        _state &= ~ENTER;
        refresh();
        _states->inactive(_button);
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
        w.border(c.lighter(Colors::Lgt060), 1);

        _inactive = w.toString();
    }

    void CheckBoxStates::makeInactiveChecked()
    {
        const QColor c = Colors::CtrlBackgroundLight;

        StyleSheetWriter ssw;
        ssw.backgroundColor(Colors::Accent.darker(Colors::Drk010));
        ssw.color(Colors::Accent.lighter(Colors::Lgt090));
        ssw.border(c.darker(Colors::Drk020), 1);

        _inactiveCheck = ssw.toString();
    }

    void CheckBoxStates::makeActive()
    {
        const QColor c = Colors::Accent;

        StyleSheetWriter ssw;
        ssw.backgroundColor(c.darker(Colors::Drk020));
        ssw.border(c.lighter(Colors::Lgt060), 1);
        ssw.color(c.lighter(Colors::Lgt090));
        _active = ssw.toString();
    }

    void CheckBoxStates::makeActiveChecked()
    {
        const QColor c = Colors::Accent;

        StyleSheetWriter ssw;
        ssw.backgroundColor(c.darker(Colors::Drk020));
        ssw.border(c.lighter(Colors::Lgt060), 1);
        ssw.color(c.lighter(Colors::Lgt090));
        _activeCheck = ssw.toString();
    }

    void CheckBoxStates::unchecked(QLabel* widget)
    {
        widget->setText("");
    }

    void CheckBoxStates::checked(QLabel* widget)
    {
        widget->setText(QChar(IconCheck2));
    }

    void CheckBoxStates::active(QLabel* widget) const
    {
        if (widget->text().isEmpty())
            widget->setStyleSheet(_active);
        else
            widget->setStyleSheet(_activeCheck);
    }

    void CheckBoxStates::inactive(QLabel* widget) const
    {
        if (widget->text().isEmpty())
            widget->setStyleSheet(_inactive);
        else
            widget->setStyleSheet(_inactiveCheck);
    }

}  // namespace Rt2::View
