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
#include <QWidget>
#include "View/Definitions.h"

class QVBoxLayout;

namespace Rt2::View
{
    class View : public QWidget
    {
        Q_OBJECT
    protected:
        QWidget*     _content{nullptr};
        QVBoxLayout* _layout{nullptr};
        QColor       _highlight;

        void constructView(
            QWidget*             content,
            int                  stretch = 1,
            const Qt::Alignment& al      = {});

    public:
        explicit View(QWidget* parent = nullptr);

        void setColor(QPalette::ColorRole role, const QColor& col) const;

        QColor backgroundColor() const;

        QColor borderColor() const;

        void setHighlightColor(const QColor& col);

        void setBorderColor(const QColor& col);

        void setBackgroundColor(const QColor& col) const;

        void setForegroundColor(const QColor& col) const;

        void setBorder(const QMargins& border);

        void setBorder(int v);

        void setBorder(int start, int end);

        void setBorder(int left, int top, int right, int bottom);

        void setPadding(const QMargins& margins) const;

        void setPadding(int v) const;

        void setPadding(int start, int end) const;

        void setPadding(int left, int top, int right, int bottom) const;

        void setFontSize(int size) const;

        void refresh();
    };

}  // namespace Rt2::View
