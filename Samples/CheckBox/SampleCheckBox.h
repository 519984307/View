#pragma once
#include "View/CheckBoxView.h"

class QWidget;

namespace Rt2::Samples
{
    class SampleCheckBox
    {
    private:
        View::CheckBoxView* _check1{nullptr};
        View::CheckBoxView* _check2{nullptr};
        QLabel*             _text1{nullptr};
        QLabel*             _text2{nullptr};

        QWidget* load();

    public:
        int go();
    };

}  // namespace Rt2::Samples
