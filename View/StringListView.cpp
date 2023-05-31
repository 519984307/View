/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "View/StringListView.h"
#include <QBoxLayout>
#include <QListView>
#include <QStandardItemModel>
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

class QLineEdit;

namespace Rt2::View
{
    StringListView::StringListView(QWidget* parent) :
        View(parent)
    {
        construct();
    }

    void StringListView::construct()
    {
        _listing = new QListView(this);
        _listing->setModel(new QStandardItemModel());
        constructView(_listing);
        setColor(QPalette::AlternateBase, Colors::Emphasis[0]);
        setPadding(Metrics::borderSizeThin);

        _listing->setSelectionRectVisible(false);
        _listing->setAlternatingRowColors(true);
        _listing->setEditTriggers(QAbstractItemView::NoEditTriggers);

        _listing->setFrameShape(QFrame::NoFrame);

        connect(_listing,
                &QListView::doubleClicked,
                this,
                &StringListView::itemDoubleClickedImpl);
    }

    void StringListView::itemDoubleClickedImpl(const QModelIndex& index)
    {
        _string.setValue(
            index.data(Qt::UserRole).toString().toStdString(),
            ViewModel::OUTPUT);
    }

    void StringListView::addEntry(const String& string, const String& data) const
    {
        addEntry({}, string, data);
    }

    void StringListView::addEntry(const QIcon& ico, const String& string, const String& data) const
    {
        if (string.empty()) return;

        if (QStandardItemModel* model = (QStandardItemModel*)_listing->model())
        {
            const int cur = model->rowCount();
            model->insertRows(cur, 1);
            if (ico.isNull())
                model->setItem(cur, new QStandardItem(Qsu::to(string)));
            else
                model->setItem(cur, new QStandardItem(ico, Qsu::to(string)));

            if (!data.empty())
            {
                const QModelIndex idx = model->index(cur, 0);
                model->setData(idx, QVariant(Qsu::to(data)), Qt::UserRole);
            }
        }
    }

    void StringListView::clear()
    {
        if (QStandardItemModel* model = (QStandardItemModel*)_listing->model())
            model->clear();
        refresh();
    }

    void StringListView::addInput(const StringListModel::Observer& ot)
    {
        _strings.addInput(ot);
    }

    void StringListView::addOutput(const StringModel::Observer& ot)
    {
        _string.addOutput(ot);
    }
}  // namespace Rt2::View
