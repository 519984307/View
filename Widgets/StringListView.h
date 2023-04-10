#pragma once
#include <QListView>
#include "ViewModel/Property.h"
#include "ViewModel/ViewModel.h"
#include "Widgets/Definitions.h"

class QLineEdit;

namespace Rt2::Widgets
{

    class StringListView final : public QWidget
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
