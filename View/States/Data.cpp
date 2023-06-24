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
#include "View/States/Data.h"
#include "View/Qu.h"
#include "View/StyleSheetWriter.h"

namespace Rt2::View::Visual
{
    void Data::update(const QString& name) const
    {
        StyleSheetWriter style;
        if (!name.isEmpty())
            style.beginId(Qsu::from(name));

        if (!_padding.isNull())
            style.padding(_padding);

        if (!_margin.isNull())
            style.margin(_margin);

        if (!_border.isNull())
            style.border(_borderColor, _border);

        if (_radius > 0)
            style.borderRadius(_radius);

        if (_highlightBackgroundColor.alpha() > 0)
            style.selectionBackgroundColor(_highlightBackgroundColor);

        if (_highlightForegroundColor.alpha() > 0)
            style.selectionColor(_highlightForegroundColor);

        if (_backgroundColor.alpha() > 0)
            style.backgroundColor(_backgroundColor);
        else
            style.noBackground();

        style.color(_foregroundColor);

        if (_fontSize > 0)
            style.fontSize(_fontSize);
        if (!name.isEmpty())
            style.end();
        _value = style.toString();
    }

    void Data::setBackgroundColor(const QColor& col)
    {
        _backgroundColor = col;
        mark();
    }

    void Data::setBorderColor(const QColor& col)
    {
        _borderColor = col;
        mark();
    }

    void Data::setForegroundColor(const QColor& col)
    {
        _foregroundColor = col;
        mark();
    }

    void Data::setBorder(const QMargins& col)
    {
        _border = col;
        mark();
    }

    void Data::setBorder(int v)
    {
        setBorder({v, v, v, v});
    }

    void Data::setBorder(int start, int end)
    {
        setBorder({start, 0, end, 0});
    }

    void Data::setBorder(int left, int top, int right, int bottom)
    {
        setBorder({left, top, right, bottom});
    }

    void Data::setPadding(int v)
    {
        setPadding({v, v, v, v});
    }

    void Data::setPadding(int start, int end)
    {
        setPadding({start, 0, end, 0});
    }

    void Data::setPadding(int left, int top, int right, int bottom)
    {
        setPadding({left, top, right, bottom});
    }

    void Data::setMargin(int v)
    {
        setMargin({v, v, v, v});
    }

    void Data::setMargin(int start, int end)
    {
        setMargin({start, 0, end, 0});
    }

    void Data::setMargin(int left, int top, int right, int bottom)
    {
        setMargin({left, top, right, bottom});
    }

    void Data::setFontSize(const int& size)
    {
        _fontSize = size;
        mark();
    }

    void Data::setBorderRadius(const qreal v)
    {
        _radius = v;
        mark();
    }

    void Data::setHighlightBackgroundColor(const QColor& col)
    {
        _highlightBackgroundColor = col;
        mark();
    }

    void Data::setHighlightForegroundColor(const QColor& col)
    {
        _highlightForegroundColor = col;
        mark();
    }

    void Data::setPadding(const QMargins& col)
    {
        _padding = col;
        mark();
    }

    void Data::setMargin(const QMargins& col)
    {
        _margin = col;
        mark();
    }

    const QString& Data::value(const QString& name) const
    {
        if (_dirty) update(name);
        return _value;
    }

    void Data::clearBackground(Data& v)
    {
        v.setBorder(0);
        v.setBorderRadius(0);
        v.setBackgroundColor(Style::Misc::Transparent);
        v.setBorderColor(Style::Misc::Transparent);
    }
}  // namespace Rt2::View::Visual
