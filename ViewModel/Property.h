#pragma once
#include "Utils/Definitions.h"
#include "ViewModel/ViewModel.h"

namespace Rt2::ViewModel
{
    using BoolModel       = ViewModel<bool>;
    using IntModel        = ViewModel<int>;
    using FloatModel      = ViewModel<float>;
    using StringModel     = ViewModel<String>;
    using StringListModel = ViewModel<StringArray>;

}  // namespace Rt2::ViewModel
