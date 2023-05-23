#pragma once
#include <QLabel>
#include "View/TextEditView.h"

class QHBoxLayout;
class QWidget;

namespace Rt2::Samples
{
    class SampleSlider
    {
    private:
        QLabel*  _label{nullptr};
        QWidget* load();

    public:
        int go();
    };

}  // namespace Rt2::Samples
