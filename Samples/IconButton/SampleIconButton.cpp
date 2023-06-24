#include "Samples/IconButton/SampleIconButton.h"
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include "Utils/Char.h"
#include "Utils/Exception.h"
#include "View/Qu.h"

using namespace Rt2::View;

namespace Rt2::Samples
{

    QHBoxLayout* addIcon(const IconMap ico, const String& text)
    {
        const auto lo = Style::Layout::hl(Style::Size::Large);
        lo->addWidget(Style::Views::icon(ico));
        lo->addWidget(Style::Widget::label(text));
        return lo;
    }

    QWidget* SampleIconButton::load()
    {
        const auto root   = Style::Layout::h4();
        auto       layout = Style::Layout::v2();

        for (int i = 0; i < (IconsEnd - IconsStart) - 1; ++i)
        {
            String s;
            s.push_back('\'');
            s.push_back((char)(i + IconsStart + 1));
            s.push_back('\'');
            layout->addLayout(addIcon((IconMap)(i + IconsStart + 1), s));

            if (i % 12 == 11)
            {
                layout->addStretch();
                root->addLayout(layout);
                layout = Style::Layout::v2();
            }
        }

        layout->addStretch();
        root->addLayout(layout);
        return Style::Widget::blank(root);
    }

    int SampleIconButton::go()
    {
        int temp = 0;
        QApplication app(temp, nullptr);
        Qu::initResources(app);
        const auto view = load();
        view->show();
        temp = QApplication::exec();
        delete view;
        return temp;
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
        Rt2::Console::println(ex.what());
        rc = 1;
    }
    return rc;
}
