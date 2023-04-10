#pragma once
#include <QWidget>

class QPushButton;

namespace Rt2::Widgets
{
    class IconButtonView final : public QWidget
    {
        Q_OBJECT
    private:
        QPushButton* _button{nullptr};

    public:
        explicit IconButtonView(QWidget* parent = nullptr);

    public:
        void construct();
    };

}  // namespace Rt2::Widgets
