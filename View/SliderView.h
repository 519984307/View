#pragma once
#include <QWidget>
#include "View/CustomView.h"
#include "View/Definitions.h"
#include "ViewModel/Property.h"

class QLabel;
class QPushButton;

namespace Rt2::View
{
    class SliderViewStates;

    class SliderView final : public CustomView
    {
        Q_OBJECT
    private:
        QLabel*           _button{nullptr};
        SliderViewStates* _states{nullptr};
        DoubleModel       _value{0};
        double            _rangeRate[3];
        int               _state{0};

    public:
        explicit SliderView(QWidget* parent = nullptr);

        ~SliderView() override;

        void setRange(const double& min, const double& max);

        void setRate(const double& val);

        void setValue(const double& val);

        void addInput(const FloatModel::Observer& ob);

        void addOutput(const FloatModel::Observer& ob);

    private:
        void construct();

    protected:
        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void mouseMoveEvent(QMouseEvent* event) override;

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;

        void render(QPainter& paint, const QRectF& rect) override;
    };

}  // namespace Rt2::View
