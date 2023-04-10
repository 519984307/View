#include "TextEditView.h"
#include <QLineEdit>
#include <QWidget>
#include "Colors.h"
#include "Qu.h"
#include "ViewModel/ViewModel.h"

class QLineEdit;

namespace Rt2::Widgets
{
    TextEditView::TextEditView(QWidget* parent) :
        QWidget(parent)
    {
        construct();
    }

    void TextEditView::setText(const String& text)
    {
        _viewModel.setValue(text);
    }

    String TextEditView::text() const
    {
        return _viewModel.value();
    }

    void TextEditView::addOutput(const ObserverType& type)
    {
        _viewModel.addOutput(type);
    }

    void TextEditView::construct()
    {
        Qu::setBackground(this, Colors::GreyM2);
        setContentsMargins(1,1,1,1);

        const auto layout = Qu::horizontal();

        _edit = new QLineEdit(this);
        _edit->setFrame(false);

        Qu::setBackground(_edit, Colors::GreyM1);
        Qu::setForeground(_edit, Colors::Text00);

        layout->addWidget(_edit, 1);
        setLayout(layout);

        bind();
    }

    void TextEditView::bind()
    {
        _viewModel.addInput(
            [=](const String& text)
            {
                if (_edit)
                    _edit->setText(Qsu::to(text));
            });

        connect(_edit,
                &QLineEdit::textEdited,
                this,
                &TextEditView::textChanged);
    }

    void TextEditView::textChanged(const QString& val)
    {
        _viewModel.setValue(Qsu::from(val), ViewModel::OUTPUT);
    }

}  // namespace Rt2::Widgets
