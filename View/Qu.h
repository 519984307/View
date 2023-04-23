#pragma once
#include <QPalette>
#include "Utils/String.h"

namespace Rt2
{
    namespace Math
    {
        class Rect;
    }
}  // namespace Rt2

class QLayout;
class QPushButton;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QWidget;

namespace Rt2::View
{
    class Qu
    {
    public:
        static void initResources();

        static void dropShadow(
            QLinearGradient& gradient,
            const QRectF&    into,
            const QColor&    base);

        static void fit(QWidget* widget);

        static QString defaultStyle();

        static void fit(QLayout* layout);

        static QVBoxLayout* vertical(QWidget* parent = nullptr);

        static QHBoxLayout* horizontal(QWidget* parent = nullptr);

        static QPushButton* flatButton(QWidget* parent = nullptr);

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
            QWidget*      widget,
            const QColor& value);

        static QColor opacity(const QColor& value, int alpha);

        static void clearSpace(QObject* top);

        static bool isWidget(const QObject* obj);

        static bool isLayout(const QObject* obj);

        static void logRecursive(const QObject* root, int depth);

        static QFont iconFont();

        static void textStyle(QLabel* label, int size, const QColor& color, bool bold = false);
    };

    class Qsu
    {
    public:
        static String from(const QString& str);
        static String from(const QVariant& str);

        static QString to(const String& str);
    };

}  // namespace Rt2::View
