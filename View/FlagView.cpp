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

    void FlagView::addFlag(const bool state, const String& text)
    {
        const auto box = new FlagViewItem(state,
                                          _content->count(),
                                          Qsu::to(text),
                                          this);

        const auto stateChanged = [this](const bool st, const int index)
        {
            int v = _bits.value();
            if (st)
                v |= (1 << index);
            else
                v &= ~(1 << index);
            _bits.setValue(v, ViewModel::OUTPUT);
        };

        connect(box, &FlagViewItem::stateChanged, this, stateChanged);
        _content->addWidget(box);
    }

    void FlagView::setBits(int bits) const
    {
        for (int i = 0; i < _content->count(); ++i)
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

}  // namespace Rt2::View
