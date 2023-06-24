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
#include "View/TitleListWidget.h"
#include <QBoxLayout>
#include <QLabel>
#include "Qu.h"
#include "View/StyleSheetWriter.h"

namespace Rt2::View
{
    TitleListWidget::TitleListWidget(
        const String&        titleText,
        const QWidgetList&   titleItems,
        const int&           textSize,
        const int&           maxHeight,
        const QMargins&      margin,
        const QColor&        foreground,
        const QColor&        background,
        const Qt::Alignment& titleAlignment,
        QWidget*             parent) :
        QWidget(parent)
    {
        const auto lo = Style::Layout::h0();
        lo->setContentsMargins(margin);

        StyleSheetWriter w;
        w.backgroundColor(background);
        w.color(foreground);
        w.height(maxHeight);
        setStyleSheet(w.toString());

        lo->addWidget(Style::Widget::label(titleText, textSize, foreground), 1, titleAlignment);
        lo->addStretch();

        for (const auto item : titleItems)
        {
            lo->addWidget(item, 0, Qt::AlignCenter);
            item->setAttribute(Qt::WA_TranslucentBackground);
        }
        setLayout(lo);
    }

    TitleListView::TitleListView(QWidget* parent) :
        LayoutView(parent)
    {
        construct();
    }

    void TitleListView::construct()
    {
        using namespace Style;

        const auto layout = Layout::h1();
        constructView(layout);

        _title = Widget::label(Style::FontSize::Large);
        layout->addWidget(_title, 1);
        layout->addStretch();
    }

    void TitleListView::setTitle(const String& title) const
    {
        RT_GUARD_CHECK_VOID(_title)
        _title->setText(Qsu::to(title));
    }

    void TitleListView::setWidgetList(const QWidgetList& widgets) const
    {
        RT_GUARD_CHECK_VOID(_content)
        for (const auto w : widgets)
            _content->addWidget(w);
    }

}  // namespace Rt2::View
