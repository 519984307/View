#include <gtest/gtest.h>
#include <QApplication>
#include <QColor>
#include <QVBoxLayout>
#include "View/CheckBoxView.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"
//
#include "Test2.h"
#include "View/IconButtonView.h"
#define SHOW_RUN 1
#if SHOW_RUN == 1
    #define RUN QApplication::exec()
#else
    #define RUN
#endif

GTEST_QT_TEST(View, CheckBoxView)
{
    const auto view = new Rt2::View::CheckBoxView();
    layout->addWidget(view, 1, Qt::AlignCenter);

    bool checkState = false;
    view->addObserver([&checkState](const bool& v)
                      { checkState = v; });

    view->setChecked(true);
    EXPECT_EQ(checkState, true);

    view->setChecked(false);
    EXPECT_EQ(checkState, false);

    root->show();
    RUN;
}

GTEST_QT_TEST(View, IconButton)
{
    using namespace Rt2::View;

    QHBoxLayout* chb = nullptr;
    for (int i = 0; i < 26; ++i)
    {
        if (!chb)
            chb = Qu::horizontal();

        const auto view = new IconButtonView((IconMap)(i + IconDelete));
        chb->addWidget(view, 1, Qt::AlignCenter);

        if (i % 10 == 9)
        {
            layout->addLayout(chb);
            chb = Qu::horizontal();
        }
    }
    layout->addLayout(chb);

    root->show();
    RUN;
}
