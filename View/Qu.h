/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#pragma once
#include <QPalette>
#include "Colors.h"
#include "Metrics.h"
#include "Utils/String.h"
#include "View/IconFontMapping.h"
#include "View/LabelView.h"

class QGuiApplication;
class QLayout;
class QPushButton;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QSplitter;

namespace Rt2::View
{
    class WorkspaceTab;
    class PushButtonView;
    class FlatIconButtonView;
    class IconButtonView;

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

        static QSplitter* split(QWidget* a, QWidget* b, Qt::Orientation ori, QWidget* parent = nullptr);

        [[deprecated("use text")]] static QLabel* title(
            const String& str,
            const int&    size   = Metrics::h5,
            const QColor& col    = QColor(0xFF, 0x00, 0xFF),
            QWidget*      parent = nullptr);

        static QHBoxLayout* titleList(
            const String&        str,
            const QWidgetList&   items,
            const int&           size      = Metrics::h5,
            const QColor&        color     = Colors::Emphasis[5],
            const Qt::Alignment& alignment = {});

        static QWidget* itemList(
            const QWidgetList& items,
            const int&         size       = Metrics::h5,
            const QColor&      color      = Colors::Emphasis[5],
            const QColor&      background = Colors::CtrlBackground);

        static IconButtonView* icon(IconMap ico, QWidget* parent = nullptr);

        static FlatIconButtonView* flatIcon(IconMap ico, QWidget* parent = nullptr);

        static QPushButton* flatButton(QWidget* parent = nullptr);

        static PushButtonView* button(const String& label, QWidget* parent = nullptr);

        static QWidget* box(
            const QColor& col    = QColor(0xFF, 0x00, 0xFF),
            QWidget*      parent = nullptr);

        static QWidget* separator(
            const QColor& col    = QColor(0xFF, 0x00, 0xFF),
            QWidget*      parent = nullptr);

        static QLabel* text(
            const String& str,
            const QColor& col    = QColor(0xFF, 0x00, 0xFF),
            QWidget*      parent = nullptr);

        static QLabel* text(
            const String& str,
            const int&    size,
            const QColor& color  = QColor(0xFF, 0x00, 0xFF),
            QWidget*      parent = nullptr);

        static LabelView* label(
            const String& str,
            const int&    size,
            const QColor& color  = QColor(0xFF, 0x00, 0xFF),
            QWidget*      parent = nullptr);

        static QLabel* emphasis(
            const String& str,
            const int&    size,
            const int&    level,  // [0..5]
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

        static bool isLabel(const QObject* obj);

        static bool isWidget(const QObject* obj);

        static bool isLayout(const QObject* obj);

        static void logRecursive(const QObject* root, int depth);

        static QFont iconFont();

        static void textStyle(QLabel* label, int size, const QColor& color, bool bold = false);

        static QRectF measure(const String& str, int size);
    };

    class Qsu
    {
    public:
        static String from(const QString& str);
        static String from(const QVariant& str);

        static QString  to(const String& str);
        static QVariant variant(const String& str);
    };

    class Qmc
    {
    public:
        static QPoint  point(const QPointF& pt);
        static QPointF point(const QPoint& pt);

        static QRect  rect(const QRectF& v);
        static QRectF rect(const QRect& v);
        static QSizeF size(const QSize& size);
    };

}  // namespace Rt2::View
