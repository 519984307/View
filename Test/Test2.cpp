#include <QApplication>
#include <QColor>
#include <QVBoxLayout>
#include <gtest/gtest.h>
#include "View/CheckBoxView.h"
#include "View/Qu.h"
//
#include "View/IconButtonView.h"
#include "View/GTest/Macros.h"

GTEST_QT_TEST(View, CheckBoxView)
{
    const auto view = new Rt2::View::CheckBoxView();
    layout->addWidget(view, 1, Qt::AlignCenter);

    
    bool checkState = false;
    view->addOutput([&checkState](const bool& v)
                      { checkState = v; });

    view->setChecked(true);
    EXPECT_EQ(checkState, true);

    view->setChecked(false);
    EXPECT_EQ(checkState, false);
    RUN;
}

GTEST_QT_TEST(View, IconButton)
{
    using namespace Rt2::View;

    QHBoxLayout* chb = nullptr;
    for (int i = 0; i < 26; ++i)
    {
        if (!chb)
            chb = Style::Layout::h0();

        const auto view = new IconButtonView((IconMap)(i + IconDelete));
        chb->addWidget(view, 1, Qt::AlignCenter);

        if (i % 10 == 9)
        {
            layout->addLayout(chb);
            chb = Style::Layout::h0();
        }
    }
    layout->addLayout(chb);
    RUN;
}
