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
#include "View/CustomView.h"
#include <QPainter>
#include <QVBoxLayout>
#include "View/Qu.h"

namespace Rt2::View
{

    CustomView::CustomView(QWidget* parent) :
        QWidget(parent)
    {
        setContentsMargins(0, 0, 0, 0);
        setUpdatesEnabled(true);
    }

    void CustomView::setFlags(const int vf)
    {
        _flags = vf;
        refresh();
    }

    QColor CustomView::backgroundColor() const
    {
        return _background;
    }

    QColor CustomView::borderColor() const
    {
        return _border;
    }

    QColor CustomView::highlightColor() const
    {
        return _highlight;
    }

    void CustomView::setBackgroundColor(const QColor& col)
    {
        _background = col;
    }

    void CustomView::setBorderColor(const QColor& col)
    {
        _border = col;
    }

    void CustomView::setHighlightColor(const QColor& col)
    {
        _highlight = col;
    }

    void CustomView::setMargin(const QMargins& v)
    {
        applyNotZero(CvMargin, v);
        _margin = v;
    }

    void CustomView::setMargin(int v)
    {
        setMargin({v, v, v, v});
    }

    void CustomView::setMargin(int start, int end)
    {
        setMargin({start, 0, end, 0});
    }

    void CustomView::setMargin(int left, int top, int right, int bottom)
    {
        setMargin({left, top, right, bottom});
    }

    void CustomView::setPadding(const QMargins& v)
    {
        applyNotZero(CvPadding, v);
        _padding = v;
    }

    void CustomView::setPadding(int v)
    {
        setPadding({v, v, v, v});
    }

    void CustomView::setPadding(int start, int end)
    {
        setPadding({start, 0, end, 0});
    }

    void CustomView::setPadding(int left, int top, int right, int bottom)
    {
        setPadding({left, top, right, bottom});
    }

    void CustomView::refresh()
    {
        update();
    }

    void CustomView::constructView()
    {
        setUpdatesEnabled(true);
        setFlags(0);
        setMargin(0);
        setPadding(0);

        setBorderColor(Style::Window::Border);
        setBackgroundColor(Style::Window::Background);
        setHighlightColor(Style::Window::Accent);
    }

    void CustomView::paintEvent(QPaintEvent* event)
    {
        QPainter paint(this);
        paint.setRenderHint(QPainter::Antialiasing);

        const QRectF base{0, 0, (qreal)width(), (qreal)height()};

        const QPalette colors  = palette();
        QRectF         modRect = base;

        if ((_flags & CvFullView) != 0)
        {
            render(paint, modRect);
            if (_flags & CvHighLightContent)
            {
                paint.setPen(QPen(_highlight, 1));
                paint.drawRect(base);
            }
        }
        else
        {
            QRectF preCvMargin = base;

            if ((_flags & CvMargin) != 0)
            {
                modRect     = modRect.marginsRemoved(_margin);
                preCvMargin = modRect;
                paint.fillRect(modRect, _border);
            }

            if ((_flags & CvPadding) != 0)
            {
                paint.fillRect(modRect, _background);
                modRect = modRect.marginsRemoved(_padding);
            }

            const QRect cv = paint.viewport();
            const QRect cw = paint.window();

            paint.setClipRect(modRect);
            render(paint, modRect);
            paint.setClipRect(base);

            paint.resetTransform();
            paint.setWindow(cw);
            paint.setViewport(cv);

            if (_flags & CvHighLightContent)
            {
                paint.setPen(QPen(_highlight, 1));
                paint.drawRect(preCvMargin);
            }
        }
    }

    void CustomView::applyNotZero(const int apply, const QMargins& test)
    {
        bool notZero = test.left() > 0;

        notZero = notZero || test.top() > 0;
        notZero = notZero || test.right() > 0;
        notZero = notZero || test.bottom() > 0;

        if (notZero)
        {
            if (_flags & CvFullView)
                _flags &= ~CvFullView;
            _flags |= apply;
        }
    }
}  // namespace Rt2::View
