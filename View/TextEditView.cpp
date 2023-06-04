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
#include "StyleSheetWriter.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"
#include "ViewModel/ViewModel.h"

namespace Rt2::View
{
    TextEditView::TextEditView(QWidget* parent) :
        View(parent)
    {
        construct();
    }

    TextEditView::~TextEditView() = default;

    void TextEditView::construct()
    {
        _edit = new QLineEdit(this);
        constructView(_edit);

        setMaximumHeight(Metrics::ctrlMin.height());
        setBorderColor(Colors::BorderDark);
        setBackgroundColor(Colors::Transparent);
        setColor(QPalette::Highlight, Colors::Accent);

        _edit->setFrame(false);

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

    void TextEditView::paintEvent(QPaintEvent* event)
    {
        QPainter paint(this);
        paint.setRenderHint(QPainter::Antialiasing);

        QRectF ctx = {0, 0, (qreal)width(), (qreal)height()};

        ctx = ctx.marginsRemoved(contentsMargins());

        const QColor col = palette().color(QPalette::Window);

        QLinearGradient gradient(ctx.topLeft(), ctx.bottomLeft());
        gradient.setColorAt(0.0, col.darker(Colors::Drk050));
        gradient.setColorAt(0.2, col.darker(Colors::Drk010));
        gradient.setColorAt(1.0, col);

        paint.fillRect(ctx, col.darker(150));
        paint.setPen(QPen(col.lighter(), Metrics::borderSizeTiny));
        paint.drawRect(ctx.adjusted(-1, -1, 1, 1));
    }
}  // namespace Rt2::View
