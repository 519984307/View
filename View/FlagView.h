#pragma once
#include <QWidget>
#include "LayoutView.h"
#include "ViewModel/Property.h"

class QBoxLayout;
class QLabel;

namespace Rt2::View
{
    class FlagView final : public LayoutView
    {
        Q_OBJECT
    public:
        using ObserverType = ViewModel::IntModel::Observer;

    private:
        ViewModel::IntModel _bits{0};
        int                 _max{5};

    public:
        explicit FlagView(QWidget* parent = nullptr);

        ~FlagView() override;

        void setMax(int max);

        void setBits(int bits) const;

        void addOutput(const ObserverType& ot);

    private:
        void construct();

        void onCountChange();
    };

}  // namespace Rt2::View
