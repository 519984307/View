#include "IconButtonView.h"
#include <QPushButton>
#include <QWidget>
#include "Colors.h"
#include "Qu.h"

namespace Rt2::Widgets
{
    IconButtonView::IconButtonView(QWidget* parent) :
        QWidget(parent)
    {
        construct();
    }

    void IconButtonView::construct()
    {
        Qu::setBackground(this, Colors::Grey00);
        const auto layout = Qu::horizontal();

        _button = Qu::flatButton(this);
        Qu::setColor(_button, QPalette::Button, Colors::Grey00);
        Qu::setColor(_button, QPalette::ButtonText, Colors::Text00);

        const QFont fnt("ViewIcon");
        _button->setFont(fnt);
        _button->setText("G");

        layout->addWidget(_button, 0);
        setLayout(layout);
    }

}  // namespace Rt2::Widgets
