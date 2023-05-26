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
class QBoxLayout;

namespace Rt2::View
{
    class LayoutView : public QWidget
    {
        Q_OBJECT
    protected:
        QLayout* _content{nullptr};

        void constructView(QLayout* content, int stretch = 1);

        QBoxLayout* boxLayout() const;

    public:
        explicit LayoutView(QWidget* parent = nullptr);

        void setColor(QPalette::ColorRole role, const QColor& col);

        void setBorderColor(const QColor& col);

        void setBorder(const QMargins& border);

        void setBorder(int v);

        void setBorder(int start, int end);

        void setBorder(int left, int top, int right, int bottom);

        void setPadding(const QMargins& margins) const;

        void setPadding(int v) const;

        void setPadding(int start, int end) const;

        void setPadding(int left, int top, int right, int bottom) const;

        void refresh();
    protected:

        void resizeEvent(QResizeEvent* event) override;
    };

}  // namespace Rt2::View
