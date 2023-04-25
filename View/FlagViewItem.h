#pragma once
#include <QWidget>
#include "CustomView.h"

namespace Rt2::View
{
    class FlagViewItemStates;

    class FlagViewItem final : public CustomView
    {
        Q_OBJECT

    private:
        FlagViewItemStates* _states{nullptr};

        enum States
        {
            NONE     = 0x00,
            PRESSED  = 0x01,
            RELEASED = 0x02,
            ENTER    = 0x04,
            ON       = 0x08,
        };
        int _state{NONE};
    signals:
        void checked();

    public:
        explicit FlagViewItem(bool state, QWidget* parent = nullptr);

    private:
        void construct();

        bool  isOn() const {return (_state & ON) != 0;}

    protected:
        void render(QPainter& paint, const QRectF& rect) override;

        void mousePressEvent(QMouseEvent* event) override;

         void mouseReleaseEvent(QMouseEvent* event) override;

         void enterEvent(QEnterEvent* event) override;

         void leaveEvent(QEvent* event) override;
    };

}  // namespace Rt2::View
