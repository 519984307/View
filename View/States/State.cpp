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
#include "View/States/State.h"
#include <qstyle.h>
#include <QWidget>
#include "View/States/Data.h"
#include "View/StyleSheetWriter.h"

namespace Rt2::View::Visual
{
    State::State()  = default;
    State::~State() = default;
    
    bool State::cacheDirty() 
    {
        const bool result = isDirty();
        _attributes &= ~Dirty;
        return result;
    }

    void State::setAttribute(const StateAttribute attr, const bool on)
    {
        if (on) _attributes |= attr;
        else  _attributes &= ~attr;
        _attributes |= Dirty;
    }

    void State::apply(const Data& data, QWidget* widget)
    {
        RT_GUARD_CHECK_VOID(widget)
        if (const QString& obj = widget->objectName();
            !obj.isEmpty())
            widget->setStyleSheet(data.value(obj));
        else
            widget->setStyleSheet(data.value());
    }
}  // namespace Rt2::View::Visual
