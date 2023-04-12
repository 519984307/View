#include <QVBoxLayout>
#include "Colors.h"
#include "Metrics.h"
#include "Qu.h"
#include "View/LayoutView.h"

namespace Rt2::View
{

    LayoutView::LayoutView(QWidget* parent) :
        QWidget(parent)
    {
    }

    void LayoutView::setColor(const QPalette::ColorRole role, const QColor& col)
    {
        Qu::setColor(this, role, col);
    }

    void LayoutView::setBorderColor(const QColor& col)
    {
        Qu::setBackground(this, col);
    }

    void LayoutView::setBorder(const QMargins& border)
    {
        setContentsMargins(border);
    }

    void LayoutView::setBorder(int v)
    {
        setBorder({v, v, v, v});
    }

    void LayoutView::setBorder(int start, int end)
    {
        setBorder({start, 0, end, 0});
    }

    void LayoutView::setBorder(int left, int top, int right, int bottom)
    {
        setBorder({left, top, right, bottom});
    }

    void LayoutView::setPadding(const QMargins& margins) const
    {
        if (_content)
            _content->setContentsMargins(margins);
    }

    void LayoutView::setPadding(int v) const
    {
        setPadding({v, v, v, v});
    }

    void LayoutView::setPadding(int start, int end) const
    {
        setPadding({start, 0, end, 0});
    }

    void LayoutView::setPadding(int left, int top, int right, int bottom) const
    {
        setPadding({left, top, right, bottom});
    }

    void LayoutView::refresh()
    {
        update();
        if (_content)
            _content->invalidate();
    }

    void LayoutView::constructView(QLayout* content, int stretch)
    {
        _content = content;
        setBorder(Metrics::borderSizeThin);
        setBorderColor(Colors::Background);
        setPadding(Metrics::borderSizeThick);
        setLayout(content);
    }

}  // namespace Rt2::View
