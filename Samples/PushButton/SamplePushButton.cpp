#include "Samples/PushButton/SamplePushButton.h"
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

using namespace Rt2::View;

namespace Rt2::Samples
{

    QHBoxLayout *group(QWidget *a, QWidget* b)
    {
        const auto lo = Qu::horizontal();
        lo->setSpacing(2);
        lo->addWidget(a);
        lo->addWidget(b, 1);
        return lo;
    }

    QWidget* SamplePushButton::load()
    {
        const auto wig = new QWidget();
        wig->setMinimumSize(Metrics::minWindow);

        const auto lo = Qu::vertical();
        lo->setContentsMargins(Metrics::borderThick);

        const auto t1 = new PushButtonView("Press");
        const auto t2 = new PushButtonView("Press");
        _a = Qu::text("", 10, Colors::Foreground);
        _b = Qu::text("", 10, Colors::Foreground);

        lo->addLayout(group(t1, _a));
        lo->addLayout(group(t2, _b));

        wig->setLayout(lo);


        t1->addOutput([this](bool)
        {
            _a->setText("Pressed");
            _b->setText("Not Pressed");
        });

        t2->addOutput([this](bool)
        {
            _a->setText("Not Pressed");
            _b->setText("Pressed");
        });

        return wig;
    }

    int SamplePushButton::go()
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
        Rt2::Samples::SamplePushButton app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
