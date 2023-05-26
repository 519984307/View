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
#include <QWidget>
#include "CheckBoxView.h"
#include "View/LayoutView.h"

namespace Rt2::View
{
    class CheckBoxLabelView final : public LayoutView
    {
        Q_OBJECT
    private:
        QLabel*       _label{nullptr};
        CheckBoxView* _check{nullptr};

    public:
        explicit CheckBoxLabelView(const QString& text, QWidget* parent = nullptr);

        ~CheckBoxLabelView() override;

        void setChecked(bool v) const;

        bool isChecked() const;

        void setText(const QString& text) const;

        void setTextAlignment(Qt::Alignment al) const;

        void addOutput(const BoolModel::Observer &v) const;

    private:
        void construct();

        void extract(std::pair<QLabel*, QWidget*> &dest) const;
    };

}  // namespace Rt2::View
