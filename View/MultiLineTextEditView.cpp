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
#include "View/MultiLineTextEditView.h"
#include <QBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QTextEdit>
#include <QWidget>
#include "States/MultiLineTextEdit.h"
#include "View/Qu.h"
#include "View/States/State.h"
#include "ViewModel/ViewModel.h"

namespace Rt2::View
{
    MultiLineTextEditView::MultiLineTextEditView(QWidget* parent) :
        View(parent, new Visual::MultiLineTextEdit(), VisualFlag::ApplyOnShow)
    {
        construct();
    }

    MultiLineTextEditView::~MultiLineTextEditView() = default;

    void MultiLineTextEditView::construct()
    {
        _edit = Style::Widget::textEdit();
        _edit->setObjectName("MultiLineTextEditView");
        constructView(_edit);
        _edit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Style::Constraint::minimum(this, Style::Ctrl::BaseHeight);

        _model.addInput(
            [=](const String& text)
            {
                RT_GUARD_CHECK_VOID(_edit)
                _edit->setText(Qsu::to(text));
            });

        connect(_edit,
                &QTextEdit::textChanged,
                this,
                &MultiLineTextEditView::textChanged);
    }

    void MultiLineTextEditView::setText(const String& text)
    {
        _model.setValue(text);
    }

    void MultiLineTextEditView::setReadonly(const bool v) const
    {
        RT_GUARD_CHECK_VOID(_edit)
        _edit->setReadOnly(v);
    }

    String MultiLineTextEditView::text() const
    {
        return _model.value();
    }

    void MultiLineTextEditView::addOutput(const StringModel::Observer& type)
    {
        _model.addOutput(type);
    }

    void MultiLineTextEditView::textChanged()
    {
        RT_GUARD_CHECK_VOID(_edit)
        _model.setValue(Qsu::from(_edit->toPlainText()), ViewModel::OUTPUT);
    }

}  // namespace Rt2::View
