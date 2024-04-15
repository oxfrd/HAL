//
// Created by oxford on 19.09.23.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include "IPort.h"
#include "IMcu.h"

namespace hal::gpio
{
    enum class eSpeed
    {
        eVeryLow,
        eLow,
        eMediumLow,
        eMedium,
        eMediumHigh,
        eHigh,
        eVeryHigh,
    };

    enum class eTermination
    {
        eFloating,
        ePullUp,
        ePullDown,
        eReserved,
    };

}