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
#include "View/Definitions.h"

namespace Rt2::View::Visual
{
    class State
    {
    protected:
        int _attributes{NoAttribute};

    public:
        State();

        virtual ~State();

        virtual Data& get(StateType type) = 0;
        virtual void mark() {}

        bool isToggleOn() const;

        bool isToggleOff() const;

        bool isDirty() const;

        bool cacheDirty();

        bool hasBackground() const;

        void setAttribute(StateAttribute attr, bool on);

        static void apply(const Data& data, QWidget* widget);
    };
    

    inline bool State::isToggleOn() const
    {
        return (_attributes & ToggleOn) != 0;
    }

    inline bool State::isToggleOff() const
    {
        return (_attributes & ToggleOff) != 0;
    }

    inline bool State::hasBackground() const
    {
        return (_attributes & NoBackground) == 0;
    }

    inline bool State::isDirty() const
    {
        return (_attributes & Dirty) != 0;
    }

}  // namespace Rt2::View::Visual
