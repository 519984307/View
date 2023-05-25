#include "View/CheckBoxLabelView.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include "View/Colors.h"
#include "View/Qu.h"
#include "View/CheckBoxView.h"
#include "View/LayoutView.h"

namespace Rt2::View
{
    CheckBoxLabelView::CheckBoxLabelView(const QString& text, QWidget* parent) :
        LayoutView(parent)
    {
        construct();
        if (_label)
            _label->setText(text);
    }

    CheckBoxLabelView::~CheckBoxLabelView() = default;

    void CheckBoxLabelView::construct()
    {
        const auto lo = Qu::horizontal();
        constructView(lo, 0);
        setPadding(0);
        setBorder(0);

        lo->setAlignment(Qt::AlignLeft);

        _check = new CheckBoxView();
        _label = new QLabel();

        lo->addWidget(_check);
        lo->addWidget(_label);
    }

    void CheckBoxLabelView::extract(std::pair<QLabel*, QWidget*>& dest) const
    {
        QBoxLayout* lo = boxLayout();
        if (!lo)
            return;

        const QLayoutItem* a = lo->takeAt(0);
        const QLayoutItem* b = lo->takeAt(0);

        if (!a || !b)
            return;

        QWidget* wa = a->widget();
        delete a;
        QWidget* wb = b->widget();
        delete b;

        if (wa && Qu::isLabel(wa))
        {
            dest.first  = (QLabel*)wa;
            dest.second = wb;
        }
        else
        {
            dest.first  = (QLabel*)wb;
            dest.second = wa;
        }
    }

    void CheckBoxLabelView::setChecked(const bool v) const
    {
        if (_check)
            _check->setChecked(v);
    }

    bool CheckBoxLabelView::isChecked() const
    {
        if (_check) return _check->isChecked();
        return false;
    }

    void CheckBoxLabelView::setText(const QString& text) const
    {
        if (_label)
            _label->setText(text);
    }

    void CheckBoxLabelView::setTextAlignment(const Qt::Alignment al) const
    {
        std::pair<QLabel*, QWidget*> pair{nullptr, nullptr};
        extract(pair);
        if (!pair.first)
            return;

        QBoxLayout* lo = boxLayout();
        if (!lo)
            return;

        if (al == Qt::AlignLeft)
        {
            lo->addWidget(pair.first);
            lo->addWidget(pair.second);
        }
        else
        {
            lo->addWidget(pair.second);
            lo->addWidget(pair.first);
        }
    }

    void CheckBoxLabelView::addOutput(const BoolModel::Observer& v) const
    {
        if (_check)
            _check->addOutput(v);
    }

}  // namespace Rt2::View
