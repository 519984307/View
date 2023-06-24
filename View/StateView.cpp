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
#include "View/StateView.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include "States/Default.h"
#include "View/Qu.h"
#include "View/States/State.h"
#include "View/StyleSheetWriter.h"

namespace Rt2::View
{
    StateView::StateView(QWidget*              parent,
                         VisualState*          states,
                         const int             eventFlags,
                         const Qt::WindowFlags wf) :
        QWidget(parent, wf),
        _viewStates(states ? states : new Visual::Default()),
        _eventFlags(eventFlags)
    {
    }

    StateView::~StateView()
    {
        delete _viewStates;
        _viewStates = nullptr;
    }

    VisualData& StateView::get(const VisualType type)
    {
        return _viewStates->get(type);
    }

    const VisualData& StateView::get(const VisualType type) const
    {
        return _viewStates->get(type);
    }

    QColor StateView::backgroundColor(const VisualType type) const
    {
        return get(type).backgroundColor();
    }

    QColor StateView::borderColor(const VisualType type) const
    {
        return get(type).borderColor();
    }

    QColor StateView::foregroundColor(const VisualType type) const
    {
        return get(type).foregroundColor();
    }

    QColor StateView::highlightForegroundColor(const VisualType type) const
    {
        return get(type).highlightForegroundColor();
    }

    QColor StateView::highlightBackgroundColor(const VisualType type) const
    {
        return get(type).highlightBackgroundColor();
    }

    void StateView::setBackgroundColor(const QColor& col, const VisualType type)
    {
        get(type).setBackgroundColor(col);
    }

    void StateView::setForegroundColor(const QColor& col, const VisualType type)
    {
        get(type).setForegroundColor(col);
    }

    void StateView::setBorderColor(const QColor& col, const VisualType type)
    {
        get(type).setBorderColor(col);
    }

    void StateView::setHighlightBackgroundColor(const QColor& col, const VisualType type)
    {
        get(type).setHighlightBackgroundColor(col);
    }

    void StateView::setHighlightForegroundColor(const QColor& col, const VisualType type)
    {
        get(type).setHighlightForegroundColor(col);
    }

    void StateView::setBorder(const QMargins& border, const VisualType type)
    {
        get(type).setBorder(border);
    }

    void StateView::setBorder(int v, const VisualType type)
    {
        setBorder({v, v, v, v}, type);
    }

    void StateView::setBorder(int start, int end, const VisualType type)
    {
        setBorder({start, 0, end, 0}, type);
    }

    void StateView::setBorder(int left, int top, int right, int bottom, const VisualType type)
    {
        setBorder({left, top, right, bottom}, type);
    }

    void StateView::setBorderRadius(const qreal v, const VisualType type)
    {
        get(type).setBorderRadius(v);
    }

    void StateView::setPadding(const QMargins& margins, const VisualType type)
    {
        QSize old = minimumSize();
        old.setWidth(old.width() + Max(0, margins.right() + margins.left()));
        old.setHeight(old.height() + Max(0, margins.bottom() + margins.top()));
        setMinimumSize(old);
        get(type).setPadding(type);

        emit paddingChanged(margins);
    }

    void StateView::setPadding(int v, const VisualType type)
    {
        setPadding({v, v, v, v}, type);
    }

    void StateView::setPadding(int start, int end, const VisualType type)
    {
        setPadding({start, 0, end, 0}, type);
    }

    void StateView::setPadding(int left, int top, int right, int bottom, const VisualType type)
    {
        setPadding({left, top, right, bottom}, type);
    }

    void StateView::setMargin(const QMargins& margins, const VisualType type)
    {
        QSize old = minimumSize();
        old.setWidth(old.width() + Max(0, margins.right() + margins.left()));
        old.setHeight(old.height() + Max(0, margins.bottom() + margins.top()));
        setMinimumSize(old);

        get(type).setMargin(margins);

        emit marginChanged(margins);
    }

    void StateView::setMargin(int v, const VisualType type)
    {
        setMargin({v, v, v, v}, type);
    }

    void StateView::setMargin(int start, int end, const VisualType type)
    {
        setMargin({start, 0, end, 0}, type);
    }

    void StateView::setMargin(int left, int top, int right, int bottom, const VisualType type)
    {
        setMargin({left, top, right, bottom}, type);
    }

    void StateView::setFontSize(const int size, const VisualType type)
    {
        get(type).setFontSize(size);
    }

    void StateView::setState(const VisualType type)
    {
        apply(type);
    }

    void StateView::setAttributeState(VisualAttribute attr, bool v) const
    {
        RT_GUARD_CHECK_VOID(_viewStates)
        _viewStates->setAttribute(attr, v);
    }

    void StateView::apply(const VisualType type)
    {
        RT_GUARD_CHECK_VOID(_viewStates)
        if (_viewStates->cacheDirty())
            _viewStates->mark();

        Visual::State::apply(get(type), this);
    }

    void StateView::apply(const VisualType type, QWidget* widget)
    {
        RT_GUARD_CHECK_VOID(_viewStates)
        if (_viewStates->cacheDirty())
            _viewStates->mark();

        Visual::State::apply(get(type), widget);
    }

    void StateView::enterEvent(QEnterEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)
        if (_eventFlags & VisualFlag::HoverState)
            apply(VisualType::Hover);
        QWidget::enterEvent(event);
    }

    void StateView::leaveEvent(QEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)
        if (_eventFlags & VisualFlag::HoverState)
            apply(VisualType::Normal);
        QWidget::leaveEvent(event);
    }

    void StateView::showEvent(QShowEvent* event)
    {
        RT_GUARD_CHECK_VOID(event)
        if (_eventFlags & VisualFlag::ApplyOnShow)
            apply(VisualType::Normal);
        QWidget::showEvent(event);
    }

}  // namespace Rt2::View
