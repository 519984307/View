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
#include "View/Style.h"

namespace Rt2::View::Visual
{

    class Data
    {
    private:
        mutable QString _value;

        int      _fontSize                 = {Style::Size::None};
        QColor   _backgroundColor          = {Style::Misc::Empty};
        QColor   _borderColor              = {Style::Misc::Empty};
        QColor   _foregroundColor          = {Style::Misc::Empty};
        QColor   _highlightBackgroundColor = {Style::Misc::Transparent};
        QColor   _highlightForegroundColor = {Style::Misc::Transparent};
        qreal    _radius                   = {Style::Size::None};
        QMargins _border                   = {Style::Margin::None};
        QMargins _padding                  = {Style::Margin::None};
        QMargins _margin                   = {Style::Margin::None};
        bool     _dirty                    = {true};

        void update( const QString& name) const;

    public:
        void setBackgroundColor(const QColor& col);
        void setForegroundColor(const QColor& col);
        void setHighlightBackgroundColor(const QColor& col);
        void setHighlightForegroundColor(const QColor& col);
        void setBorderColor(const QColor& col);

        const QColor& backgroundColor() const;
        const QColor& borderColor() const;
        const QColor& foregroundColor() const;
        const QColor& highlightBackgroundColor() const;
        const QColor& highlightForegroundColor() const;

        void setBorderRadius(const qreal v);

        const qreal& radius() const;

        void setBorder(const QMargins& col);
        void setBorder(int v);
        void setBorder(int start, int end);
        void setBorder(int left, int top, int right, int bottom);

        const QMargins& border() const;

        void setPadding(const QMargins& col);
        void setPadding(int v);
        void setPadding(int start, int end);
        void setPadding(int left, int top, int right, int bottom);

        const QMargins& padding() const;

        void setMargin(const QMargins& col);
        void setMargin(int v);
        void setMargin(int start, int end);
        void setMargin(int left, int top, int right, int bottom);

        const QMargins& margin() const;

        void setFontSize(const int& size);

        const int& fontSize() const;

        const QString& value(const QString& name = "") const;

        void mark();
    public:
        Data() = default;


        static void clearBackground(Data& v);
    };

    inline const QColor& Data::backgroundColor() const
    {
        return _backgroundColor;
    }

    inline const QColor& Data::borderColor() const
    {
        return _borderColor;
    }

    inline const QColor& Data::foregroundColor() const
    {
        return _foregroundColor;
    }

    inline const QColor& Data::highlightBackgroundColor() const
    {
        return _highlightBackgroundColor;
    }

    inline const QColor& Data::highlightForegroundColor() const
    {
        return _highlightForegroundColor;
    }

    inline const QMargins& Data::border() const
    {
        return _border;
    }

    inline const qreal& Data::radius() const
    {
        return _radius;
    }

    inline const QMargins& Data::padding() const
    {
        return _padding;
    }

    inline const QMargins& Data::margin() const
    {
        return _margin;
    }

    inline const int& Data::fontSize() const
    {
        return _fontSize;
    }

    inline void Data::mark()
    {
        _dirty = true;
    }

}  // namespace Rt2::View::Visual
