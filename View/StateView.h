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
#include "View/Definitions.h"

namespace Rt2::View
{
    class StateView : public QWidget
    {
        Q_OBJECT
    protected:
        VisualState* _viewStates{nullptr};
        int          _eventFlags{0};

    signals:
        void marginChanged(const QMargins& margins);
        void paddingChanged(const QMargins& margins);

    public:
        explicit StateView(QWidget*        parent     = nullptr,
                           VisualState*    states     = nullptr,
                           int             eventFlags = 0,
                           Qt::WindowFlags wf         = {});
        ~StateView() override;

        VisualData& get(VisualType type);

        const VisualData& get(VisualType type) const;

        QColor backgroundColor(VisualType type = VisualType::Normal) const;

        QColor borderColor(VisualType type = VisualType::Normal) const;

        QColor foregroundColor(VisualType type = VisualType::Normal) const;

        QColor highlightBackgroundColor(VisualType type = VisualType::Normal) const;

        QColor highlightForegroundColor(VisualType type = VisualType::Normal) const;

        void setBackgroundColor(const QColor& col, VisualType type = VisualType::Normal);

        void setBorderColor(const QColor& col, VisualType type = VisualType::Normal);

        void setForegroundColor(const QColor& col, VisualType type = VisualType::Normal);

        void setHighlightBackgroundColor(const QColor& col, VisualType type = VisualType::Normal);

        void setHighlightForegroundColor(const QColor& col, VisualType type = VisualType::Normal);

        void setBorderRadius(qreal v, VisualType type = VisualType::Normal);

        void setBorder(const QMargins& border, VisualType type = VisualType::Normal);

        void setBorder(int v, VisualType type = VisualType::Normal);

        void setBorder(int start, int end, VisualType type = VisualType::Normal);

        void setBorder(int left, int top, int right, int bottom, VisualType type = VisualType::Normal);

        void setPadding(const QMargins& margins, VisualType type = VisualType::Normal);

        void setPadding(int v, VisualType type = VisualType::Normal);

        void setPadding(int start, int end, VisualType type = VisualType::Normal);

        void setPadding(int left, int top, int right, int bottom, VisualType type = VisualType::Normal);

        void setMargin(const QMargins& margins, VisualType type = VisualType::Normal);

        void setMargin(int v, VisualType type = VisualType::Normal);

        void setMargin(int start, int end, VisualType type = VisualType::Normal);

        void setMargin(int left, int top, int right, int bottom, VisualType type = VisualType::Normal);

        void setFontSize(int size, VisualType type = VisualType::Normal);

        void setState(VisualType type);

    protected:
        void setAttributeState(VisualAttribute attr, bool v) const;

        void apply(VisualType type);

        void apply(VisualType type, QWidget* widget);

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;

        void showEvent(QShowEvent* event) override;
    };

}  // namespace Rt2::View
