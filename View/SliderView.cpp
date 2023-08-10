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
#include "View/SliderView.h"
#include <QMouseEvent>
#include <QPainter>
#include <cfloat>
#include <cmath>
#include "Qu.h"
#include "Utils/Char.h"

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
        Style::Constraint::minimum(this, Style::Slider::MinSize);
        Style::Constraint::height(this, Style::Slider::MinSize.height());

        _background = Style::Normal::Background;
        _border     = Style::Normal::Border;
        _highlight  = Style::Normal::Highlight;
    }

    void SliderView::updateText()
    {
        const String text = Char::toString((int)_value.value());

        _textPos = Qu::measure(text, Style::FontSize::Normal);
        _text    = Qsu::to(text);
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
        updateText();
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
        updateText();
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
        if (_state & ENTER)
            paint.fillRect(rect, borderColor());
        else
            paint.fillRect(rect, backgroundColor());

        const double value = (abs(_rangeRate[0]) + _value.value()) / (_rangeRate[1] - _rangeRate[0]);
        const double v     = rect.width() * value;

        const auto fr = QRectF{rect.left(), rect.top(), v, rect.height()};

        paint.fillRect(fr, highlightColor());

        const QPointF loc = rect.center() - _textPos.center();

        paint.drawText(loc, _text);
    }
}  // namespace Rt2::View