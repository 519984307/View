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
#include <QLineEdit>
#include <QSplitter>
#include "Utils/Console.h"
#include "Utils/Definitions.h"
#include "Utils/StreamConverters/Hex.h"
#include "Utils/StreamConverters/Tab.h"
#include "Utils/SymbolStream.h"
#include "View/DefaultStyleSheet.h"
#include "View/IconButtonView.h"
#include "View/ItemListWidget.h"
#include "View/LabelView.h"

static int symbolLink()
{
    Q_INIT_RESOURCE(Icons);
    return 0;
}

namespace Rt2::View
{
    void Qu::initResources(QApplication& app)
    {
        symbolLink();
        QFontDatabase::addApplicationFont(":/fonts/IconFont.ttf");
        QFontDatabase::addApplicationFont(":/fonts/JetBrainsMono-Thin.ttf");
        writeStyleSheet(app);

        QFont fnt(Style::Fonts::DefaultFamily);
        fnt.setPointSize(Style::Points::Pt10);
        QApplication::setFont(fnt);
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

    QRectF Qu::measure(const String& str, const int size)
    {
        return measureQString(Qsu::to(str), size);
    }

    QRectF Qu::measureQString(const QString& str, const int size)
    {
        QFont fnt = QApplication::font();
        fnt.setPointSize(size);

        const QFontMetricsF fm(fnt);
        return fm.boundingRect(str);
    }

    QString Qu::trimToFit(const QString& str, const QRectF& r, const int size)
    {
        if (const QRectF br = measureQString(str, size); br.width() > r.width())
        {
            auto over = (int)(br.width() - r.width()) / size;
            if (over < str.size())
            {
                over += 5;
                String s = str.toStdString();
                while (over--)
                    s.pop_back();
                s.append("...");
                return Qsu::to(s);
            }
        }
        return str;
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

    QString Qsu::to(const uint8_t* buf, size_t size)
    {
        return to({(const char*)buf, size});
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

    QString Qsu::wrapStyle(const String& name, const uint8_t *style, size_t len)
    {
        return Qsu::to(Su::join('#', name, '{', String{(char*)style, len}, '}'));
    }

    QString Qsu::color(const QColor& color)
    {
        return to(colorString(color));
    }

    QString Qsu::name(const void* address)
    {
        return to(SymbolStream::toString((size_t)address, SymbolStream::HexB, 2));
    }

    String Qsu::colorString(const QColor& color)
    {
        return Su::join(Hex((uint8_t)Min(color.red(), 0xFF)),
                        Hex((uint8_t)Min(color.green(), 0xFF)),
                        Hex((uint8_t)Min(color.blue(), 0xFF)));
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

    QSize Qmc::size(const QSizeF& size)
    {
        return {(int)size.width(), (int)size.height()};
    }

    void Qu::writeStyleSheet(QApplication& app)
    {
        QString style;
        DefaultStyleSheet::get(style);
        app.setStyleSheet(style);
    }

}  // namespace Rt2::View
