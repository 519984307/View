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

    public:
        explicit FlagView(QWidget* parent = nullptr);

        ~FlagView() override;

        void addFlag(bool state, const String& text);

        void setBits(int bits) const;

        void addOutput(const ObserverType& ot);
        void addInput(const ObserverType& ot);

    private:
        void construct();
    };

}  // namespace Rt2::View
