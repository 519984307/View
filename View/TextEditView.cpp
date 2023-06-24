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
#include "View/TextEditView.h"
#include <QBoxLayout>
#include <QLineEdit>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>
#include "States/TextEdit.h"
#include "View/Qu.h"
#include "View/States/State.h"
#include "ViewModel/ViewModel.h"

namespace Rt2::View
{
    TextEditView::TextEditView(QWidget* parent) :
        View(parent, new Visual::TextEdit(), VisualFlag::HoverState | VisualFlag::ApplyOnShow)
    {
        construct();
    }

    TextEditView::~TextEditView() = default;

    void TextEditView::construct()
    {
        _edit = Style::Widget::lineEdit();
        _edit->setMaxLength(512);
        constructView(_edit);
        Style::Constraint::height(this, Style::Ctrl::BaseHeight);

        _model.addInput(
            [=](const String& text)
            {
                RT_GUARD_CHECK_VOID(_edit)
                _edit->setText(Qsu::to(text));
            });

        connect(_edit,
                &QLineEdit::textEdited,
                this,
                &TextEditView::textChanged);
    }

    void TextEditView::setText(const String& text)
    {
        _model.setValue(text);
    }

    String TextEditView::text() const
    {
        return _model.value();
    }

    void TextEditView::addOutput(const StringModel::Observer& type)
    {
        _model.addOutput(type);
    }

    void TextEditView::textChanged(const QString& val)
    {
        _model.setValue(Qsu::from(val), ViewModel::OUTPUT);
    }

}  // namespace Rt2::View
