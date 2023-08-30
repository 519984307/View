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
#include "View/CheckBoxView.h"
#include <QMouseEvent>
#include <QWidget>
#include "View/IconButtonView.h"
#include "View/LabelView.h"
#include "View/States/CheckBox.h"
#include "View/States/Data.h"
#include "View/States/State.h"
#include "View/StyleSheetWriter.h"
#include "View/View.h"

namespace Rt2::View
{
    constexpr int CheckFlags = VisualFlag::HoverState |
                               VisualFlag::ApplyOnShow |
                               VisualFlag::LeftReleaseActive;

    CheckBoxView::CheckBoxView(QWidget* parent) :
        View(parent, new Visual::CheckBox(), CheckFlags)
    {
        construct();
    }

    void CheckBoxView::construct()
    {
        _icon = Style::Widget::iconLabel(
            IconNone,
            Style::Icon::Normal,
            Style::Icon::Bounds);
        constructView(_icon);
        setMinimumSize(Style::Icon::Bounds);
        setMaximumSize(Style::Icon::Bounds);
        setChecked(false);
    }

    void CheckBoxView::setCheckedText(const bool v) const
    {
        RT_GUARD_CHECK_VOID(_icon)
        _icon->setText(v ? QString(QChar(IconCheck0)) : "");
    }

    void CheckBoxView::setChecked(const bool v)
    {
        setCheckedText(v);
        apply(VisualType::Normal);
        _check.setValue(v, ViewModel::OUTPUT);
    }

    void CheckBoxView::addInput(const BoolModel::Observer& ob)
    {
        _check.addInput(ob);
    }

    void CheckBoxView::addOutput(const BoolModel::Observer& ob)
    {
        _check.addOutput(ob);
    }

    void CheckBoxView::contentClicked()
    {
        setChecked(!isChecked());
        _check.dispatch(ViewModel::OUTPUT);
    }

}  // namespace Rt2::View
