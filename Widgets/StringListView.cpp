#include "Widgets/StringListView.h"
#include <QListView>
#include <QStringListModel>
#include "Colors.h"
#include "Metrics.h"
#include "Qu.h"

class QLineEdit;

namespace Rt2::Widgets
{
    StringListView::StringListView(QWidget* parent) :
        QWidget(parent)
    {
        construct();
    }

    void StringListView::construct()
    {
        Qu::setBackground(this, Colors::Border);
        setContentsMargins(Metrics::BorderThick);

        const auto layout = Qu::horizontal();

        _listing = new QListView(this);
        _listing->setSelectionRectVisible(false);
        _listing->setAlternatingRowColors(true);
        _listing->setEditTriggers(QAbstractItemView::NoEditTriggers);

        Qu::setBackground(_listing, Colors::Background);
        Qu::setForeground(_listing, Colors::Foreground);
        Qu::setColor(_listing, QPalette::AlternateBase, Colors::CtrlBackgroundLight);
        
        _listing->setFrameShape(QFrame::NoFrame);

        layout->addWidget(_listing, 1);
        setLayout(layout);
        bind();
    }

    void StringListView::itemDoubleClickedImpl(const QModelIndex& index)
    {
        const QString str = index.data().toString();

        emit itemDoubleClicked(index.row(), str.toStdString());
    }

    void StringListView::setList(const StringArray& strList) const
    {
        if (!_listing->model())
            _listing->setModel(new QStringListModel());

        QStringListModel* model = (QStringListModel*)_listing->model();

        QStringList  old = model->stringList();
        const size_t os  = old.size();

        if (const size_t ns = strList.size();
            os >= ns)
        {
            old.resize(ns);
            for (size_t i = 0; i < ns; ++i)
                old[i] = Qsu::to(strList[i]);
        }
        else
        {
            size_t i = 0;
            for (; i < os; ++i)
                old[i] = Qsu::to(strList[i]);
            for (; i < ns; ++i)
                old.push_back(Qsu::to(strList[i]));
        }

        model->setStringList(old);
    }

    void StringListView::addInput(const ObserverType& ot)
    {
        _viewModel.addInput(ot);
    }

    void StringListView::bind()
    {
        connect(_listing,
                &QListView::doubleClicked,
                this,
                &StringListView::itemDoubleClickedImpl);
    }
}  // namespace Rt2::Widgets
