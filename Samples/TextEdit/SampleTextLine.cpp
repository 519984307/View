#include "Samples/TextEdit/SampleTextLine.h"
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

    String merge(const String& a, const String& b)
    {
        String c;

        const size_t n = Max(a.size(), b.size());
        for (size_t i = 0; i < n; ++i)
        {
            if (i < a.size()) c.push_back(a[i]);
            if (i < b.size()) c.push_back(b[i]);
        }
        return c;
    }

    QWidget* SampleTextLine::load() const
    {
        using namespace Style;
        const auto lo     = Layout::vl(Margin::Large, Size::XLarge);
        const auto label1 = Widget::label();
        const auto a      = Views::textEdit();
        const auto b      = Views::textEdit();

        const auto cba =
            [label1, b](const String& text)
        {
            label1->setText(Qsu::to(merge(text, b->text())));
        };
        const auto cbb =
            [label1, a](const String& text)
        {
            label1->setText(Qsu::to(merge(a->text(), text)));
        };

        a->addOutput(cba);
        b->addOutput(cbb);

        lo->addWidget(a);
        lo->addWidget(b);
        lo->addWidget(label1);
        lo->addStretch();
        return Widget::blank(lo, Window::Small);
    }

    int SampleTextLine::go() const
    {
        int          temp = 0;
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
        constexpr Rt2::Samples::SampleTextLine app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::println(ex.what());
        rc = 1;
    }
    return rc;
}
