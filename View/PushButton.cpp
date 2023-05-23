#include "View/PushButton.h"
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
        _button->setText(Qsu::to(label));
    }

    String PushButtonView::label() const
    {
        return Qsu::from(_button->text());
    }

    void PushButtonView::addOutput(const BoolModel::Observer& ob)
    {
        _observers.addOutput(ob);
    }

    void PushButtonView::construct()
    {
        _button = new QLabel(this);
        constructView(_button);
        setPadding(0);
        setBorder(Metrics::borderSizeThick);
        setMinimumSize(Metrics::buttonSize);
        setMaximumHeight(Metrics::buttonSize.height());
        _button->setAlignment(Qt::AlignCenter);
        _states->inactive(_button);
    }

    void PushButtonView::mousePressEvent(QMouseEvent* event)
    {
        _states->pressed(_button);
        refresh();
    }

    void PushButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        bool inside = false;

        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _button->geometry().contains(pt))
            {
                _observers.setValue(true, ViewModel::OUTPUT);
                inside = true;
            }
        }

        if (inside)
            _states->hover(_button);
        else
            _states->inactive(_button);

        refresh();
    }

    void PushButtonView::enterEvent(QEnterEvent* event)
    {
        _states->hover(_button);
        refresh();
    }

    void PushButtonView::leaveEvent(QEvent* event)
    {
        _states->inactive(_button);
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
        w.border(c.lighter(Colors::Lgt060), 1);

        _inactive = w.toString();
    }

    void PushButtonStates::makeActive()
    {
        const QColor c = Colors::CtrlBackground;

        StyleSheetWriter w;
        w.backgroundColor(c.lighter(Colors::Lgt020));
        w.color(Colors::Foreground);
        w.border(c.lighter(Colors::Lgt060), 1);

        _active = w.toString();
    }

    void PushButtonStates::makeHover()
    {
        const QColor c = Colors::Accent;

        StyleSheetWriter w;
        w.backgroundColor(Colors::CtrlBackground);
        w.border(c.lighter(Colors::Lgt060), 1);
        w.color(Colors::ForegroundLight);

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
        widget->setStyleSheet(_pressed);
    }

    void PushButtonStates::hover(QLabel* widget) const
    {
        widget->setStyleSheet(_hover);
    }

    void PushButtonStates::active(QLabel* widget) const
    {
        widget->setStyleSheet(_active);
    }

    void PushButtonStates::inactive(QLabel* widget) const
    {
        widget->setStyleSheet(_inactive);
    }

}  // namespace Rt2::View
