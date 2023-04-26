#pragma once
#define GTEST_QT_TEST_FRAME()                                      \
    QWidget* root;                                                 \
    {                                                              \
        using namespace Rt2::View;                                 \
        const auto box = Qu::box(nullptr, Colors::CtrlBackground); \
        box->setMinimumSize(Metrics::minWindow);                   \
        Qu::setBackground(box, Colors::CtrlBackground);            \
        box->setUpdatesEnabled(true);                              \
        box->setMouseTracking(true);                               \
        QVBoxLayout* layout = new QVBoxLayout();                   \
        box->setLayout(layout);                                    \
        root = box;                                                \
    }

#define GTEST_QT_TEST(suite_name, name)                                   \
    void suite_name##name##_scope(QWidget* root, QVBoxLayout*);           \
    GTEST_TEST(suite_name, name)                                          \
    {                                                                     \
        using namespace Rt2;                                              \
        int          argc = 0;                                            \
        QApplication app(argc, nullptr);                                  \
        Rt2::View::Qu::initResources(app);                                \
        GTEST_QT_TEST_FRAME();                                            \
        try                                                               \
        {                                                                 \
            suite_name##name##_scope(root, (QVBoxLayout*)root->layout()); \
        }                                                                 \
        catch (Exception&)                                                \
        {                                                                 \
        }                                                                 \
        delete root;                                                      \
    }                                                                     \
    void suite_name##name##_scope(QWidget* root, QVBoxLayout* layout)
