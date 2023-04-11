#include "View/TextEditView.h"
#include <QLineEdit>
#include <QBoxLayout>
#include <QWidget>
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"
#include "ViewModel/ViewModel.h"

class QLineEdit;

namespace Rt2::View
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
        Qu::setBackground(this, Colors::Border);
        setContentsMargins(Metrics::BorderThin);

        const auto layout = Qu::horizontal();

        _edit     = new QLineEdit(this);
        QFont fnt = _edit->font();
        // fnt.setPointSize(Metrics::iconFontSize-2);
        _edit->setFont(fnt);

        _edit->setFrame(false);

        Qu::setBackground(_edit, Colors::CtrlBackground);
        Qu::setForeground(_edit, Colors::Foreground);

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

}  // namespace Rt2::View
