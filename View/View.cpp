#include "View/View.h"
#include <QVBoxLayout>
#include "Colors.h"
#include "Metrics.h"
#include "Palette.h"
#include "Qu.h"

namespace Rt2::View
{

    View::View(QWidget* parent) :
        QWidget(parent)
    {
    }

    void View::setColor(const QPalette::ColorRole role, const QColor& col) const
    {
        if (_content)
            Qu::setColor(_content, role, col);
    }

    QColor View::backgroundColor() const
    {
        return palette().color(QPalette::Window);
    }

    QColor View::borderColor() const
    {
        return palette().color(QPalette::Base);
    }

    void View::setHighlightColor(const QColor& col)
    {
        _highlight = col;
    }

    void View::setBorderColor(const QColor& col)
    {
        Qu::setBackground(this, col);
    }

    void View::setBorder(const QMargins& border)
    {
        setContentsMargins(border);
    }

    void View::setBorder(int v)
    {
        setBorder({v, v, v, v});
    }

    void View::setBorder(int start, int end)
    {
        setBorder({start, 0, end, 0});
    }

    void View::setBorder(int left, int top, int right, int bottom)
    {
        setBorder({left, top, right, bottom});
    }

    void View::setBackgroundColor(const QColor& col) const
    {
        if (_content)
            Qu::setBackground(_content, col);
    }

    void View::setForegroundColor(const QColor& col) const
    {
        if (_content)
            Qu::setForeground(_content, col);
    }

    void View::setPadding(const QMargins& margins) const
    {
        if (_layout)
            _layout->setContentsMargins(margins);
    }

    void View::setPadding(int v) const
    {
        setPadding({v, v, v, v});
    }

    void View::setPadding(int start, int end) const
    {
        setPadding({start, 0, end, 0});
    }

    void View::setPadding(int left, int top, int right, int bottom) const
    {
        setPadding({left, top, right, bottom});
    }

    void View::setFontSize(const int size) const
    {
        if (_content)
        {
            QFont fnt = _content->font();
            fnt.setPointSize(size);
            _content->setFont(fnt);
        }
    }

    void View::refresh()
    {
        update();
        if (_content)
            _content->update();
    }

    void View::constructView(QWidget* content, const int stretch, const Qt::Alignment& al)
    {
        _content = content;
        _layout  = Qu::vertical();
        RT_ASSERT(_content)

        Palette::applyCtrlPalette(this);
        Palette::applyCtrlPalette(_content);

        setBackgroundColor(Colors::Background);
        setForegroundColor(Colors::Foreground);
        setBorder(1);
        setBorderColor(Colors::Border);
        setPadding(0);
        _highlight = Colors::Accent;

        _layout->addWidget(_content, stretch, al);
        setLayout(_layout);
    }

}  // namespace Rt2::View
