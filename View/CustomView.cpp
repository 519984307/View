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

    void CustomView::setColor(const QPalette::ColorRole role, const QColor& col)
    {
        Qu::setColor(this, role, col);
    }

    void CustomView::setBackgroundColor(const QColor& col)
    {
        setColor(QPalette::PlaceholderText, col);
    }

    void CustomView::setBorderColor(const QColor& col)
    {
        setColor(QPalette::AlternateBase, col);
    }

    void CustomView::setBorder(const QMargins& border)
    {
        setContentsMargins(border);
    }

    void CustomView::setBorder(int v)
    {
        setBorder({v, v, v, v});
    }

    void CustomView::setBorder(int start, int end)
    {
        setBorder({start, 0, end, 0});
    }

    void CustomView::setBorder(int left, int top, int right, int bottom)
    {
        setBorder({left, top, right, bottom});
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
        setBorder(Metrics::borderSizeThin);
        setBorderColor(Colors::Border);
        setBackgroundColor(Colors::Background);
        setPadding(Metrics::borderSizeThick);
    }

    void CustomView::paintEvent(QPaintEvent* event)
    {
        QPainter paint(this);
        paint.setRenderHint(QPainter::Antialiasing);

        QRectF   root{0, 0, (qreal)width(), (qreal)height()};

        QPalette pal = palette();
        paint.fillRect(root, pal.color(QPalette::AlternateBase));


        QRectF bg = root.marginsRemoved(contentsMargins());
        paint.fillRect(bg, pal.color(QPalette::PlaceholderText));

        const QRectF ctx = bg.marginsRemoved(_padding);
        render(paint, ctx);
    }

}  // namespace Rt2::View
