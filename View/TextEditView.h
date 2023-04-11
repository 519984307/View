#pragma once
#include <QWidget>
#include "View/Definitions.h"

class QLineEdit;

namespace Rt2::View
{
    class TextEditView final : public QWidget
    {
        Q_OBJECT
    public:
        using ObserverType = StringModel::Observer;

    private:
        QLineEdit*             _edit{nullptr};
        ViewModel::StringModel _viewModel;

    public:
        explicit TextEditView(QWidget* parent = nullptr);

        void setText(const String& text);

        String text() const;

        void addOutput(const ObserverType& type);

    private:
        void construct();

        void bind();
        void textChanged(const QString&);
    };

}  // namespace Rt2::Widgets
