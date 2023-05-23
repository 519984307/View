#pragma once
#include <QWidget>
#include "Definitions.h"
#include "View/LayoutView.h"
#include "ViewModel/Property.h"

class QBoxLayout;
class QLabel;

namespace Rt2::View
{
    class FlagView final : public LayoutView
    {
        Q_OBJECT
    private:
        IntModel _bits{0};

    public:
        explicit FlagView(QWidget* parent = nullptr);

        ~FlagView() override;

        void addFlag(bool state, const String& text);

        void setBits(int bits) const;

        void addOutput(const IntModel::Observer& ot);

        void addInput(const IntModel::Observer& ot);

    private:
        void construct();
    };

}  // namespace Rt2::View
