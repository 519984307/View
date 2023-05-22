#pragma once
#include <QListView>
#include "View/View.h"
#include "View/Definitions.h"

class QLineEdit;

namespace Rt2::View
{

    class StringListView final : public View
    {
        Q_OBJECT
    public:
        using ObserverType = StringListModel::Observer;

    signals:
        void itemDoubleClicked(const int idx, const String& data);

    private:
        QListView*      _listing{nullptr};
        StringListModel _viewModel;

    public:
        explicit StringListView(QWidget* parent = nullptr);

        void setList(const StringArray& strList) const;

        void addInput(const ObserverType& ot);

    private:
        void bind();

        void construct();

        void itemDoubleClickedImpl(const QModelIndex& index);
    };

}  // namespace Rt2::Widgets
