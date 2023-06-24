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
#include "View/IconButtonView.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include "View/Qu.h"
#include "View/States/Data.h"
#include "View/States/Icon.h"
#include "View/StyleSheetWriter.h"

namespace Rt2::View
{
    constexpr int IconFlags = VisualFlag::HoverState;

    IconButtonView::IconButtonView(const IconMap icon, QWidget* parent) :
        View(parent, new Visual::Icon(), IconFlags)
    {
        construct(icon);
    }

    IconButtonView::~IconButtonView() = default;

    void IconButtonView::construct(const IconMap icon)
    {
        _icon = Style::Widget::iconLabel(icon, Style::Icon::Normal, Style::Icon::Bounds);
        constructView(_icon);
        Style::Constraint::fixed(this, Style::Icon::Bounds);
        apply(VisualType::Normal);
    }

    void IconButtonView::addOutput(const BoolModel::Observer& ot)
    {
        _model.addOutput(ot);
    }

    void IconButtonView::setFlat(const bool v)
    {
        setAttributeState(VisualAttribute::NoBackground, v);
        setBorder(0, VisualType::Normal);
        setForegroundColor(Style::PressedPrimary::Highlight, VisualType::Normal);
        setBorder(0, VisualType::Hover);
        setForegroundColor(Style::PressedPrimary::HighlightText, VisualType::Hover);
        setBorder(0, VisualType::Pressed);
        setForegroundColor(Style::PressedSecondary::BorderLight, VisualType::Pressed);
        apply(VisualType::Normal);
    }


    
    void IconButtonView::setIconSize(const int size)
    {
        RT_GUARD_CHECK_VOID(_icon)
        setFontSize(size, VisualType::Normal);
        setFontSize(size, VisualType::Hover);
        setFontSize(size, VisualType::Pressed);
        apply(VisualType::Normal);
    }

    void IconButtonView::setIcon(const int ico) const
    {
        RT_GUARD_CHECK_VOID(_icon)
        _icon->setText(QChar(Clamp<int>(ico, Style::Icon::FirstIcon, Style::Icon::LastIcon)));
    }

    int IconButtonView::icon() const
    {
        RT_GUARD_CHECK_RET(_icon, 0)
        if (const QString text = _icon->text(); text.isEmpty())
            return 0;
        else
            return text.at(0).cell();
    }


    void IconButtonView::mousePressEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)
        if (event->button() == Qt::LeftButton)
            apply(VisualType::Pressed);
        event->accept();
    }

    void IconButtonView::mouseReleaseEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event && _icon)

        apply(VisualType::Normal);
        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                _icon->geometry().contains(pt))
                _model.dispatch(ViewModel::OUTPUT);
        }
        event->accept();
    }

    bool IconButtonView::isPressed() const
    {
        return (_state & PRESSED) != 0;
    }

}  // namespace Rt2::View
