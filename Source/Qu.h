#pragma once
#include <QBoxLayout>
#include <QWidget>
#include "Layouts/RowLayout.h"
#include "Utils/String.h"

class QLabel;
class QHBoxLayout;

namespace Rt2::Qt
{
    class Qu
    {
    public:
        static constexpr QSize mw{320, 240};
        static constexpr int   mch = 24;
        static constexpr int   mcw = 24;
        static constexpr QSize cm{mcw, mch};
        static constexpr int   ts{10};
        static constexpr int   gm{0};
        static constexpr int   gs{0};
        static constexpr int   h1{28};
        static constexpr int   h2{24};
        static constexpr int   h3{20};
        static constexpr int   h4{18};
        static constexpr int   h5{16};
        static constexpr int   h6{15};

        static void fit(QWidget* widget);
        static void fit(QLayout* layout);

        static QVBoxLayout* vertical(QWidget* parent = nullptr);

        static QHBoxLayout* horizontal(QWidget* parent = nullptr);

        static QWidget* box(
            QWidget*      parent = nullptr,
            const QColor& col    = QColor(0xFF, 0x00, 0xFF));

        static QLabel* text(
            const String& str,
            QWidget*      parent = nullptr,
            const QColor& col    = QColor(0xFF, 0x00, 0xFF));

        static void setColor(
            QWidget*            widget,
            QPalette::ColorRole role,
            const QColor&       value);

        static void setBackground(
            QWidget*      widget,
            const QColor& value);

        static void setForeground(
            QWidget* widget, 
            const QColor& value);

        static void clearMargins(const QObject* top);

        static void clearSpace(QObject* top);

        static bool isWidget(const QObject* obj);

        static bool isLayout(const QObject* obj);

        static void logRecursive(const QObject* root, int depth);
    };

}  // namespace Rt2::Qt
