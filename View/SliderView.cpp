#include <cfloat>
#include <cmath>
#include "View/SliderView.h"
#include <QMouseEvent>
#include <QPainter>
#include "Colors.h"
#include "Metrics.h"
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

    void SliderView::construct()
    {
        constructView();
        setPadding(0);
        setMargin(0);
        setFlags(CvFullView);
        setMinimumHeight(Metrics::iconHeight);
        setBackgroundColor(Colors::CtrlBackground.darker(Colors::Drk010));
    }

    void SliderView::mousePressEvent(QMouseEvent* event)
    {
        if (!event) return;

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
        if (!event) return;

        if (event->button() == Qt::LeftButton)
        {
            if (_state & PRESSED)
                refresh();
            _state &= ~PRESSED;
        }
    }

    void SliderView::mouseMoveEvent(QMouseEvent* event)
    {
        if (!event) return;

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
            paint.setPen(QPen(backgroundColor().lighter(Colors::Lgt080)));
            paint.drawRect(rect.adjusted(1, 1, -1, -1));
        }

        const double value = _value.value() / (_rangeRate[1] - _rangeRate[0]);
        const double v     = rect.width() * value;

        paint.fillRect(QRectF{2, 2, v, rect.height() - 2}, Colors::Accent);
    }
}  // namespace Rt2::View