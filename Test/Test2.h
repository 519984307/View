#pragma once
#include <QObject>

namespace View::Tests
{
    class WidgetTests final : public QObject
    {
        Q_OBJECT
    private:
        QWidget* _test{nullptr};

    public:
        WidgetTests();

    private slots:

        void initTestCase() const;

        void test1();

        void cleanup();

        void cleanupTestCase() const;
    };

}  // namespace View::Tests
