#pragma once
#include "Utils/Array.h"
#include "Utils/String.h"
namespace Rt2::Window
{
    using ByteArray = SimpleArray<uint8_t>;


    class Resource
    {
    public:
        static void getStyle(ByteArray &dest);

        static void getStyle(String &dest);
    };
} // namespace Rt2::Window
