#include "IconButtonView.h"
#include <QPushButton>
#include <QWidget>
#include "Colors.h"
#include "Metrics.h"
#include "Qu.h"

namespace Rt2::Widgets
{
    IconButtonView::IconButtonView(IconMap icon, QWidget* parent) :
        QWidget(parent)
    {
        construct(icon);
    }

    void IconButtonView::construct(IconMap icon)
    {
        Qu::setBackground(this, Colors::Border);
        setContentsMargins(Metrics::BorderThin);

        const auto layout = Qu::horizontal();

        _button = Qu::flatButton(this);
        Qu::setColor(_button, QPalette::Button, Colors::CtrlBackground);
        Qu::setColor(_button, QPalette::ButtonText, Colors::Foreground);

        QFont fnt("ViewIcon");
        _button->setFont(fnt);

        fnt.setPointSize(2*Metrics::iconWidth);
        String ico;
        ico.push_back(icon);
        _button->setText(Qsu::to(ico));

        layout->addWidget(_button, 0);
        setLayout(layout);

        connect(_button, &QPushButton::clicked, this, [=]
                { emit clicked(); });
    }

}  // namespace Rt2::Widgets
