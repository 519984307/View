#pragma once
#include <QBoxLayout>
#include <QWidget>
#include "Utils/String.h"

class QLabel;
class QHBoxLayout;

namespace Rt2::Widgets
{
    class Qu
    {
    public:
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
