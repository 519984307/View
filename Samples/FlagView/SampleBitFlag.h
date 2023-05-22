#pragma once
#include "View/CheckBoxView.h"

class QWidget;

namespace Rt2::Samples
{
    class SampleBitFlag
    {
    private:
        View::FlagView* _flag{nullptr};
        QLabel*         _bits{nullptr};

        QWidget* load();

    public:
        int go();
    };

}  // namespace Rt2::Samples
