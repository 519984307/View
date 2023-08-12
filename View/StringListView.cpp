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
#include <qsortfilterproxymodel.h>
#include <QBoxLayout>
#include <QListView>
#include <QStandardItemModel>
#include "Utils/Char.h"
#include "View/Qu.h"

namespace Rt2::View
{
    StringListView::StringListView(QWidget* parent) :
        View(parent, nullptr, VisualFlag::ApplyOnShow)
    {
        construct();
    }

    StringListView::~StringListView()
    {
        delete _listing->model();
        _listing->setModel(nullptr);
    }

    void StringListView::construct()
    {
        const auto model = new QStandardItemModel();
        model->setSortRole(Qt::UserRole + 1);

        _listing = new QListView(this);
        _listing->setModel(model);
        _listing->setSelectionRectVisible(false);
        _listing->setAlternatingRowColors(true);
        _listing->setEditTriggers(QAbstractItemView::NoEditTriggers);
        _listing->setFrameShape(QFrame::NoFrame);
        constructView(_listing);

        connect(_listing,
                &QListView::doubleClicked,
                this,
                &StringListView::itemDoubleClickedImpl);

        connect(_listing,
                &QListView::clicked,
                this,
                &StringListView::itemClickedImpl);
    }

    void StringListView::itemDoubleClickedImpl(const QModelIndex& index)
    {
        _doubleClick.setValue(
            index.data(Qt::UserRole),
            ViewModel::OUTPUT);
    }

    void StringListView::itemClickedImpl(const QModelIndex& index)
    {
        _click.setValue(
            index.data(Qt::UserRole),
            ViewModel::OUTPUT);
    }

    void StringListView::addEntry(const String& string, const QVariant& data, const QVariant& sortData) const
    {
        addEntry({}, string, data, sortData);
    }

    void StringListView::addEntry(const QIcon& ico, const String& string, const QVariant& data, const QVariant& sortData) const
    {
        RT_GUARD_CHECK_VOID(!string.empty() && _listing && _listing->model())

        if (QStandardItemModel* model = (QStandardItemModel*)_listing->model())
        {
            const int cur = model->rowCount();
            model->insertRows(cur, 1);
            if (ico.isNull())
                model->setItem(cur, new QStandardItem(Qsu::to(string)));
            else
                model->setItem(cur, new QStandardItem(ico, Qsu::to(string)));

            const QModelIndex idx = model->index(cur, 0);
            if (!data.isNull())
                model->setData(idx, data, Qt::UserRole);

            if (!sortData.isNull())
            {
                model->setData(idx, data, Qt::InitialSortOrderRole);
                model->setData(idx, sortData, Qt::UserRole + 1);
            }
        }
    }

    void StringListView::clear() const
    {
        RT_GUARD_CHECK_VOID(_listing && _listing->model())

        delete _listing->model();
        const auto model = new QStandardItemModel();
        model->setSortRole(Qt::UserRole + 1);
        _listing->setModel(model);
    }

    void StringListView::addInput(const StringListModel::Observer& ot)
    {
        _strings.addInput(ot);
    }

    void StringListView::addDoubleClickOutput(const VariantModel::Observer& ot)
    {
        _doubleClick.addOutput(ot);
    }

    void StringListView::addClickOutput(const VariantModel::Observer& ot)
    {
        _click.addOutput(ot);
    }

    void StringListView::sort(const Qt::SortOrder order) const
    {
        RT_GUARD_VOID(_listing && _listing->model())
        _listing->model()->sort(0, order);
    }
    
}  // namespace Rt2::View
