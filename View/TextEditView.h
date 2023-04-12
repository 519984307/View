#pragma once
#include <QWidget>

#include "View.h"
#include "View/Definitions.h"

class QLineEdit;

namespace Rt2::View
{
    class TextEditView final : public View
    {
        Q_OBJECT
    public:
        using ObserverType = StringModel::Observer;

    private:
        QLineEdit*             _edit{nullptr};
        ViewModel::StringModel _viewModel;

    public:
        explicit TextEditView(QWidget* parent = nullptr);

        String text() const;

        void setText(const String& text);

        void addOutput(const ObserverType& type);

    private:
        void construct();

        void bind();

        void textChanged(const QString&);

        void paintEvent(QPaintEvent* event) override;
    };

}  // namespace Rt2::View
