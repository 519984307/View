#include "FlagView.h"
#include <QVBoxLayout>
#include <QWidget>
#include "Colors.h"
#include "FlagViewItem.h"
#include "LayoutView.h"
#include "Metrics.h"
#include "Qu.h"

class QLabel;

namespace Rt2::View
{

    FlagView::FlagView(QWidget* parent) :
        LayoutView(parent)
    {
        construct();
    }

    FlagView::~FlagView() = default;

    void FlagView::setMax(const int max)
    {
        _max = max;
        if (_content->count() != max)
            onCountChange();
    }

    void FlagView::setBits(int bits) const
    {
        for (int i = 0; i < _max; ++i)
        {
            QLayoutItem* item = _content->itemAt(i);
            QWidget*     wdg  = item->widget();
            if (wdg && wdg->inherits("Rt2::View::FlagViewItem"))
            {
                FlagViewItem* fv = (FlagViewItem*)wdg;
                fv->setState((bits & (1 << i)) != 0);
            }
        }
    }

    void FlagView::addOutput(const ObserverType& ot)
    {
        _bits.addOutput(ot);
    }

    void FlagView::construct()
    {
        _content = Qu::horizontal();
        _content->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        constructView(_content, 0);
        setAutoFillBackground(true);
        setUpdatesEnabled(true);
        setBorder(1);
        setBorderColor(Colors::CtrlBackgroundLight.lighter(Colors::Lgt090));
        setPadding(0);
    }

    void FlagView::onCountChange()
    {
        while (const QLayoutItem* item = _content->takeAt(0))
        {
            delete item->widget();
            delete item;
        }

        for (int i = 0; i < _max; ++i)
        {
            const auto box = new FlagViewItem(false, i, this);

            const auto stateChanged = [this](const bool state, const int index)
            {
                int v = _bits.value();
                if (state)
                    v |= (1 << index);
                else
                    v &= ~(1 << index);
                _bits.setValue(v, ViewModel::OUTPUT);
            };

            connect(box, &FlagViewItem::stateChanged, this, stateChanged);

            _content->addWidget(box);
        }
        _content->invalidate();
        refresh();
    }

}  // namespace Rt2::View
