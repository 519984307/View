#pragma once
#include <QWidget>
#include "View/Definitions.h"
#include "View/View.h"

class QLineEdit;

namespace Rt2::View
{
    class TextEditView final : public View
    {
        Q_OBJECT
    private:
        QLineEdit*  _edit{nullptr};
        StringModel _textModel;

    public:
        explicit TextEditView(QWidget* parent = nullptr);

        String text() const;

        void setText(const String& text);

        void addOutput(const StringModel::Observer& type);

    private:
        void construct();

        void bind();

        void textChanged(const QString&);

        void paintEvent(QPaintEvent* event) override;
    };

}  // namespace Rt2::View
