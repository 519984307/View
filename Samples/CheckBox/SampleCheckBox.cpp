#include "Samples/CheckBox/SampleCheckBox.h"
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include "Utils/Exception.h"
#include "View/CheckBoxLabelView.h"
#include "View/CheckBoxView.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::Samples
{
    QHBoxLayout* group(QWidget* a, QWidget* b)
    {
        const auto hg = View::Qu::horizontal();
        hg->setSpacing(2);
        hg->addWidget(a);
        hg->addWidget(b);
        return hg;
    }

    QWidget* SampleCheckBox::load()
    {
        const auto wig = new QWidget();
        wig->setMinimumSize(View::Metrics::minWindow);

        const auto lo = View::Qu::vertical();

        _check1 = new View::CheckBoxView();
        _text1  = View::Qu::text("Left", View::Colors::Foreground);

        _check2 = new View::CheckBoxView();
        _text2  = View::Qu::text("Right", View::Colors::Foreground);

        lo->addLayout(group(_check1, _text1));
        lo->addLayout(group(_check2, _text2));
        const auto cb = new View::CheckBoxLabelView("Label");
        lo->addWidget(cb,0, Qt::AlignTop);
        
        wig->setLayout(lo);

        _check1->addInput(
            [this, cb](const bool v)
            {
                cb->setTextAlignment(Qt::AlignLeft);
                _check2->setChecked(false);
            });
        _check2->addInput(
            [this, cb](const bool v)
            {
                cb->setTextAlignment(Qt::AlignRight);
                _check1->setChecked(false);
            });

        cb->addOutput([this, cb](const bool v)
        {
            cb->setText(v ? "Label On" : "Label Off");
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
