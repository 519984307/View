#pragma once
#include <QWidget>
#include "View/View.h"
#include "View/IconFontMapping.h"

class QLabel;
class QPushButton;

namespace Rt2::View
{
    class IconButtonStates;

    class IconButtonView final : public View
    {
        Q_OBJECT
    private:
        QLabel*           _button{nullptr};
        IconButtonStates* _states{nullptr};
        int               _state{NONE};

    signals:
        void clicked();

    public:
        explicit IconButtonView(IconMap icon, QWidget* parent = nullptr);
        ~IconButtonView() override;

    private:
        void construct(IconMap icon);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;
    };

}  // namespace Rt2::View
