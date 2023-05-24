#pragma once
#include <QWidget>
#include "View/View.h"

class QLabel;
class QPushButton;

namespace Rt2::View
{
    class CheckBoxStates;

    class CheckBoxView final : public View
    {
        Q_OBJECT
    private:
        QLabel*         _icon{nullptr};
        CheckBoxStates* _states{nullptr};
        BoolModel       _check{false};
        int             _state{NONE};

    public:
        explicit CheckBoxView(QWidget* parent = nullptr);

        ~CheckBoxView() override;

        void setChecked(bool v);

        bool isChecked() const;

        void addInput(const BoolModel::Observer& ob);

        void addOutput(const BoolModel::Observer& ob);

    private:
        void construct();

    protected:
        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;
    };

    inline bool CheckBoxView::isChecked() const
    {
        return _state & ON;
    }

}  // namespace Rt2::View
