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

class QVBoxLayout;

namespace Rt2::View
{
    enum CustomViewFlags
    {
        CvFullView         = 0x01,
        CvMargin           = 0x02,
        CvPadding          = 0x04,
        CvHighLightContent = 0x08,
        CvDefaultFlags     = CvMargin | CvHighLightContent,
    };

    class CustomView : public QWidget
    {
        Q_OBJECT
    protected:
        QMargins _padding{0, 0, 0, 0};
        QMargins _margin{0, 0, 0, 0};
        int      _flags{CvDefaultFlags};
        QColor   _highlight;
        QColor   _background;
        QColor   _border;

    public:
        explicit CustomView(QWidget* parent = nullptr);

        void setFlags(int vf);

        QColor backgroundColor() const;

        QColor borderColor() const;

        QColor highlightColor() const;

        void setHighlightColor(const QColor& col);

        void setBackgroundColor(const QColor& col);

        void setBorderColor(const QColor& col);

        void setMargin(const QMargins& v);

        void setMargin(int v);

        void setMargin(int start, int end);

        void setMargin(int left, int top, int right, int bottom);

        void setPadding(const QMargins& v);

        void setPadding(int v);

        void setPadding(int start, int end);

        void setPadding(int left, int top, int right, int bottom);

        void refresh();

    protected:
        void constructView();

        void paintEvent(QPaintEvent* event) override;

        virtual void render(QPainter& paint, const QRectF& rect) = 0;

    private:

        void applyNotZero(int apply, const QMargins& test);

    };

}  // namespace Rt2::View
