#include "View/StringListView.h"
#include <QListView>
#include <QBoxLayout>
#include <QStringListModel>
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

class QLineEdit;

namespace Rt2::View
{
    StringListView::StringListView(QWidget* parent) :
        View(parent)
    {
        _listing = new QListView(this);
        construct();
    }

    void StringListView::construct()
    {
        constructView(_listing);
        setBorderColor(Colors::BorderLight);
        setColor(QPalette::AlternateBase, Colors::CtrlBackgroundLight);
        setColor(QPalette::AlternateBase, Colors::CtrlBackground);
        setPadding(Metrics::borderSizeThin);

        _listing->setSelectionRectVisible(false);
        _listing->setAlternatingRowColors(true);
        _listing->setEditTriggers(QAbstractItemView::NoEditTriggers);

        _listing->setFrameShape(QFrame::NoFrame);
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
}  // namespace Rt2::View
