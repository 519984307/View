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
#include "Utils/String.h"
#include "Utils/TextStreamWriter.h"
#include "View/Style.h"


namespace Rt2::View
{
    class Qu
    {
    private:
        static void writeStyleSheet(QApplication& app);

    public:
        static void initResources(QApplication& app);

        static bool isLabel(const QObject* obj);

        static bool isWidget(const QObject* obj);

        static bool isLayout(const QObject* obj);

        static void logRecursive(const QObject* root, int depth);

        static QRectF measure(const String& str, int size);
        static QRectF measureQString(const QString& str, int size);
    };

    class Qsu
    {
    public:
        static String from(const QString& str);

        static String from(const QVariant& str);

        static QString to(const String& str);

        static QVariant variant(const String& str);

        static String wrap(const String& str, const int width, const int maxWidth);

        static QString color(const QColor& color);

        static QString name(const void* address);

        static String colorString(const QColor& color);

        template<typename ...Args>
        static QString format(Args&& ... args)
        {
            OutputStringStream oss;
            Ts::print(oss, (std::forward<Args>(args),...));
            return to(oss.str());
        }
    };

    class Qmc
    {
    public:
        static QPoint point(const QPointF& pt);

        static QPointF point(const QPoint& pt);

        static QRect rect(const QRectF& v);

        static QRectF rect(const QRect& v);

        static QSizeF size(const QSize& size);

        static QSize size(const QSizeF& size);
    };

}  // namespace Rt2::View
