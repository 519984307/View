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
#pragma once
#include <QListView>
#include "View/Definitions.h"
#include "View/View.h"

class QLineEdit;

namespace Rt2::View
{
    class StringListView final : public View
    {
        Q_OBJECT
    private:
        QListView*      _listing{nullptr};
        StringListModel _strings;
        StringModel     _string;

    public:
        explicit StringListView(QWidget* parent = nullptr);

        [[deprecated]] void setList(const StringArray& strList);

        void addEntry(const String& string, const String& data = "") const;

        void clear();

        void addInput(const StringListModel::Observer& ot);

        void addOutput(const StringModel::Observer& ot);

    private:
        void construct();

        void itemDoubleClickedImpl(const QModelIndex& index);
    };

}  // namespace Rt2::View
