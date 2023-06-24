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
#include <cfloat>
#include <cmath>
#include "View/SliderView.h"
#include <QMouseEvent>
#include <QPainter>
#include "Qu.h"

namespace Rt2::View
{
    SliderView::SliderView(QWidget* parent) :
        CustomView(parent),
        _rangeRate{0, 1, 1}
    {
        construct();
    }

    SliderView::~SliderView() = default;
    
    void SliderView::construct()
    {
        constructView();
        setPadding(0);
        setMargin(0);
        setFlags(CvFullView);
        setMinimumHeight(Style::Icon::BoundingHeight);
        setBackgroundColor(Style::Window::Background);
    }

    void SliderView::setRange(const double& min, const double& max)
    {
        if (min > max)
        {
            _rangeRate[0] = max;
            _rangeRate[1] = min;
        }
        else if (min < max)
        {
            _rangeRate[0] = min;
            _rangeRate[1] = max;
        }
        else
        {
            _rangeRate[0] = 0;
            _rangeRate[1] = 1;
        }
        refresh();
    }

    void SliderView::setRate(const double& val)
    {
        if (const double d = fabs(val);
            d > DBL_EPSILON)
            _rangeRate[2] = d;
    }

    void SliderView::setValue(const double& val)
    {
        _value.setValue(val);
    }

    void SliderView::addInput(const FloatModel::Observer& ob)
    {
        _value.addInput(ob);
    }

    void SliderView::addOutput(const FloatModel::Observer& ob)
    {
        _value.addOutput(ob);
    }

    void SliderView::mousePressEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)

        if (event->button() == Qt::LeftButton)
        {
            if (const QPoint pt = Qmc::point(event->position());
                rect().contains(pt))
            {
                _state |= PRESSED;
                refresh();
            }
            else
            {
                _state &= ~PRESSED;
                refresh();
            }
        }
    }

    void SliderView::mouseReleaseEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)

        if (event->button() == Qt::LeftButton)
        {
            if (_state & PRESSED)
                refresh();
            _state &= ~PRESSED;
        }
    }

    void SliderView::mouseMoveEvent(QMouseEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)

        const double w = double(width());
        const double u = Clamp(double(event->position().x()), 0.0, w) / w;

        double v = (_rangeRate[1] - _rangeRate[0]) * u + _rangeRate[0];
        v -= fmod(v, _rangeRate[2]);
        _value.setValue(v, ViewModel::OUTPUT);
        refresh();
    }

    void SliderView::enterEvent(QEnterEvent* event)
    {
        _state |= ENTER;
        refresh();
    }

    void SliderView::leaveEvent(QEvent* event)
    {
        _state &= ~ENTER;
        refresh();
    }

    void SliderView::render(QPainter& paint, const QRectF& rect)
    {
        paint.fillRect(rect, backgroundColor());

        if (_state & ENTER)
        {
            paint.setPen(QPen(Style::Window::Background));
            paint.drawRect(rect.adjusted(1, 1, -1, -1));
        }

        const double value = _value.value() / (_rangeRate[1] - _rangeRate[0]);
        const double v     = rect.width() * value;

        paint.fillRect(QRectF{2, 2, v, rect.height() - 2}, Style::Window::Accent);
    }
}  // namespace Rt2::View