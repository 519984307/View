#include "StyleSheetWriter.h"

#include "Qu.h"
#include "Utils/StackStream.h"
#include "Utils/StreamConverters/Hex.h"

namespace Rt2::View
{
    StyleSheetWriter::StyleSheetWriter()
    {
        _out._push(&_data);
    }

    StyleSheetWriter::StyleSheetWriter(OStream* stream)
    {
        _out._push(stream);
    }

    StyleSheetWriter::~StyleSheetWriter()
    {
        _out.flush();
    }

    QString StyleSheetWriter::toString()
    {
        _out.flush();
        return Qsu::to(_data.str());
    }

    void StyleSheetWriter::begin()
    {
        _out.print('{');
    }

    void StyleSheetWriter::begin(const String& widget)
    {
        _out.print(widget, '{');
    }

    void StyleSheetWriter::outline(const qreal& v)
    {
        _out.print("outline:", v, ';');
    }

    void StyleSheetWriter::backgroundColor(const QColor& col)
    {
        _out.print("background-color:#",
                   Hex((uint8_t)Min(col.red(), 0xFF)),
                   Hex((uint8_t)Min(col.green(), 0xFF)),
                   Hex((uint8_t)Min(col.blue(), 0xFF)),
                   ';');
    }

    void StyleSheetWriter::selectionBackgroundColor(const QColor& col)
    {
        _out.print("selection-background-color:#",
                   Hex((uint8_t)Min(col.red(), 0xFF)),
                   Hex((uint8_t)Min(col.green(), 0xFF)),
                   Hex((uint8_t)Min(col.blue(), 0xFF)),
                   ';');
    }

    void StyleSheetWriter::selectionColor(const QColor& col)
    {
        _out.print("selection-color:#",
                   Hex((uint8_t)Min(col.red(), 0xFF)),
                   Hex((uint8_t)Min(col.green(), 0xFF)),
                   Hex((uint8_t)Min(col.blue(), 0xFF)),
                   ';');
    }

    void StyleSheetWriter::showSelectedDecoration(bool v)
    {
        _out.print("show-decoration-selected:", (v ? 1 : 0), ';');
    }

    void StyleSheetWriter::noBorder()
    {
        _out.print("border:none;");
    }

    void StyleSheetWriter::border(const QColor& col, qreal size)
    {
        _out.print("border:",
                   size,
                   "px solid #",
                   Hex((uint8_t)Min(col.red(), 0xFF)),
                   Hex((uint8_t)Min(col.green(), 0xFF)),
                   Hex((uint8_t)Min(col.blue(), 0xFF)),
                   ";");
    }

    void StyleSheetWriter::borderLeft(const QColor& col, qreal size)
    {
        _out.print("border-left:",
                   size,
                   "px solid #",
                   Hex((uint8_t)Min(col.red(), 0xFF)),
                   Hex((uint8_t)Min(col.green(), 0xFF)),
                   Hex((uint8_t)Min(col.blue(), 0xFF)),
                   ";");
    }

    void StyleSheetWriter::borderRight(const QColor& col, qreal size)
    {
        _out.print("border-right:",
                   size,
                   "px solid #",
                   Hex((uint8_t)Min(col.red(), 0xFF)),
                   Hex((uint8_t)Min(col.green(), 0xFF)),
                   Hex((uint8_t)Min(col.blue(), 0xFF)),
                   ";");
    }

    void StyleSheetWriter::borderTop(const QColor& col, qreal size)
    {
        _out.print("border-top:",
                   size,
                   "px solid #",
                   Hex((uint8_t)Min(col.red(), 0xFF)),
                   Hex((uint8_t)Min(col.green(), 0xFF)),
                   Hex((uint8_t)Min(col.blue(), 0xFF)),
                   ";");
    }

    void StyleSheetWriter::borderBottom(const QColor& col, qreal size)
    {
        _out.print("border-bottom:",
                   size,
                   "px solid #",
                   Hex((uint8_t)Min(col.red(), 0xFF)),
                   Hex((uint8_t)Min(col.green(), 0xFF)),
                   Hex((uint8_t)Min(col.blue(), 0xFF)),
                   ";");
    }

    void StyleSheetWriter::borderRadius(qreal size)
    {
        _out.print("border-radius:", size, "px;");
    }

    void StyleSheetWriter::minSize(const QSizeF& sz)
    {
        minWidth(sz.width());
        minHeight(sz.height());
    }

    void StyleSheetWriter::minWidth(const qreal& sz)
    {
        _out.print("min-width:", sz, "px;");
    }

    void StyleSheetWriter::minHeight(const qreal& sz)
    {
        _out.print("min-height:", sz, "px;");
    }

    void StyleSheetWriter::maxSize(const QSizeF& sz)
    {
        maxWidth(sz.width());
        maxHeight(sz.height());
    }

    void StyleSheetWriter::maxWidth(const qreal& sz)
    {
        _out.print("max-width:", sz, "px;");
    }

    void StyleSheetWriter::maxHeight(const qreal& sz)
    {
        _out.print("max-height:", sz, "px;");
    }

    void StyleSheetWriter::noBackground()
    {
        _out.print("background:none;");
    }

    void StyleSheetWriter::color(const QColor& col)
    {
        _out.print("color:#",
                   Hex((uint8_t)Min(col.red(), 0xFF)),
                   Hex((uint8_t)Min(col.green(), 0xFF)),
                   Hex((uint8_t)Min(col.blue(), 0xFF)),
                   ';');
    }

    void StyleSheetWriter::fontSize(const int& size)
    {
        _out.print("font-size:", size, "pt;");
    }

    void StyleSheetWriter::width(const int& size)
    {
        _out.print("width:", size, "px;");
    }

    void StyleSheetWriter::height(const int& size)
    {
        _out.print("height:", size, "px;");
    }

    void StyleSheetWriter::padding(const int& v)
    {
        _out.print("padding:", v, "px;");
    }

    void StyleSheetWriter::padding(const int& l, const int& t, const int& r, const int& b)
    {
        _out.print("padding: ", l, "px ", t, "px ", r, "px ", b, "px;");
    }

    void StyleSheetWriter::paddingLeft(const int& v)
    {
        _out.print("padding-left:", v, "px;");
    }

    void StyleSheetWriter::paddingTop(const int& v)
    {
        _out.print("padding-top:", v, "px;");
    }

    void StyleSheetWriter::paddingRight(const int& v)
    {
        _out.print("padding-right:", v, "px;");
    }

    void StyleSheetWriter::paddingBottom(const int& v)
    {
        _out.print("padding-bottom:", v, "px;");
    }

    void StyleSheetWriter::margin(const int& v)
    {
        _out.print("margin: ", v, "px;");
    }

    void StyleSheetWriter::margin(const int& l, const int& t, const int& r, const int& b)
    {
        _out.print("margin: ", l, "px ", t, "px ", r, "px ", b, "px;");
    }

    void StyleSheetWriter::marginLeft(const int& v)
    {
        _out.print("margin-left:", v, "px;");
    }

    void StyleSheetWriter::marginTop(const int& v)
    {
        _out.print("margin-top:", v, "px;");
    }

    void StyleSheetWriter::marginRight(const int& v)
    {
        _out.print("margin-right:", v, "px;");
    }

    void StyleSheetWriter::marginBottom(const int& v)
    {
        _out.print("margin-bottom:", v, "px;");
    }

    void StyleSheetWriter::end()
    {
        _out.print('}');
    }

}  // namespace Rt2::View