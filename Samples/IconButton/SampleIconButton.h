#pragma once
#include "View/IconButtonView.h"

class QHBoxLayout;
class QWidget;

namespace Rt2::Samples
{
    class SampleIconButton
    {
    private:
        static QWidget* load();

    public:
        static int go();
    };

}  // namespace Rt2::Samples
