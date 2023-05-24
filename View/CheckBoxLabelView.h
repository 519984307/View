#pragma once
#include <QWidget>
#include "CheckBoxView.h"
#include "View/LayoutView.h"

namespace Rt2::View
{
    class CheckBoxLabelView final : public LayoutView
    {
        Q_OBJECT
    private:
        QLabel*       _label{nullptr};
        CheckBoxView* _check{nullptr};

    public:
        explicit CheckBoxLabelView(const QString& text, QWidget* parent = nullptr);

        ~CheckBoxLabelView() override;

        void setChecked(bool v) const;

        bool isChecked() const;

        void setText(const QString& text) const;

        void setTextAlignment(Qt::Alignment al) const;

        void addOutput(const BoolModel::Observer &v) const;

    private:
        void construct();

        void extract(std::pair<QLabel*, QWidget*> &dest) const;
    };

}  // namespace Rt2::View
