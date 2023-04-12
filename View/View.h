#pragma once
#include <QWidget>
#include "View/Definitions.h"

class QVBoxLayout;

namespace Rt2::View
{
    class View : public QWidget
    {
        Q_OBJECT
    protected:
        QWidget*     _content{nullptr};
        QVBoxLayout* _layout{nullptr};

        void constructView(
            QWidget*             content,
            int                  stretch = 1,
            const Qt::Alignment& al      = {});

    public:
        explicit View(QWidget* parent = nullptr);

        void setColor(QPalette::ColorRole role, const QColor& col) const;

        void setBorderColor(const QColor& col);

        void setBackgroundColor(const QColor& col) const;

        void setForegroundColor(const QColor& col) const;

        void setBorder(const QMargins& border);

        void setBorder(int v);

        void setBorder(int start, int end);

        void setBorder(int left, int top, int right, int bottom);

        void setPadding(const QMargins& margins) const;

        void setPadding(int v) const;

        void setPadding(int start, int end) const;

        void setPadding(int left, int top, int right, int bottom) const;

        void setFontSize(int size) const;

        void refresh();
    };
    
}  // namespace Rt2::View
