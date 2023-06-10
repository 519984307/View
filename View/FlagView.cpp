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
#include "View/FlagView.h"
#include <QVBoxLayout>
#include <QWidget>
#include "View/Colors.h"
#include "View/FlagViewItem.h"
#include "View/LayoutView.h"
#include "View/Qu.h"

class QLabel;

namespace Rt2::View
{

    FlagView::FlagView(QWidget* parent) :
        LayoutView(parent)
    {
        construct();
    }

    FlagView::~FlagView() = default;

    void FlagView::construct()
    {
        _content = Qu::horizontal();
        _content->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        constructView(_content, 0);

        setBorder(1);
        setPadding(0);
        setBorderColor(Colors::up(Colors::CtrlBackgroundLight));
        _background = Colors::CtrlBackground;
        _accent     = Colors::Accent;
    }

    void FlagView::updateFlags() const
    {
        RT_GUARD_CHECK_VOID(_content)

        for (int i = 0; i < _content->count(); ++i)
        {
            const QLayoutItem* item = _content->itemAt(i);

            if (QWidget* wdg = item->widget();
                wdg && wdg->inherits("Rt2::View::FlagViewItem"))
            {
                FlagViewItem* fv = (FlagViewItem*)wdg;
                fv->setBackgroundColor(_background);
                fv->setAccentColor(_accent);
            }
        }
    }

    void FlagView::addFlag(const bool state, const String& text)
    {
        RT_GUARD_CHECK_VOID(_content)

        const auto box = new FlagViewItem(state,
                                          _content->count(),
                                          Qsu::to(text),
                                          this);

        box->setBackgroundColor(_background);
        box->setAccentColor(_accent);

        const auto stateChanged = [this](const bool st, const int index)
        {
            int v = _bits.value();
            if (st)
                v |= 1 << index;
            else
                v &= ~(1 << index);
            _bits.setValue(v, ViewModel::OUTPUT);
        };

        connect(box, &FlagViewItem::stateChanged, this, stateChanged);
        _content->addWidget(box);
    }

    void FlagView::setBits(const int bits) const
    {
        RT_GUARD_CHECK_VOID(_content)

        for (int i = 0; i < _content->count(); ++i)
        {
            const QLayoutItem* item = _content->itemAt(i);

            if (QWidget* wdg = item->widget();
                wdg && wdg->inherits("Rt2::View::FlagViewItem"))
            {
                FlagViewItem* fv = (FlagViewItem*)wdg;
                fv->setState((bits & (1 << i)) != 0);
            }
        }
    }

    void FlagView::addOutput(const IntModel::Observer& ot)
    {
        _bits.addOutput(ot);
    }

    void FlagView::addInput(const IntModel::Observer& ot)
    {
        _bits.addInput(ot);
    }

    void FlagView::setAccentColor(const QColor& col)
    {
        _accent = col;
        updateFlags();
    }

    void FlagView::setBackgroundColor(const QColor& col)
    {
        _background = col;
        updateFlags();
    }
}  // namespace Rt2::View
