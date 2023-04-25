#pragma once
#include <QWidget>
#include "View.h"

class QLabel;
class QPushButton;

namespace Rt2::View
{
    class CheckBoxStates;
    
    class CheckBoxView final : public View
    {
        Q_OBJECT
    private:
        QLabel*         _button{nullptr};
        CheckBoxStates* _states{nullptr};

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
        void checkChanged(bool value);

    public:
        explicit CheckBoxView(QWidget* parent = nullptr);
        ~CheckBoxView() override;

    private:
        void construct();

    protected:
        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;
    };

}  // namespace Rt2::View
