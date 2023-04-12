#pragma once
#include <QWidget>
#include "View.h"

class QLabel;
class QPushButton;

namespace Rt2::View
{
    enum IconMap
    {
        IconAdd = ' ',
        IconEdit,
        IconDelete,
        IconClear   = '$',
        IconExit    = '&',
        IconRefresh = '0',
        IconBack    = 'G',
        IconUp,
        IconForward,
        IconDown,

    };

    class IconButtonView final : public View
    {
        Q_OBJECT
    private:
        QLabel* _button{nullptr};

        enum States
        {
            NONE     = 0x00,
            PRESSED  = 0x01,
            RELEASED = 0x02,
            ENTER    = 0x04,
        };
        int _state{NONE};

    signals:
        void clicked();

    public:
        explicit IconButtonView(IconMap icon, QWidget* parent = nullptr);

    private:
        void construct(IconMap icon);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;

        void paintEvent(QPaintEvent* event) override;
    };

}  // namespace Rt2::View
