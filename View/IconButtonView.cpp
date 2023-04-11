#include "View/IconButtonView.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::View
{
    IconButtonView::IconButtonView(IconMap icon, QWidget* parent) :
        QWidget(parent)
    {
        construct(icon);
    }

    void IconButtonView::construct(const IconMap icon)
    {
        Qu::setBackground(this, Colors::Border);
        setContentsMargins(Metrics::BorderThin);

        const auto layout = Qu::horizontal();

        _button = Qu::flatButton(this);
        Qu::setColor(_button, QPalette::Button, Colors::CtrlBackground);
        Qu::setColor(_button, QPalette::ButtonText, Colors::Foreground);

        _button->setFont(Qu::iconFont());
        _button->setText(QChar(icon));

        layout->addWidget(_button, 0);
        setLayout(layout);

        connect(_button, &QPushButton::clicked, this, [=]
                { emit clicked(); });
    }

}  // namespace Rt2::View
