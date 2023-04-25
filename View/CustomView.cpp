#include "View/CustomView.h"
#include <QPainter>
#include <QVBoxLayout>
#include "Colors.h"
#include "Metrics.h"
#include "Palette.h"
#include "Qu.h"

namespace Rt2::View
{

    CustomView::CustomView(QWidget* parent) :
        QWidget(parent)
    {
    }

    void CustomView::setFlags(int vf)
    {
        _flags = vf;
        refresh();
    }

    void CustomView::setColor(const QPalette::ColorRole role, const QColor& col)
    {
        Qu::setColor(this, role, col);
    }

    void CustomView::setHighlightColor(const QColor& col)
    {
        _highlight = col;
    }

    QColor CustomView::backgroundColor() const
    {
        return palette().color(Colors::CustomViewBackground);
    }

    QColor CustomView::borderColor() const
    {
        return palette().color(Colors::CustomViewBorder);
    }

    void CustomView::setBackgroundColor(const QColor& col)
    {
        setColor(Colors::CustomViewBackground, col);
    }

    void CustomView::setBorderColor(const QColor& col)
    {
        setColor(Colors::CustomViewBorder, col);
    }

    void CustomView::setMargin(const QMargins& border)
    {
        setContentsMargins(border);
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

    void CustomView::setPadding(const QMargins& margins)
    {
        _padding = margins;
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

        Palette::applyCtrlPalette(this);

        setMargin(1);
        setPadding(0);

        setBorderColor(Colors::CtrlBackgroundLight);
        setBackgroundColor(Colors::CtrlBackground);
        _highlight = Colors::BorderLight;
    }

    void CustomView::paintEvent(QPaintEvent* event)
    {
        QPainter paint(this);
        paint.setRenderHint(QPainter::Antialiasing);

        const QRectF base{0, 0, (qreal)width(), (qreal)height()};

        const QPalette colors  = palette();
        QRectF         modRect = base;

        if ((_flags & CvFullView) != 0)
            render(paint, modRect);
        else
        {
            if ((_flags & CvMargin) != 0)
            {
                paint.fillRect(modRect, colors.color(Colors::CustomViewBorder));
                modRect = modRect.marginsRemoved(contentsMargins());
            }

            if ((_flags & CvPadding) != 0)
            {
                paint.fillRect(modRect, colors.color(Colors::CustomViewBackground));
                modRect = modRect.marginsRemoved(_padding);
            }

            paint.setClipRect(modRect);
            render(paint, modRect);
            paint.setClipRect(base);
        }

        if (_flags & CvHighLightContent)
        {
            paint.setPen(QPen(_highlight, 1));
            paint.drawRect(modRect.adjusted(1, 1, -1, -1));
        }
    }

}  // namespace Rt2::View
