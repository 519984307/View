#include "Test2.h"
#include <QPushButton>
#include <QTest>

WidgetTests::WidgetTests() = default;

void WidgetTests::initTestCase() const
{
    QCOMPARE(_test, nullptr);
}

void WidgetTests::test1()
{
    _test = new QWidget();
    _test->setMinimumSize(320, 240);

    QCOMPARE_EQ(_test->minimumWidth(), 320);
    QCOMPARE_EQ(_test->minimumHeight(), 240);
    _test->show();
}

void WidgetTests::cleanup()
{
    delete _test;
    _test = nullptr;
}

void WidgetTests::cleanupTestCase() const
{
    QCOMPARE(_test, nullptr);
}

QTEST_MAIN(WidgetTests)
