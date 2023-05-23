#include "Samples/CheckBox/SampleCheckBox.h"
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include "Utils/Exception.h"
#include "View/CheckBoxView.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::Samples
{
    QHBoxLayout* group(QWidget* a, QWidget* b)
    {
        const auto hg = View::Qu::horizontal();
        hg->setSpacing(View::Metrics::indent);

        hg->addWidget(a);
        hg->addWidget(b);
        return hg;
    }

    QWidget* SampleCheckBox::load()
    {
        const auto wig = new QWidget();
        wig->setMinimumSize(View::Metrics::minWindow);

        const auto lo = View::Qu::vertical();

        _text1 = View::Qu::text("", View::Colors::Foreground);
        _text2 = View::Qu::text("", View::Colors::Foreground);

        _check1 = new View::CheckBoxView();
        _check2 = new View::CheckBoxView();

        lo->setAlignment(Qt::AlignCenter);
        lo->addLayout(group(_check1, _text1));
        lo->addLayout(group(_check2, _text2));
        lo->addStretch();

        wig->setLayout(lo);

        _check1->addInput(
            [this](const bool v)
            {
                _text1->setText(v ? "Checked" : "Unchecked");
                _check2->setChecked(!v);
            });
        _check2->addInput(
            [this](const bool v)
            {
                _text2->setText(v ? "Checked" : "Unchecked");
                _check1->setChecked(!v);
            });

        _check1->setChecked(true);
        return wig;
    }

    int SampleCheckBox::go()
    {
        int unused = 0;

        QApplication app(unused, nullptr);
        View::Qu::initResources(app);

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
        Rt2::Samples::SampleCheckBox app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
