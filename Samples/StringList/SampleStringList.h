#pragma once
#include <QLabel>
#include "View/TextEditView.h"

class QHBoxLayout;
class QWidget;

namespace Rt2::Samples
{
    class SampleStringList
    {
    private:
        View::StringListView* _list{nullptr};
        int                   _cur{0};

        QWidget* load();

    public:
        int go();
    };

}  // namespace Rt2::Samples
