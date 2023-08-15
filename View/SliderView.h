/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
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

    enum SliderViewOptions
    {
        SliderViewScroll   = 0x01,
        SliderViewConstant = 0x02
    };

    class SliderView final : public CustomView
    {
        Q_OBJECT
    private:
        QLabel*           _button{nullptr};
        SliderViewStates* _states{nullptr};
        DoubleModel       _value{0};
        double            _rangeRate[3];
        int               _state{0};
        QRectF            _textPos;
        QString           _text;
        int               _opts{SliderViewConstant | SliderViewScroll};

    public:
        explicit SliderView(QWidget* parent = nullptr);

        ~SliderView() override;

        void setRange(const double& min, const double& max);

        void setRate(const double& val);

        void setValue(const double& val, ViewModel::Direction dir = ViewModel::OUTPUT);

        void addInput(const FloatModel::Observer& ob);

        void addOutput(const FloatModel::Observer& ob);

    private:
        void construct();

        void updateText();

    protected:
        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void mouseMoveEvent(QMouseEvent* event) override;

        void wheelEvent(QWheelEvent* event) override;

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;

        void render(QPainter& paint, const QRectF& rect) override;
    };

}  // namespace Rt2::View
