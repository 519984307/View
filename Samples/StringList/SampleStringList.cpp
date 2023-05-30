#include "Samples/StringList/SampleStringList.h"
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include "Utils/Char.h"
#include "Utils/Exception.h"
#include "View/Colors.h"
#include "View/FlagView.h"
#include "View/IconButtonView.h"
#include "View/Metrics.h"
#include "View/Qu.h"
#include "View/StringListView.h"

using namespace Rt2::View;

namespace Rt2::Samples
{

    QWidget* SampleStringList::load()
    {
        const auto wig = new QWidget();
        wig->setMinimumSize(Metrics::minWindow);

        const auto lo = Qu::vertical();
        lo->setContentsMargins(Metrics::borderThick);

        const auto add  = Qu::icon(IconAdd);
        const auto clear  = Qu::icon(IconClear);

        _list= new StringListView();

        lo->addLayout(Qu::titleList("StringList", {add, clear}));
        lo->addWidget(_list, 1);

        add->addOutput(
            [this](bool) {
                _list->addEntry(Su::join("item #", _cur++));
            });

        clear->addOutput(
            [this](bool) {
                _cur = 0;
                _list->clear();
            });

        wig->setLayout(lo);
        return wig;
    }

    int SampleStringList::go()
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
        Rt2::Samples::SampleStringList app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
