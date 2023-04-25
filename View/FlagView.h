#pragma once
#include <QWidget>
#include "LayoutView.h"

class QBoxLayout;
class QLabel;

namespace Rt2::View
{
    class FlagView final : public LayoutView
    {
        Q_OBJECT
    private:
        int         _bits{0};
        int         _max{5};

    public:
        explicit FlagView(QWidget* parent = nullptr);

        ~FlagView() override;

        void setMax(int max);

    private:
        void construct();

        void onCountChange();
    };

}  // namespace Rt2::View
