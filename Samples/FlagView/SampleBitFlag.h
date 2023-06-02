#pragma once
#include "View/CheckBoxView.h"

class QWidget;

namespace Rt2::Samples
{
    class SampleBitFlag
    {
    private:
        View::FlagView* _flag{nullptr};
        QLabel*         _bin{nullptr};
        QLabel*         _hex{nullptr};
        QLabel*         _oct{nullptr};

        QWidget* load();

    public:
        int go();
    };

}  // namespace Rt2::Samples
