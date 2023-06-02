#include "Samples/FlagView/SampleBitFlag.h"
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

namespace Rt2::Samples
{
    QWidget* SampleBitFlag::load()
    {
        const auto wig = new QWidget();
        wig->setMinimumSize(View::Metrics::minWindow);

        const auto lo = View::Qu::vertical();

        _flag = new View::FlagView();
        _bin  = View::Qu::text("00000000", View::Metrics::h5, View::Colors::Foreground);
        _oct  = View::Qu::text("000", View::Metrics::h5, View::Colors::Foreground);
        _hex  = View::Qu::text("00", View::Metrics::h5, View::Colors::Foreground);

        for (int i = 0; i < 8; i++)
            _flag->addFlag(false, Char::toString(1 << i));

        lo->addWidget(_flag);
        lo->addWidget(_bin);
        lo->addWidget(_oct);
        lo->addWidget(_hex);
        lo->addStretch();

        _flag->addOutput(
            [this](const int bits)
            {
                const uint8_t b = (uint8_t)Clamp<int>(bits, 0, 255);
                _bin->setText(View::Qsu::to(Char::toBinaryString(b)));
                _hex->setText(View::Qsu::to(Char::toHexString(b)));
                _oct->setText(View::Qsu::to(Char::toOctalString(b)));
            });

        wig->setLayout(lo);
        return wig;
    }

    int SampleBitFlag::go()
    {
        int          unused = 0;
        QApplication app(unused, nullptr);
        View::Qu::initResources(app);

        auto view = load();
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
        Rt2::Samples::SampleBitFlag app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
