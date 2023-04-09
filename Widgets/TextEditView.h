#pragma once
#include <QWidget>
#include "ViewModel/Property.h"
#include "ViewModel/ViewModel.h"

class QLineEdit;

namespace Rt2::Widgets
{
    class TextEditView final : public QWidget
    {
        Q_OBJECT
    public:
        using ObserverType = ViewModel::StringProperty::ObserverType;

    private:
        QLineEdit*                _edit{nullptr};
        ViewModel::StringProperty _viewModel;


    public:
        explicit TextEditView(QWidget* parent = nullptr);

        void setText(const String& text);

        String text() const;

        void addOutput(const ObserverType& type);

    public:
        void construct();

        void bind();

        void textChanged(const QString&);
    };

}  // namespace Rt2::Widgets
