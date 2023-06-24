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
#include "View/States/Layout.h"

namespace Rt2::View
{

    LayoutView::LayoutView(QWidget* parent, VisualState* states) :
        StateView(parent, states ? states : new Visual::Layout(), VisualFlag::ApplyOnShow)
    {
        setMinimumSize(Style::Window::Panel);
    }

    LayoutView::~LayoutView() = default;

    void LayoutView::refresh() const
    {
        RT_GUARD_CHECK_VOID(_content)
        _content->invalidate();
    }

    void LayoutView::tinted(const bool v)
    {
        setAttribute(Qt::WA_TintedBackground, v);
    }

    void LayoutView::constructView(QLayout* content)
    {
        if (!content)
            content = Style::Layout::v0();

        _content = content;
        _content->setSizeConstraint(QLayout::SetMinAndMaxSize);
        tinted(true);

        this->setLayout(content);
        connect(this,
                &StateView::marginChanged,
                this,
                [this](const QMargins& m)
                {
                    RT_GUARD_CHECK_VOID(_content)
                    _content->setContentsMargins(m);
                });
    }

    QBoxLayout* LayoutView::boxLayout() const
    {
        RT_GUARD_CHECK_RET(_content, nullptr)
        if (_content->inherits("QBoxLayout"))
            return (QBoxLayout*)_content;
        return nullptr;
    }

}  // namespace Rt2::View
