#pragma once
#include "View/PushButton.h"

class QWidget;

namespace Rt2::Samples
{
    class SamplePushButton
    {
    private:

        QLabel *_a{nullptr};
        QLabel *_b{nullptr};
        QWidget* load();

    public:
        int go();
    };

}  // namespace Rt2::Samples
