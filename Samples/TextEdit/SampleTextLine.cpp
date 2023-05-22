#include "Samples/TextEdit/SampleTextLine.h"
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

    QWidget* SampleTextLine::load()
    {
        const auto wig = new QWidget();
        wig->setMinimumSize(Metrics::minWindow);

        const auto root = Qu::vertical();
        root->setContentsMargins(Metrics::borderThick);

        _label = Qu::text("", 18, Colors::Foreground);

        const auto te = new TextEditView();
        root->addWidget(te);
        root->addWidget(_label, 1);

        te->addOutput(
            [this](const String& text)
            {
                _label->setText(Qsu::to(text));
            });

        wig->setLayout(root);
        return wig;
    }

    int SampleTextLine::go()
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
        Rt2::Samples::SampleTextLine app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
