#pragma once
#include <gtest/gtest.h>
//
#include <QApplication>
#include <QBoxLayout>
#include <QColor>
//
#include "View/CheckBoxView.h"
#include "View/Qu.h"

#define GTEST_QT_TEST(suite_name, name)                                   \
    void suite_name##name##_scope(QWidget* root, QVBoxLayout*);           \
    GTEST_TEST(suite_name, name)                                          \
    {                                                                     \
        using namespace Rt2::View;                                        \
        using namespace Style;                                            \
        int          argc = 0;                                            \
        QApplication app(argc, nullptr);                                  \
        Qu::initResources(app);                                           \
        QWidget* root;                                                    \
        {                                                                 \
            const auto box = Widget::blank(Style::Window::Background);    \
            box->setMinimumSize(Window::Small);                           \
            box->setUpdatesEnabled(true);                                 \
            box->setMouseTracking(true);                                  \
            QVBoxLayout* layout = new QVBoxLayout();                      \
            box->setLayout(layout);                                       \
            root = box;                                                   \
        }                                                                 \
        try                                                               \
        {                                                                 \
            suite_name##name##_scope(root, (QVBoxLayout*)root->layout()); \
        }                                                                 \
        catch (Rt2::Exception&)                                           \
        {                                                                 \
        }                                                                 \
        delete root;                                                      \
    }                                                                     \
    void suite_name##name##_scope(QWidget* root, QVBoxLayout* layout)

#define SHOW_RUN 0  // keep off except for testing
#if SHOW_RUN == 1
    #define RUN                   \
        {                         \
            root->show();         \
            QApplication::exec(); \
        }
#else
    #define RUN
#endif
