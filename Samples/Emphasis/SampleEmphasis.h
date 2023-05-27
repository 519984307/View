#pragma once
#include <QLabel>
#include "View/TextEditView.h"

class QHBoxLayout;
class QWidget;

namespace Rt2::Samples
{
    class SampleEmphasis
    {
    private:
        QLabel*  _label0{nullptr};
        QLabel*  _label1{nullptr};
        QLabel*  _label2{nullptr};
        QLabel*  _label3{nullptr};
        QLabel*  _label4{nullptr};
        QLabel*  _label5{nullptr};

        QWidget* load();

    public:
        int go();
    };

}  // namespace Rt2::Samples
