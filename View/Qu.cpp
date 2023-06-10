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
#include "View/Qu.h"
#include <QApplication>
#include <QBoxLayout>
#include <QFontDatabase>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include "View/TitleListWidget.h"
#include "Utils/Console.h"
#include "Utils/Definitions.h"
#include "Utils/StreamConverters/Tab.h"
#include "View/Colors.h"
#include "View/DefaultStyleSheet.h"
#include "View/FlatIconButtonView.h"
#include "View/IconButtonView.h"
#include "View/ItemListWidget.h"
#include "View/Metrics.h"
#include "View/Palette.h"
#include "View/PushButtonView.h"
#include "View/StyleSheetWriter.h"

static int symbolLink()
{
    Q_INIT_RESOURCE(Icons);
    return 0;
}

namespace Rt2::View
{
    using Mt = Metrics;

    void Qu::initResources(QApplication& app)
    {
        symbolLink();
        QFontDatabase::addApplicationFont(":/fonts/IconFont.ttf");
        QFontDatabase::addApplicationFont(":/fonts/JetBrainsMono-Thin.ttf");
        Palette::applyInternal();
        writeStyleSheet(app);

        QFont fnt("Segoe UI");
        fnt.setPointSize(Metrics::defaultTextSize);
        QApplication::setFont(fnt);
    }

    void Qu::dropShadow(QLinearGradient& gradient,
                        const QRectF&    into,
                        const QColor&    base)
    {
        qreal r;
        if (into.height() > 0)
            r = 20.0 * (1.0 / into.height());
        else
            r = 0.001;

        gradient.setStart(into.topLeft());
        gradient.setFinalStop(into.bottomLeft());
        gradient.setColorAt(0.000, base.darker(150));
        gradient.setColorAt(r, base);
        gradient.setColorAt(1.000, base);
    }

    void Qu::fit(QWidget* widget)
    {
        RT_GUARD_CHECK_VOID(widget)
        widget->setContentsMargins(Mt::gm, Mt::gm, Mt::gm, Mt::gm);
    }

    QWidget* Qu::box(const QColor& col, QWidget* parent)
    {
        QWidget* box = new QWidget(parent);
        fit(box);
        StyleSheetWriter w;
        w.backgroundColor(col);
        w.noBorder();
        w.margin(1);
        box->setStyleSheet(w.toString());
        return box;
    }

    QWidget* Qu::separator(const QColor& col, QWidget* parent)
    {
        QWidget*         box = new QWidget(parent);
        StyleSheetWriter ssw;
        ssw.borderBottom(col, 1);
        ssw.height(2);
        ssw.minHeight(2);
        ssw.margin(2);
        box->setStyleSheet(ssw.toString());
        return box;
    }

    QWidget* Qu::separator(
        const Qt::Orientation& orientation,
        const int              size,
        const QColor&          col,
        QWidget*               parent)
    {
        QWidget* box = new QWidget(parent);
        if (orientation == Qt::Horizontal)
        {
            StyleSheetWriter w;
            w.backgroundColor(col);
            w.height(size);
            w.minHeight(size);
            w.noBorder();
            box->setStyleSheet(w.toString());
        }
        else
        {
            StyleSheetWriter w;
            w.backgroundColor(col);
            w.width(size);
            w.minWidth(size);
            w.noBorder();
            box->setStyleSheet(w.toString());
        }
        return box;
    }

    QLabel* Qu::text(const String& str,
                     const QColor& col,
                     QWidget*      parent)
    {
        return text(str, Metrics::h7, col, parent);
    }

    QLabel* Qu::text(const String& str,
                     const int&    size,
                     const QColor& color,
                     QWidget*      parent)
    {
        QLabel*          la = new QLabel(Qsu::to(str), parent);
        StyleSheetWriter style;
        style.fontSize(size);
        style.noBackground();
        style.color(color);
        la->setStyleSheet(style.toString());

        return la;
    }

    LabelView* Qu::label(const String& str,
                         const int&    size,
                         const QColor& color,
                         QWidget*      parent)
    {
        LabelView* la = new LabelView(Qsu::to(str), parent);

        StyleSheetWriter style;
        style.fontSize(size);
        style.noBackground();
        style.color(color);
        la->setStyleSheet(style.toString());

        return la;
    }

    QLabel* Qu::emphasis(
        const String& str,
        const int&    size,
        const int&    level,
        QWidget*      parent)
    {
        return text(str, size, Colors::Emphasis[Clamp(level, 0, 5)], parent);
    }

    void Qu::setColor(QWidget*                  widget,
                      const QPalette::ColorRole role,
                      const QColor&             value)
    {
        RT_GUARD_CHECK_VOID(widget)

        QPalette pal = widget->palette();
        pal.setColor(role, value);
        widget->setPalette(pal);
    }

    void Qu::setBackground(QWidget* widget, const QColor& value)
    {
        RT_GUARD_CHECK_VOID(widget)

        widget->setAutoFillBackground(true);
        setColor(widget, QPalette::Window, value);
        setColor(widget, QPalette::Base, value);
    }

    void Qu::setForeground(QWidget* widget, const QColor& value)
    {
        RT_GUARD_CHECK_VOID(widget)

        setColor(widget, QPalette::WindowText, value);
        setColor(widget, QPalette::Text, value);
    }

    QColor Qu::opacity(const QColor& value, const int alpha)
    {
        QColor color = value;
        color.setAlpha(alpha);
        return color;
    }

    void Qu::clearSpace(QObject* obj)
    {
        RT_GUARD_CHECK_VOID(obj)

        if (isLayout(obj))
            ((QLayout*)obj)->setSpacing(0);
    }

    bool Qu::isLabel(const QObject* obj)
    {
        RT_GUARD_CHECK_RET(obj, false)

        return obj->inherits("QLabel");
    }

    bool Qu::isWidget(const QObject* obj)
    {
        RT_GUARD_CHECK_RET(obj, false)

        return obj->inherits("QWidget");
    }

    bool Qu::isLayout(const QObject* obj)
    {
        RT_GUARD_CHECK_RET(obj, false)

        return obj->inherits("QLayout");
    }

    void Qu::fit(QLayout* layout)
    {
        RT_GUARD_CHECK_VOID(layout)

        layout->setContentsMargins(Mt::gm, Mt::gm, Mt::gm, Mt::gm);
        layout->setSpacing(Mt::gs);
    }

    QVBoxLayout* Qu::vertical(QWidget* parent)
    {
        const auto layout = new QVBoxLayout(parent);
        fit(layout);
        return layout;
    }

    QHBoxLayout* Qu::horizontal(QWidget* parent)
    {
        const auto layout = new QHBoxLayout(parent);
        fit(layout);
        return layout;
    }

    QSplitter* Qu::split(QWidget* a, QWidget* b, const Qt::Orientation ori, QWidget* parent)
    {
        // fall back cases
        if (!a) a = box();
        if (!b) b = box();

        QSplitter* spl = new QSplitter(parent);
        spl->setOrientation(ori);
        spl->addWidget(a);
        spl->addWidget(b);
        return spl;
    }

    QLabel* Qu::title(const String& str,
                      const int&    size,
                      const QColor& col,
                      QWidget*      parent)
    {
        return text(str, size, col, parent);
    }

    QHBoxLayout* Qu::titleList(const String&        str,
                               const QWidgetList&   items,
                               const int&           size,
                               const QColor&        color,
                               const Qt::Alignment& alignment)
    {
        const auto lo = horizontal();
        lo->setContentsMargins(Metrics::borderThick);

        lo->addWidget(text(str, size, color), 1, alignment);
        lo->addStretch();

        for (const auto item : items)
            lo->addWidget(item);

        return lo;
    }

    QWidget* Qu::titleWidget(
        const String&        str,
        const QWidgetList&   items,
        const int&           size,
        const int&           height,
        const QMargins&      margins,
        const QColor&        color,
        const QColor&        background,
        const Qt::Alignment& alignment,
        QWidget*             parent)
    {
        // clang-format off
        return new TitleListWidget(
            str, items, size, height, margins, 
            color, background, alignment, parent);
        // clang-format on
    }

    QWidget* Qu::itemList(
        const QWidgetList& items,
        const int&         size,
        const QColor&      color,
        const QColor&      background)
    {
        return new ItemListWidget(items, size, Metrics::borderThin, color, background);
    }

    IconButtonView* Qu::icon(const IconMap ico, QWidget* parent)
    {
        return new IconButtonView(ico, parent);
    }

    FlatIconButtonView* Qu::flatIcon(const IconMap ico, QWidget* parent)
    {
        return new FlatIconButtonView(ico, parent);
    }

    QPushButton* Qu::flatButton(QWidget* parent)
    {
        const auto button = new QPushButton(parent);
        fit(button);
        button->setMaximumSize(Metrics::ctrlMin);
        button->setFlat(true);
        return button;
    }

    PushButtonView* Qu::button(const String& label, QWidget* parent)
    {
        return new PushButtonView(label, parent);
    }

    void Qu::logRecursive(const QObject* root, const int depth)
    {
        if (!root)
            return;

        const uint8_t stackDepth = (uint8_t)(depth * 2);

        Console::println(
            Tab(stackDepth),
            '<',
            root->metaObject()->className(),
            '>');

        const QObjectList& objectList = root->children();

        for (const auto& object : objectList)
            logRecursive(object, depth + 1);

        Console::println(
            Tab(stackDepth),
            '<',
            '/',
            root->metaObject()->className(),
            '>');
    }

    QFont Qu::iconFont()
    {
        QFont font("ViewIcon");
        font.setPointSize(Metrics::iconFontSize);
        return font;
    }

    QFont Qu::fixedWidthFont()
    {
        QFont font("JetBrains Mono Thin");
        font.setPointSize(Metrics::h6);
        return font;
    }

    void Qu::textStyle(QLabel* label, const int size, const QColor& color, bool bold)
    {
        setColor(label, QPalette::WindowText, color);
        QFont fnt = label->font();
        fnt.setPointSize(size);
        fnt.setBold(bold);
        label->setFont(fnt);
    }

    QRectF Qu::measure(const String& str, const int size)
    {
        QFont fnt = QApplication::font();
        fnt.setPointSize(size);

        const QFontMetricsF fm(fnt);
        return fm.boundingRect(Qsu::to(str));
    }

    String Qsu::from(const QString& str)
    {
        return str.toStdString();
    }

    String Qsu::from(const QVariant& str)
    {
        return str.toString().toStdString();
    }

    QString Qsu::to(const String& str)
    {
        return QString::fromStdString(str);
    }

    QVariant Qsu::variant(const String& str)
    {
        return {to(str)};
    }

    String Qsu::wrap(const String& str, const int width, const int maxWidth)
    {
        String wn;
        int    cy = 0;
        for (const char ch : str)
        {
            if (cy * width > maxWidth)
            {
                wn.push_back('\n');
                cy = 0;
            }
            wn.push_back(ch);
            ++cy;
        }
        return wn;
    }

    QPoint Qmc::point(const QPointF& pt)
    {
        return {(int)pt.x(), (int)pt.y()};
    }

    QPointF Qmc::point(const QPoint& pt)
    {
        return {(qreal)pt.x(), (qreal)pt.y()};
    }

    QRect Qmc::rect(const QRectF& v)
    {
        return {(int)v.x(), (int)v.y(), (int)v.width(), (int)v.height()};
    }

    QRectF Qmc::rect(const QRect& v)
    {
        return {(qreal)v.x(), (qreal)v.y(), (qreal)v.width(), (qreal)v.height()};
    }

    QSizeF Qmc::size(const QSize& size)
    {
        return {(qreal)size.width(), (qreal)size.height()};
    }

    void Qu::writeStyleSheet(QApplication& app)
    {
        QString style;
        DefaultStyleSheet::get(style);
        app.setStyleSheet(style);
    }

}  // namespace Rt2::View
