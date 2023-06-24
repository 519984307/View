#include "Samples/StringList/SampleStringList.h"
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include "Utils/Char.h"
#include "Utils/Exception.h"
#include "View/IconButtonView.h"
#include "View/Qu.h"
#include "View/StringListView.h"
#include "View/TitleListWidget.h"

using namespace Rt2::View;

namespace Rt2::Samples
{

    QWidget* SampleStringList::load()
    {
        using namespace Style;

        _list = new StringListView();
        
        const auto lo = Layout::v4(0);

        lo->addWidget(
            Views::title(
                "String List",
                {
                    Views::flatIcon(
                        IconAdd,
                        [this](bool)
                        {
                            _list->addEntry(Su::join("item #", _cur++));
                        }),  // flatIcon
                    Views::flatIcon(
                        IconClear,
                        [this](bool)
                        {
                            _cur = 0;
                            _list->clear();
                        }),  // flatIcon
                }            // widget list
                )            // title
        );
        lo->addWidget(_list, 1);
        return Widget::blank(lo, Style::Window::BackgroundLight);
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
