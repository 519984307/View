#pragma once
#include <QPalette>
#include "Utils/String.h"

class QGuiApplication;
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
    private:
        static void writeStyleSheet(QApplication& app);

    public:
        static void initResources(QApplication& app);

        static void dropShadow(
            QLinearGradient& gradient,
            const QRectF&    into,
            const QColor&    base);

        static void fit(QWidget* widget);

        static void fit(QLayout* layout);

        static QVBoxLayout* vertical(QWidget* parent = nullptr);

        static QHBoxLayout* horizontal(QWidget* parent = nullptr);

        static QPushButton* flatButton(QWidget* parent = nullptr);

        static QWidget* box(
            QWidget*      parent = nullptr,
            const QColor& col    = QColor(0xFF, 0x00, 0xFF));

        static QWidget* separator(
            const QColor& col    = QColor(0xFF, 0x00, 0xFF),
            QWidget*      parent = nullptr);

        static QLabel* text(
            const String& str,
            const QColor& col    = QColor(0xFF, 0x00, 0xFF),
            QWidget*      parent = nullptr);

        static QLabel* title(
            const String& str,
            const QColor& col    = QColor(0xFF, 0x00, 0xFF),
            QWidget*      parent = nullptr);

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

    class Qmc
    {
    public:
        static QPoint  point(const QPointF& pt);
        static QPointF point(const QPoint& pt);
    };

}  // namespace Rt2::View
