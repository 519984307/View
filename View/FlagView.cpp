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
#include "View/FlagViewItem.h"
#include "View/LayoutView.h"
#include "View/Qu.h"

namespace Rt2::View
{
    namespace Detail
    {
        FlagViewItem* flagItem(const QLayoutItem* obj)
        {
            RT_GUARD_CHECK_RET(obj, nullptr)
            if (QWidget* wi = obj->widget(); wi && wi->inherits("Rt2::View::FlagViewItem"))
                return (FlagViewItem*)wi;
            return nullptr;
        }
    }  // namespace Detail

    FlagView::FlagView(QWidget* parent) :
        LayoutView(parent)
    {
        construct();
    }

    FlagView::~FlagView() = default;

    void FlagView::construct()
    {
        constructView(Style::Layout::h0());
    }

    void FlagView::addFlag(const bool state, const String& text)
    {
        RT_GUARD_CHECK_VOID(_content)

        const auto box = new FlagViewItem(state, _content->count(), Qsu::to(text), this);

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

    void FlagView::setBits(const int bits)
    {
        RT_GUARD_CHECK_VOID(_content)
        _bits.setValue(bits, ViewModel::NONE);

        for (int i = 0; i < _content->count(); ++i)
        {
            if (const auto item = Detail::flagItem(_content->itemAt(i)))
                item->setState((bits & 1 << i) != 0);
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
}  // namespace Rt2::View
