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
#include "View/PushButtonView.h"
#include <QLabel>
#include <QMouseEvent>
#include "States/PushButton.h"
#include "View/Qu.h"

namespace Rt2::View
{

    PushButtonView::PushButtonView(QWidget* parent) :
        View(parent, new Visual::PushButton(), VisualFlag::HoverState | VisualFlag::ApplyOnShow)
    {
        construct();
    }

    PushButtonView::PushButtonView(const String& text, QWidget* parent) :
        View(parent, new Visual::PushButton(), VisualFlag::HoverState | VisualFlag::ApplyOnShow)
    {
        construct();
        setLabel(text);
    }

    PushButtonView::~PushButtonView() = default;

    void PushButtonView::construct()
    {
        _text = Style::Widget::centeredLabel(Style::Size::Button);
        setMinimumSize(Style::Size::Button);
        setMaximumHeight(Style::Size::Button.height());
        constructView(_text);
    }

    void PushButtonView::setLabel(const String& label) const
    {
        RT_GUARD_CHECK_VOID(_text)
        _text->setText(Qsu::to(label));
    }

    String PushButtonView::label() const
    {
        RT_GUARD_CHECK_RET(_text, "")
        return Qsu::from(_text->text());
    }

    void PushButtonView::addOutput(const BoolModel::Observer& ob)
    {
        _state.addOutput(ob);
    }

    void PushButtonView::mousePressEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)
        apply(VisualType::Pressed);
        event->accept();
    }

    void PushButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)

        bool inside = false;
        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                geometry().contains(pt) || _text->geometry().contains(pt))
            {
                _state.dispatch(ViewModel::OUTPUT);
                inside = true;
            }
        }

        if (inside)
            apply(VisualType::Hover);
        else
            apply(VisualType::Normal);
        event->accept();
    }

}  // namespace Rt2::View
