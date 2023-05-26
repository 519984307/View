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
#include "Definitions.h"
#include "View/LayoutView.h"
#include "ViewModel/Property.h"

class QBoxLayout;
class QLabel;

namespace Rt2::View
{
    class FlagView final : public LayoutView
    {
        Q_OBJECT
    private:
        IntModel _bits{0};

    public:
        explicit FlagView(QWidget* parent = nullptr);

        ~FlagView() override;

        void addFlag(bool state, const String& text);

        void setBits(int bits) const;

        void addOutput(const IntModel::Observer& ot);

        void addInput(const IntModel::Observer& ot);

    private:
        void construct();
    };

}  // namespace Rt2::View
