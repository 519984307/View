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
#include "View/CustomView.h"

namespace Rt2::View
{

    class FlagViewItem final : public CustomView
    {
        Q_OBJECT
    private:
        int    _state{NONE};
        int    _index{0};
        QColor _accent;
        QColor _background;

    signals:
        void stateChanged(bool state, int index);

    public:
        explicit FlagViewItem(bool on, int index, const QString& toolTip, QWidget* parent = nullptr);

        bool isOn() const;

        void setState(bool state);

        void setAccentColor(const QColor& col);

        void setBackgroundColor(const QColor& col) override;

    private:
        void construct();

        void render(QPainter& paint, const QRectF& rect) override;

        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;
    };

    inline bool FlagViewItem::isOn() const
    {
        return (_state & ON) != 0;
    }

}  // namespace Rt2::View
