#pragma once
#include <QWidget>
#include "View/View.h"

class QLabel;
class QPushButton;

namespace Rt2::View
{
    class PushButtonStates;

    class PushButtonView final : public View
    {
        Q_OBJECT
    private:
        QLabel*           _text{nullptr};
        PushButtonStates* _states{nullptr};
        BoolModel         _observers{};

    public:
        explicit PushButtonView(QWidget* parent = nullptr);
        explicit PushButtonView(const String& text, QWidget* parent = nullptr);

        ~PushButtonView() override;

        void setLabel(const String& label) const;

        String label() const;

        void addOutput(const BoolModel::Observer& ob);

    private:
        void construct();

        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;
    };

}  // namespace Rt2::View
