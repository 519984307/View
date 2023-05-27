#include "Samples/Emphasis/SampleEmphasis.h"
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

    QWidget* SampleEmphasis::load()
    {
        const auto wig = new QWidget();
        wig->setMinimumSize(Metrics::minWindow);

        const auto lo = Qu::vertical();
        lo->setContentsMargins(Metrics::borderThick);

        _label0 = Qu::emphasis("", 16, 5);
        _label1 = Qu::emphasis("", 16, 4);
        _label2 = Qu::emphasis("", 16, 3);
        _label3 = Qu::emphasis("", 16, 2);
        _label4 = Qu::emphasis("", 16, 1);
        _label5 = Qu::emphasis("", 16, 0);


        const auto te = new TextEditView();
        lo->addWidget(_label0);
        lo->addWidget(_label1);
        lo->addWidget(_label2);
        lo->addWidget(_label3);
        lo->addWidget(_label4);
        lo->addWidget(_label5);
        lo->addStretch();

        lo->addWidget(te);
        te->addOutput(
            [this](const String& text)
            {
                QString str = Qsu::to(text);
                _label0->setText(str);
                _label1->setText(str);
                _label2->setText(str);
                _label3->setText(str);
                _label4->setText(str);
                _label5->setText(str);
            });
        wig->setLayout(lo);
        return wig;
    }

    int SampleEmphasis::go()
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
        Rt2::Samples::SampleEmphasis app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
