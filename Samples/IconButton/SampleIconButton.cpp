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

    QHBoxLayout* addIcon(IconMap ico, const String& text)
    {
        const auto lo = Qu::horizontal();
        lo->setSpacing(2);
        lo->addWidget(new IconButtonView(ico));
        lo->addWidget(Qu::text(text, Metrics::defaultTextSize, Colors::Foreground));

        return lo;
    }

    QWidget* SampleIconButton::load()
    {
        const auto wig = new QWidget();
        wig->setMinimumSize(Metrics::minWindow);
        const auto root = Qu::horizontal();

        auto lo1 = Qu::vertical();
        lo1->setContentsMargins(Metrics::borderThick);

        for (int i = 0; i < (IconsEnd - IconsStart) - 1; ++i)
        {
            String s;
            s.push_back('\'');
            s.push_back((char)(i + IconsStart + 1));
            s.push_back('\'');
            lo1->addLayout(addIcon((IconMap)(i + IconsStart + 1), s));
            if (i % 12 == 11)
            {
                root->addLayout(lo1);
                lo1 = Qu::vertical();
                lo1->setContentsMargins(Metrics::borderThick);
            }
        }
        root->addLayout(lo1);
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
