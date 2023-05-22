#include "Samples/IconButton/SampleIconButton.h"
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

    QHBoxLayout* addIcon(View::IconMap ico, const String& text)
    {
        const auto lo = Qu::horizontal();
        lo->setSpacing(2);
        lo->addWidget(new IconButtonView(ico));
        lo->addWidget(Qu::text(text, Metrics::defaultTextSize, Colors::Foreground));
        return lo;
    }

    QWidget* SampleIconButton::load()
    {
#define Icon(x) x, #x
        const auto wig = new QWidget();
        wig->setMinimumSize(Metrics::minWindow);
        const auto root = Qu::horizontal();

        const auto lo1 = Qu::vertical();
        lo1->setContentsMargins(Metrics::borderThick);
        lo1->addLayout(addIcon(Icon(IconAdd)));
        lo1->addLayout(addIcon(Icon(IconEdit)));
        lo1->addLayout(addIcon(Icon(IconDelete)));
        lo1->addLayout(addIcon(Icon(IconClear)));
        lo1->addLayout(addIcon(Icon(IconBack)));
        lo1->addLayout(addIcon(Icon(IconUp)));
        lo1->addLayout(addIcon(Icon(IconForward)));
        lo1->addLayout(addIcon(Icon(IconDown)));
        lo1->addLayout(addIcon(Icon(IconExit)));
        lo1->addLayout(addIcon(Icon(IconCheck0)));
        lo1->addLayout(addIcon(Icon(IconCheck1)));
        root->addLayout(lo1);

        const auto lo2 = Qu::vertical();
        lo1->setContentsMargins(Metrics::borderThick);
        lo2->addLayout(addIcon(Icon(IconCheck2)));
        lo2->addLayout(addIcon(Icon(IconCheck3)));
        lo2->addLayout(addIcon(Icon(IconX)));
        lo2->addLayout(addIcon(Icon(IconBox)));
        lo2->addLayout(addIcon(Icon(IconSettings)));
        lo2->addLayout(addIcon(Icon(IconTriDown)));
        lo2->addLayout(addIcon(Icon(IconMenu1)));
        lo2->addLayout(addIcon(Icon(IconMenu2)));
        lo2->addLayout(addIcon(Icon(IconGraphBar)));
        lo2->addLayout(addIcon(Icon(IconGraphScatter)));
        root->addLayout(lo2);

        const auto lo3 = Qu::vertical();
        lo3->setContentsMargins(Metrics::borderThick);
        lo3->addLayout(addIcon(Icon(IconGraphLine)));
        lo3->addLayout(addIcon(Icon(IconGraphArea)));
        lo3->addLayout(addIcon(Icon(IconFull)));
        lo3->addLayout(addIcon(Icon(IconUpdate)));
        lo3->addLayout(addIcon(Icon(IconSettings2)));
        lo3->addLayout(addIcon(Icon(IconHome)));
        lo3->addLayout(addIcon(Icon(IconRefresh)));
        root->addLayout(lo3);

        wig->setLayout(root);
        return wig;
    }

    int SampleIconButton::go()
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
        Rt2::Samples::SampleIconButton app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
