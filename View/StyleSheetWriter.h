#pragma once
#include <QColor>
#include <QSizeF>
#include "Utils/StackStream.h"

namespace Rt2::View
{
    class StyleSheetWriter
    {
    private:
        OutputStreamStack _out;
        OutputStringStream _data;

    public:
        StyleSheetWriter();
        explicit StyleSheetWriter(OStream* stream);
        ~StyleSheetWriter();

        QString toString();

        void begin();

        void begin(const String& widget);

        void outline(const qreal& v);

        void backgroundColor(const QColor& col);

        void selectionBackgroundColor(const QColor& col);

        void selectionColor(const QColor& col);

        void showSelectedDecoration(bool v);

        void noBorder();

        void border(const QColor& col, qreal size);

        void borderLeft(const QColor& col, qreal size);

        void borderRight(const QColor& col, qreal size);

        void borderTop(const QColor& col, qreal size);

        void borderBottom(const QColor& col, qreal size);

        void borderRadius(qreal size);

        void minSize(const QSizeF& sz);

        void minWidth(const qreal& sz);

        void minHeight(const qreal& sz);

        void maxSize(const QSizeF& sz);

        void maxWidth(const qreal& sz);

        void maxHeight(const qreal& sz);

        
        void noBackground();

        void color(const QColor& col);

        void fontSize(const int& size);

        void width(const int& size);

        void height(const int& size);

        void padding(const int& v);

        void padding(const int& l, const int& t, const int& r, const int& b);

        void paddingLeft(const int& v);

        void paddingTop(const int& v);

        void paddingRight(const int& v);

        void paddingBottom(const int& v);

        void margin(const int& v);

        void margin(const int& l, const int& t, const int& r, const int& b);

        void marginLeft(const int& v);

        void marginTop(const int& v);

        void marginRight(const int& v);

        void marginBottom(const int& v);

        void end();
    };
}  // namespace Rt2::View
