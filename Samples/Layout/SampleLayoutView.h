#pragma once
#include "View/LayoutView.h"

class QHBoxLayout;
class QWidget;

namespace Rt2::Samples
{
    class SampleLayoutView
    {
    private:
        static QWidget* load();

    public:
        static int go();
    };

}  // namespace Rt2::Samples
