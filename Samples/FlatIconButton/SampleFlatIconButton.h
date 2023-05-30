#pragma once
#include "View/FlatIconButtonView.h"

class QHBoxLayout;
class QWidget;

namespace Rt2::Samples
{
    class SampleFlatIconButton
    {
    private:
        static QWidget* load();

    public:
        static int go();
    };

}  // namespace Rt2::Samples
