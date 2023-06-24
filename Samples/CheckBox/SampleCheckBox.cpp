#include "Samples/CheckBox/SampleCheckBox.h"
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include "Utils/Exception.h"
#include "Utils/Win32/CrtUtils.h"
#include "View/CheckBoxView.h"
#include "View/Qu.h"

using namespace Rt2::View;

namespace Rt2::Samples
{
    QHBoxLayout* group(QWidget* a, QWidget* b)
    {
        const auto hg = Style::Layout::h3();
        hg->addWidget(a);
        hg->addWidget(b);
        return hg;
    }

    QWidget* SampleCheckBox::load()
    {
        const auto lo = Style::Layout::v3();

        _check1 = Style::Views::check();
        _text1  = Style::Widget::label("Left");

        _check2 = Style::Views::check();
        _text2  = Style::Widget::label("Right");

        lo->addLayout(group(_check1, _text1));
        lo->addLayout(group(_check2, _text2));

        _check1->addOutput(
            [this](const bool v)
            {
                _check2->setChecked(!v);
            });
        _check2->addOutput(
            [this](const bool v)
            {
                _check1->setChecked(!v);
            });
        _check1->setChecked(true);
        return Style::Widget::blank(lo);
    }

    int SampleCheckBox::go()
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
        Rt2::Samples::SampleCheckBox app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::println(ex.what());
        rc = 1;
    }
    return rc;
}
