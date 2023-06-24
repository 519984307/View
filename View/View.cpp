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
#include "View/View.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include "States/Default.h"
#include "View/Qu.h"
#include "View/States/State.h"
#include "View/StyleSheetWriter.h"

namespace Rt2::View
{
    View::View(QWidget* parent, VisualState* states, const int eventFlags) :
        StateView(parent, states, eventFlags)
    {
    }

    void View::constructView(QWidget* content, const int stretch, const Qt::Alignment& al)
    {
        _content = content;
        if (!_content) _content = Style::Widget::box();
        _layout = Style::Layout::v0();
        _layout->addWidget(_content, stretch, al);
        setAttribute(Qt::WA_TranslucentBackground);
        setLayout(_layout);
    }

    void View::refresh()
    {
        update();
    }

    void View::mousePressEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)
        if (_eventFlags & VisualFlag::LeftClickActive && event->button() == Qt::LeftButton)
        {
            if (clickHitEvent(event->position()))
            {
                event->accept();
                return;
            }
        }
        StateView::mousePressEvent(event);
    }

    void View::mouseReleaseEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)
        if (_eventFlags & VisualFlag::LeftReleaseActive && event->button() == Qt::LeftButton)
        {
            if (clickHitEvent(event->position()))
            {
                event->accept();
                return;
            }
        }
        StateView::mouseReleaseEvent(event);
    }

    bool View::clickHitEvent(const QPointF& co)
    {
        RT_GUARD_CHECK_RET(_content, false)
        if (const QPoint pt = Qmc::point(co);
            geometry().contains(pt) ||
            _content->geometry().contains(pt))
        {
            contentClicked();
            return true;
        }
        return false;
    }

}  // namespace Rt2::View
