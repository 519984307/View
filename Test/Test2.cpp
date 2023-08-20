#include <gtest/gtest.h>
#include <QApplication>
#include <QColor>
#include <QVBoxLayout>
#include "View/CheckBoxView.h"
#include "View/Qu.h"
//
#include "View/GTest/Macros.h"
#include "View/IconButtonView.h"

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
