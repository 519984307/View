#include "Samples/Slider/SampleSlider.h"
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include "Utils/Char.h"
#include "Utils/Exception.h"
#include "View/Colors.h"
#include "View/FlagView.h"
#include "View/Metrics.h"
#include "View/Qu.h"
#include "View/SliderView.h"

using namespace Rt2::View;

namespace Rt2::Samples
{

    QWidget* SampleSlider::load()
    {
        const auto wig = new QWidget();
        wig->setMinimumSize(Metrics::minWindow);

        const auto lo = Qu::vertical();
        lo->setContentsMargins(Metrics::borderThick);

        _label = Qu::text("", 12, Colors::Foreground);

        const auto view = new SliderView();
        view->setRange(0, 5000);
        view->setValue(2500);
        view->setRate(2);


        lo->addWidget(view);
        lo->addWidget(_label, 1, Qt::AlignTop | Qt::AlignCenter);

        wig->setLayout(lo);

        view->addOutput(
            [this](const double value)
            {
                _label->setText(Qsu::to(Char::toString(value)));
            });

        return wig;
    }

    int SampleSlider::go()
    {
        int unused = 0;

        QApplication app(unused, nullptr);
        Qu::initResources(app);

        const auto view = load();
        view->show();

        unused = QApplication::exec();
        delete view;
        return unused;
    }

}  // namespace Rt2::Samples

int main(int, char*[])
{
    int rc;
    try
    {
        Rt2::Samples::SampleSlider app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
