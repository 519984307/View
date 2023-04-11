#pragma once
#include <QWidget>

class QPushButton;

namespace Rt2::Widgets
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

    class IconButtonView final : public QWidget
    {
        Q_OBJECT
    private:
        QPushButton* _button{nullptr};

    signals:
        void clicked();

    public:
        explicit IconButtonView(IconMap icon, QWidget* parent = nullptr);

    public:
        void construct(IconMap icon);
    };

}  // namespace Rt2::Widgets
