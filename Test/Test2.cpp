#include "Test2.h"
#include <QPushButton>
#include <QTest>
namespace View::Tests
{
    WidgetTests::WidgetTests() = default;

    void WidgetTests::initTestCase() const
    {
        QCOMPARE(_test, nullptr);
    }

    void WidgetTests::test1()
    {
        _test->show();
        QApplication::exec();
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

}  // namespace View::Tests
QTEST_MAIN(View::Tests::WidgetTests)
