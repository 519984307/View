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
#include "View/LayoutView.h"
#include <QVBoxLayout>

#include "Utils/Definitions.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Palette.h"
#include "View/Qu.h"

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
        Qu::setBackground(this, col);  // this->Window
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

    void LayoutView::resizeEvent(QResizeEvent* event)
    {
        QWidget::resizeEvent(event);
        if (_content)
            _content->invalidate();
    }

    void LayoutView::constructView(QLayout* content, int stretch)
    {
        RT_ASSERT(content);
        _content = content;

        Palette::applyCtrlPalette(this);
        setMinimumSize(Metrics::ctrlMin);
        setBorder(Metrics::borderSizeThin);
        setBorderColor(Colors::Background);
        setPadding(Metrics::borderSizeThick);

        _content->setSizeConstraint(QLayout::SetMinAndMaxSize);
        setLayout(content);
    }

    QBoxLayout* LayoutView::boxLayout() const
    {
        if (_content)
        {
            if (_content->inherits("QBoxLayout"))
                return (QBoxLayout*)_content;
        }
        return nullptr;
    }

}  // namespace Rt2::View
