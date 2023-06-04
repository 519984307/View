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
#include "View/ItemListWidget.h"
#include <QBoxLayout>
#include "Qu.h"
#include "StyleSheetWriter.h"

namespace Rt2::View
{
    ItemListWidget::ItemListWidget(
        const QWidgetList& items,
        const int&         size,
        const QMargins&    margins,
        const QColor&      color,
        const QColor&      background,
        QWidget*           parent) :
        QWidget(parent)
    {
        const auto lo = Qu::horizontal();
        setAutoFillBackground(true);
        lo->setContentsMargins(margins);


        StyleSheetWriter w;
        w.backgroundColor(background);
        w.color(color);
        w.noBorder();
        setStyleSheet(w.toString());

        lo->addStretch();

        for (const auto item : items)
        {
            item->setFixedHeight(size);
            item->setAttribute(Qt::WA_TranslucentBackground);

            lo->addWidget(item, 0, Qt::AlignCenter);
        }
        lo->addSpacing(size);
        setLayout(lo);
    }

}  // namespace Rt2::View
