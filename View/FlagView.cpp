#include "FlagView.h"
#include <QVBoxLayout>
#include <QWidget>
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

    FlagView::~FlagView()
    {
    }

    void FlagView::setMax(const int max)
    {
        _max = max;
        if (_content->count() != max)
            onCountChange();
    }

    void FlagView::construct()
    {
        _content = Qu::horizontal();
        _content->setAlignment(Qt::AlignTop|Qt::AlignLeft);
        constructView(_content, 0);
        setAutoFillBackground(true);
        setUpdatesEnabled(true);
        setBorder(0);
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
            const auto box = new FlagViewItem(false, this);

            _content->addWidget(box);
        }

        _content->invalidate();

        refresh();
    }
}  // namespace Rt2::View
