#pragma once
#include <QWidget>

namespace Rt2::View
{
    class LayoutView : public QWidget
    {
        Q_OBJECT
    protected:
        QLayout* _content{nullptr};

        void constructView(
            QLayout* content,
            int      stretch = 1);

    public:
        explicit LayoutView(QWidget* parent = nullptr);

        void setColor(QPalette::ColorRole role, const QColor& col);

        void setBorderColor(const QColor& col);

        void setBorder(const QMargins& border);

        void setBorder(int v);

        void setBorder(int start, int end);

        void setBorder(int left, int top, int right, int bottom);

        void setPadding(const QMargins& margins) const;

        void setPadding(int v) const;

        void setPadding(int start, int end) const;

        void setPadding(int left, int top, int right, int bottom) const;

        void refresh();
    };

}  // namespace Rt2::View
